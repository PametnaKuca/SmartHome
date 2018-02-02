#include "step_motor.h"
#include "tm_stm32f4_delay.h"

//const uint16_t STEP_PIN[] = {PWMA_PIN, PWMB_PIN, DIRA_PIN, DIRB_PIN}; //pins: PWMA,PWMB,DIRA,DIRB
//GPIO_TypeDef* STEP_PORT[] = {PWMA_PORT, PWMB_PORT, DIRA_PORT, DIRB_PORT};
//const uint16_t STEP_RCC[] = {PWMA_RCC, PWMB_RCC, DIRA_RCC, DIRB_RCC};
//const uint8_t steps[4][4] = {{0, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 1}, {0, 0, 1, 0}}; //smjer okreta motora od kanala B do kanala A
//const uint8_t steps_neg[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};	//smjer okreta motora od kanala A do kanala B
//uint32_t i = 0;


//void init_step() 
//{
//	uint8_t k;
//	GPIO_InitTypeDef GPIO_STEP;
//	for (k=0;k<4;k++)
//	{
//    RCC_AHB1PeriphClockCmd(STEP_RCC[k], ENABLE);

//		GPIO_StructInit(&GPIO_STEP);
//    GPIO_STEP.GPIO_Mode = GPIO_Mode_OUT;
//    GPIO_STEP.GPIO_Pin = STEP_PIN[k];
//    GPIO_Init(STEP_PORT[k], &GPIO_STEP);
//	}
//}


//void move_positive() {									
//	uint8_t j;
//	Delayms(10);
//	for (j = 0; j < 4; j++)
//	{
//		if (steps[i][j] == 0)
//		{
//			GPIO_ResetBits(STEP_PORT[j], STEP_PIN[j]);
//		}
//		else
//		{
//			GPIO_SetBits(STEP_PORT[j], STEP_PIN[j]);
//		}
//	}
//	i=(i+1)%4;
//}

//void move_negative() {								//postavljanje vrijednosti pinova kao sto je prikazano u matrici steps_neg (suprotan smjer)
//	uint8_t j;
//	Delayms(10);
//		for (j = 0; j < 4; j++)
//	{
//		if (steps_neg[i][j] == 0)
//		{
//			GPIO_ResetBits(STEP_PORT[j], STEP_PIN[j]);
//		}
//		else
//		{
//			GPIO_SetBits(STEP_PORT[j], STEP_PIN[j]);
//		}
//	}
//	i=(i+1)%4;
//}

#include "step_motor.h"
#include "tm_stm32f4_delay.h"



//const uint16_t STEP_PIN[] = {PWMA_PIN, PWMB_PIN, DIRA_PIN, DIRB_PIN}; //pins: PWMA,PWMB,DIRA,DIRB
//GPIO_TypeDef* STEP_PORT[] = {PWMA_PORT, PWMB_PORT, DIRA_PORT, DIRB_PORT};
//const uint16_t STEP_RCC[] = {PWMA_RCC, PWMB_RCC, DIRA_RCC, DIRB_RCC};
//const uint8_t steps[4][4] = {{0, 1, 0, 0}, {1, 0, 0, 0}, {0, 0, 0, 1}, {0, 0, 1, 0}}; //smjer okreta motora od kanala B do kanala A
//const uint8_t steps_neg[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};	//smjer okreta motora od kanala A do kanala B
//uint32_t i = 0;


//void init_step() 
//{
//	uint8_t k;
//	GPIO_InitTypeDef GPIO_STEP;
//	for (k=0;k<4;k++)
//	{
//    RCC_AHB1PeriphClockCmd(STEP_RCC[k], ENABLE);

//		GPIO_StructInit(&GPIO_STEP);
//    GPIO_STEP.GPIO_Mode = GPIO_Mode_OUT;
//    GPIO_STEP.GPIO_Pin = STEP_PIN[k];
//    GPIO_Init(STEP_PORT[k], &GPIO_STEP);
//	}
//}


//void move_positive() {									
//	uint8_t j;
//	Delayms(10);
//	for (j = 0; j < 4; j++)
//	{
//		if (steps[i][j] == 0)
//		{
//			GPIO_ResetBits(STEP_PORT[j], STEP_PIN[j]);
//		}
//		else
//		{
//			GPIO_SetBits(STEP_PORT[j], STEP_PIN[j]);
//		}
//	}
//	i=(i+1)%4;
//}

//void move_negative() {								//postavljanje vrijednosti pinova kao sto je prikazano u matrici steps_neg (suprotan smjer)
//	uint8_t j;
//	Delayms(10);
//		for (j = 0; j < 4; j++)
//	{
//		if (steps_neg[i][j] == 0)
//		{
//			GPIO_ResetBits(STEP_PORT[j], STEP_PIN[j]);
//		}
//		else
//		{
//			GPIO_SetBits(STEP_PORT[j], STEP_PIN[j]);
//		}
//	}
//	i=(i+1)%4;
//}


