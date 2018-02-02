/**
*	@file init.h
*	@brief This file contains constans and init function prototypes
*	
*/

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_flash.h"
#include "misc.h"
#include "attributes.h"		
#include "tm_stm32f4_hcsr04.h"
#include "step_motor.h"


/**
*  Definition of all the ports, pins and other peripheral devices
*	 which are used. Every change you want to concerning different
*	 pin selection, you are able to do here. If not written differently,
*  you don't have to alter any other file.
*/

/* LED and BUTTON port and pins -------------------------*/
#define LEDPORT GPIOD
#define LEDRCC 	RCC_AHB1Periph_GPIOD

#define LED1PIN GPIO_Pin_12
#define LED2PIN GPIO_Pin_13
#define LED3PIN GPIO_Pin_14
#define LED4PIN GPIO_Pin_15

#define BUTTONPIN 	GPIO_Pin_0
#define BUTTONPORT 	GPIOA
#define BUTTONRCC 	RCC_AHB1Periph_GPIOA

#define BUZZERPIN	 	GPIO_Pin_7
#define BUZZERPORT 	GPIOA
#define BUZZERRCC 	RCC_AHB1Periph_GPIOA
/* ------------------------------------------------------*/

/* USART2 rcc, port, pins and interrupt ------------------*/
#define USARTID 	USART2
#define USARTRCC 	RCC_APB1Periph_USART2
#define USART_IRQ	USART2_IRQn
#define USART_AF 	GPIO_AF_USART2

#define USART_GPIORCC	RCC_AHB1Periph_GPIOA
#define USARTPORT			GPIOA
#define USART_TX_PIN	GPIO_Pin_2
#define TX_PIN_SOURCE	GPIO_PinSource2
#define USART_RX_PIN  GPIO_Pin_3
#define RX_PIN_SOURCE GPIO_PinSource3
/* ------------------------------------------------------*/
///* USART1 rcc, port, pins and interrupt ------------------*/
//#define USARTID1 	USART1
//#define USARTRCC1 	RCC_APB2Periph_USART1
//#define USART_IRQ1	USART1_IRQn
//#define USART_AF1 	GPIO_AF_USART1

//#define USART_GPIORCC1	RCC_AHB1Periph_GPIOD
//#define USARTPORT1			GPIOD
//#define USART_TX_PIN1	GPIO_Pin_3
//#define TX_PIN_SOURCE1	GPIO_PinSource3
//#define USART_RX_PIN1  GPIO_Pin_4
//#define RX_PIN_SOURCE1 GPIO_PinSource4
/* ------------------------------------------------------*/

/* DH22 port, pins and timer --------------------------- */
#define DHT22_GPIO	GPIOA
#define DHT22_DATA_PIN1 GPIO_Pin_5

#define DHT22_TIM	TIM2
#define DHT22RCC RCC_APB1Periph_TIM2
#define DHT22_REFRESHRATE 5000	//refresh rate in ms
/* ------------------------------------------------------*/
/* DH22 port, pins and timer --------------------------- */
#define DHT22_GPIO	GPIOA
#define DHT22_DATA_PIN2 GPIO_Pin_1

#define DHT22_TIM	TIM2
#define DHT22RCC RCC_APB1Periph_TIM2
#define DHT22_REFRESHRATE 5000	//refresh rate in ms
/* ------------------------------------------------------*/

/* HCSR ultrasonic sensor port, pins and timer ----------*/
#define HCSRPORT 			GPIOC
#define HCSR_RCC 			RCC_AHB1Periph_GPIOC
#define HCSR_ECHO_PIN	GPIO_Pin_5
#define HCSR_TRIG_PIN GPIO_Pin_4

#define TM_DELAY_TIM							TIM4
#define TM_DELAY_TIM_IRQ					TIM4_IRQn
#define TM_DELAY_TIM_IRQ_HANDLER	TIM4_IRQHandler
#define HCSR_REFRESHRATE	1000
/* ------------------------------------------------------*/

/* Step motor port and pins -----------------------------*/
#define PWMA_PORT GPIOB
#define PWMB_PORT GPIOB
#define DIRA_PORT GPIOB
#define DIRB_PORT GPIOD

#define PWMA_RCC  RCC_AHB1Periph_GPIOB
#define PWMB_RCC 	RCC_AHB1Periph_GPIOB
#define DIRA_RCC	RCC_AHB1Periph_GPIOB
#define DIRB_RCC 	RCC_AHB1Periph_GPIOD

#define PWMA_PIN  GPIO_Pin_13
#define PWMB_PIN	GPIO_Pin_14
#define DIRA_PIN	GPIO_Pin_15
#define DIRB_PIN	GPIO_Pin_8

/* ------------------------------------------------------*/


/* ------------------------------------------------------*/

/* MFRC522 and SPI port and pins ------------------------*/
#define MFRC522_CS_RCC				RCC_AHB1Periph_GPIOA
#define MFRC522_CS_PORT				GPIOA
#define MFRC522_CS_PIN				GPIO_Pin_8
/* For SPIx and TM_SPI_PinsPack_x definitions look at tm_stm32f4_spi.h */
#define MFRC522_SPI						SPI1
#define MFRC522_SPI_PINSPACK	TM_SPI_PinsPack_2
#define RFID_REFRESHRATE 200
/* ------------------------------------------------------*/

/* Servo motor port and pins ----------------------------*/
/* For TM_PWM_Channel_x and TM_PWM_PinsPack_x look at tm_stm32f4_pwm.h */
#define SERVO_CHANNEL 	TM_PWM_Channel_2	//This sets servo pwm pin to PA9
#define SERVO_PINSPACK 	TM_PWM_PinsPack_1
#define SCANNER_CHANNEL	TM_PWM_Channel_3
#define SCANNER_PINSPACK 	TM_PWM_PinsPack_1

#define BUZZER_CHANNEL	TM_PWM_Channel_2
#define BUZZER_PINSPACK 	TM_PWM_PinsPack_1


#define SERVO_TIM TIM1
#define SCANNER_TIM TIM1
#define BUZZER_TIM TIM3
/* ------------------------------------------------------*/

/* Protocol data ID list --------------------------------*/
//#define DHT_ID 0x1
//#define DHT_SUB_ID0 0x0				//Added in case of more sensors of the same type(with the same ID).
//#define DHT_SUB_ID1 0x1
//#define INITIAL_MAP_ID 0x2
//#define MAP_ERROR_ID 0x3
//#define RFID_ID 0x4
///* ------------------------------------------------------*/
#define DHT_ID 0x21
#define DHT_SUB_ID0 0x22			//Added in case of more sensors of the same type(with the same ID).
#define DHT_SUB_ID1 0x23
#define INITIAL_MAP_ID 0x24
#define MAP_ERROR_ID 0x25
#define RFID_ID 0x26
/* ------------------------------------------------------*/

void gpio_init(void);
void flash_init(void);
void USART_Config(void);
void USART1_Config(void);


