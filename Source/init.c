/**
*	@file init.c
*	@brief This file contains init functions
*	
*/



#include "init.h"



//void exti(void)
//{
//	 GPIO_InitTypeDef GPIO_InitStruct;

//    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;

//    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;

//    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;

//    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;

//    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;

//    GPIO_Init(GPIOA, &GPIO_InitStruct);


//	EXTI_InitTypeDef  USER_BUTTON;
//	USER_BUTTON.EXTI_Line=EXTI_Line0;
//	USER_BUTTON.EXTI_Mode=EXTI_Mode_Interrupt;
//	USER_BUTTON.EXTI_Trigger=EXTI_Trigger_Rising;
//	USER_BUTTON.EXTI_LineCmd=ENABLE;
//	
//	EXTI_Init(&USER_BUTTON);
//	
//	 NVIC_InitTypeDef NVIC_InitStruct;
//    NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
//    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
//    // EXTI0_IRQn has Most important interrupt
//    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
//    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
//    NVIC_Init(&NVIC_InitStruct);
//	
//}

/* add startup functions (GPIO, RCC, UART...) here*/
void gpio_init(void)
{
	RCC_AHB1PeriphClockCmd(LEDRCC, ENABLE);

	
	GPIO_InitTypeDef GPIO_LEDS;
	GPIO_LEDS.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_LEDS.GPIO_OType=GPIO_OType_PP;
	GPIO_LEDS.GPIO_Pin= LED1PIN | LED2PIN | LED3PIN | LED4PIN;
	GPIO_LEDS.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIO_LEDS.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(LEDPORT, &GPIO_LEDS);		
	
	GPIO_InitTypeDef GPIO_BUTTON;
	GPIO_BUTTON.GPIO_Mode=GPIO_Mode_IN;
	GPIO_BUTTON.GPIO_OType=GPIO_OType_PP;
	GPIO_BUTTON.GPIO_Pin=BUTTONPIN;
	GPIO_BUTTON.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIO_BUTTON.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(BUTTONPORT, &GPIO_BUTTON);
	


}

void flash_init(void)
{
	FLASH_SetLatency(FLASH_Latency_1);
	FLASH_PrefetchBufferCmd(ENABLE);
	FLASH_InstructionCacheCmd(ENABLE);
	FLASH_DataCacheCmd(ENABLE);
}

void USART_Config(void)
{
        GPIO_InitTypeDef  GPIO_InitStructure;
        USART_InitTypeDef USART_InitStructure;
				NVIC_InitTypeDef NVIC_InitStructure;

        RCC_APB1PeriphClockCmd(USARTRCC, ENABLE);
        RCC_AHB1PeriphClockCmd(USART_GPIORCC, ENABLE);

        GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2 | USART_RX_PIN;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
        GPIO_Init(USARTPORT, &GPIO_InitStructure);

        GPIO_PinAFConfig(USARTPORT, TX_PIN_SOURCE, USART_AF); // PA.2 = TX
        GPIO_PinAFConfig(USARTPORT, RX_PIN_SOURCE, USART_AF); // PA.3 = RX

        USART_InitStructure.USART_BaudRate            = 115200;
        USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
        USART_InitStructure.USART_StopBits            = USART_StopBits_1;
        USART_InitStructure.USART_Parity              = USART_Parity_No;
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

        USART_InitStructure.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;
        USART_Init(USARTID, &USART_InitStructure);
        USART_Cmd(USARTID, ENABLE);

        USART_ITConfig(USARTID, USART_IT_RXNE, ENABLE);
        NVIC_InitStructure.NVIC_IRQChannel	=	USART_IRQ;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=4;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
        NVIC_InitStructure.NVIC_IRQChannelCmd 	=	ENABLE;
        NVIC_Init(&NVIC_InitStructure);
}


//void USART1_Config(void)
//{
//        GPIO_InitTypeDef  GPIO_InitStructure;
//        USART_InitTypeDef USART_InitStructure;
//				NVIC_InitTypeDef NVIC_InitStructure;

//        RCC_APB2PeriphClockCmd(USARTRCC1, ENABLE);
//        RCC_AHB1PeriphClockCmd(USART_GPIORCC1, ENABLE);


//        GPIO_InitStructure.GPIO_Pin   = USART_TX_PIN1 | USART_RX_PIN1;
//        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
//        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
//        GPIO_Init(USARTPORT1, &GPIO_InitStructure);

//        GPIO_PinAFConfig(USARTPORT1, TX_PIN_SOURCE1, USART_AF1); // PA.2 = TX
//        GPIO_PinAFConfig(USARTPORT1, RX_PIN_SOURCE1, USART_AF1); // PA.3 = RX

//        USART_InitStructure.USART_BaudRate            = 115200;
//        USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
//        USART_InitStructure.USART_StopBits            = USART_StopBits_1;
//        USART_InitStructure.USART_Parity              = USART_Parity_No;
//        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

//        USART_InitStructure.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;
//        USART_Init(USARTID1, &USART_InitStructure);
//        USART_Cmd(USARTID1, ENABLE);

//        USART_ITConfig(USARTID1, USART_IT_RXNE, ENABLE);
//        NVIC_InitStructure.NVIC_IRQChannel	=	USART_IRQ1;
//        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=4;
//        NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
//        NVIC_InitStructure.NVIC_IRQChannelCmd 	=	ENABLE;
//        NVIC_Init(&NVIC_InitStructure);
//}
