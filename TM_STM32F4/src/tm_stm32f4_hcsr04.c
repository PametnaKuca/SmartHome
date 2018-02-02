#include "tm_stm32f4_hcsr04.h"	
#include "stm32f4xx_gpio.h"
#include "init.h"
	
uint8_t TM_HCSR04_Init(TM_HCSR04_t* HCSR04, uint32_t HCSR_RCC_GPIOx, GPIO_TypeDef* ECHO_GPIOx, uint16_t ECHO_GPIO_Pin, GPIO_TypeDef* TRIGGER_GPIOx, uint16_t TRIGGER_GPIO_Pin) {        
        
        TM_DELAY_Init();
				RCC_APB1PeriphClockCmd(HCSR_RCC_GPIOx, ENABLE);
        HCSR04->ECHO_GPIOx = HCSRPORT;
        HCSR04->ECHO_GPIO_Pin = HCSR_ECHO_PIN;//output
        HCSR04->TRIGGER_GPIOx = HCSRPORT;	
        HCSR04->TRIGGER_GPIO_Pin = HCSR_TRIG_PIN;//input

        

	
        TM_GPIO_Init(HCSR04->TRIGGER_GPIOx, HCSR04->TRIGGER_GPIO_Pin, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_DOWN, TM_GPIO_Speed_Fast); //Medium--> fast	
        

        TM_GPIO_Init(HCSR04->ECHO_GPIOx, HCSR04->ECHO_GPIO_Pin, TM_GPIO_Mode_IN, TM_GPIO_OType_PP, TM_GPIO_PuPd_DOWN, TM_GPIO_Speed_Fast);
        

        TM_GPIO_SetPinLow(HCSR04->TRIGGER_GPIOx, HCSR04->TRIGGER_GPIO_Pin);	
        
	
        if (TM_HCSR04_Read(HCSR04) >= 0) {
	
        
	
                return 1;
	
        }
	
        
	
        return 0;
	
}
	
float TM_HCSR04_Read(TM_HCSR04_t* HCSR04) {
	
        uint32_t timeout;
	
        float time;
	
        TM_GPIO_SetPinLow(HCSR04->TRIGGER_GPIOx, HCSR04->TRIGGER_GPIO_Pin);
	
        Delay(2);
	
        TM_GPIO_SetPinHigh(HCSR04->TRIGGER_GPIOx, HCSR04->TRIGGER_GPIO_Pin);
	
        Delay(10);
	
        TM_GPIO_SetPinLow(HCSR04->TRIGGER_GPIOx, HCSR04->TRIGGER_GPIO_Pin);
	
        timeout = HCSR04_TIMEOUT;

        while (!TM_GPIO_GetInputPinValue(HCSR04->ECHO_GPIOx, HCSR04->ECHO_GPIO_Pin)) {
					
                if (timeout-- == 0x00) {
                        return -1;	
                }
        }
				
				time = 0;	      
	        while (TM_GPIO_GetInputPinValue(HCSR04->ECHO_GPIOx, HCSR04->ECHO_GPIO_Pin)) {

                time+=(float)5;
                Delay(1);
        }
        HCSR04->Distance =  (float)time * HCSR04_NUMBER;	
        return HCSR04->Distance;
}
