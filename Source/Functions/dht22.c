/*
DHT 22 humidity and temperature sensor library

    Copyright (C) 2013  Fabio Angeletti - fabio.angeletti89@gmail.com

    See attached license.txt file

*/

/* includes --------------------------------------------------------- */
#include "dht22.h"


/* functions -------------------------------------------------------- */
/*
  configure DHT22_DATA as input
 */
 
/* Added in order to have everything in one file. */

void DHT22_TIM_Init(void) {
  uint16_t PrescalerValue = 0;

  TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
  TIM_OCInitTypeDef         TIM_OCInitStructure;

  /* DHT22_TIM clock enable */
  RCC_APB1PeriphClockCmd(DHT22RCC, ENABLE);

  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_OCStructInit(&TIM_OCInitStructure);

  /* Compute the prescaler value */
  PrescalerValue = (uint16_t) (SystemCoreClock / 1000000) - 1;

  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 65535 - 1;      //in uSecs
  TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  TIM_Cmd(DHT22_TIM, ENABLE);
}


void DHT22pinIn(uint16_t DHT22_DATA_PIN){
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin =  DHT22_DATA_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(DHT22_GPIO, &GPIO_InitStructure);
}


/*
  configure DHT22_DATA as output
 */
void DHT22pinOut(uint16_t DHT22_DATA_PIN){
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin =  DHT22_DATA_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(DHT22_GPIO, &GPIO_InitStructure);
}


void DHT22_Init(uint16_t DHT22_DATA_PIN){
	DHT22_TIM_Init();
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  DHT22pinOut(DHT22_DATA_PIN);
  /* hold DHT22 in standby state */
  GPIO_SetBits(DHT22_GPIO, DHT22_DATA_PIN);
}


bool DHT22_Read(uint16_t DHT22_DATA_PIN){

	bool dbg_flag=true;
	uint8_t dataIndex = 0;
  uint8_t index = 0;
  uint32_t startTime = 0;	
	int times[40];
  /* reset data holder */
  for(index=0; index < 6; index++){
    DHT22data[index] = 0x00;
  }
  /* mcu sends start signal to sensor */
  DHT22pinOut(DHT22_DATA_PIN);
  GPIO_ResetBits(DHT22_GPIO, DHT22_DATA_PIN);
  TIM_SetCounter(DHT22_TIM, 0);
  /* wait for at least 20 mSecs */
  while(TIM_GetCounter(DHT22_TIM) < 20000);
	TIM_SetCounter(DHT22_TIM,0);
	GPIO_SetBits(DHT22_GPIO, DHT22_DATA_PIN);
	while(TIM_GetCounter(DHT22_TIM) < 30);
  /* switch to input and wait for sensor response */
  DHT22pinIn(DHT22_DATA_PIN);
  TIM_SetCounter(DHT22_TIM, 0);
	while(GPIO_ReadInputDataBit(DHT22_GPIO, DHT22_DATA_PIN))
	if(TIM_GetCounter(DHT22_TIM)>100){
			dbg_flag=false;
			break;
	}	
  /* DHT22 sends response signal */
	TIM_SetCounter(DHT22_TIM,0);
  while(!GPIO_ReadInputDataBit(DHT22_GPIO, DHT22_DATA_PIN))
		if(TIM_GetCounter(DHT22_TIM)>100){
			dbg_flag=false;
			break;
	}		
		TIM_SetCounter(DHT22_TIM,0);
  while(GPIO_ReadInputDataBit(DHT22_GPIO, DHT22_DATA_PIN))
		if(TIM_GetCounter(DHT22_TIM)>100){
			dbg_flag=false;
			break;
	}	
  /* DHT22 sends, finally, data */
  for (dataIndex=0; dataIndex<40; dataIndex++) {
    TIM_SetCounter(DHT22_TIM, 0);		
    while(!GPIO_ReadInputDataBit(DHT22_GPIO, DHT22_DATA_PIN))
			if(TIM_GetCounter(DHT22_TIM)>100){
			dbg_flag=false;
			break;
	}	
    startTime = TIM_GetCounter(DHT22_TIM);
    while(GPIO_ReadInputDataBit(DHT22_GPIO, DHT22_DATA_PIN))
			if(TIM_GetCounter(DHT22_TIM)-startTime>100){
			dbg_flag=false;
			break;
	}	
		times[dataIndex]=TIM_GetCounter(DHT22_TIM)-startTime;
  }
	for (int byte=0; byte<5; byte++)
	{
		DHT22data[byte] = 0;
		for (int bit=7; bit>=0;bit--)
		{			
			if(times[8*byte+7-bit]>50)
			{
				DHT22data[byte] |= (1<<bit);
			}
		}
	}
	if (DHT22data[4] == ((DHT22data[0] + DHT22data[1] + DHT22data[2] + DHT22data[3]) & 0xFF) && dbg_flag) {
		return true;
    
  }
	else return false;
	
}


float DHT22getTemperature(void){
  float retVal;
  retVal = DHT22data[2] & 0x7F;
  retVal *= 256;
  retVal += DHT22data[3];
  retVal /= 10;
  if (DHT22data[2] & 0x80)
    retVal *= -1;
  return retVal;
}


float DHT22getHumidity(void){
  float retVal;
  retVal = DHT22data[0];
  retVal *= 256;
  retVal += DHT22data[1];
  retVal /= 10;
  return retVal;
}


float convertCtoF(float cTemperature){
  return cTemperature * 9 / 5 + 32;
}


