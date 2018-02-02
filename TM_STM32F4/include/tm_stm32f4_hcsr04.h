#ifndef TM_HCSR04_H
#define TM_HCSR04_H 200	
#include "stm32f4xx.h"
#include "defines.h"
#include "tm_stm32f4_delay.h"
#include "gpio.h"
#ifndef HCSR04_TIMEOUT
#define HCSR04_TIMEOUT                        1000000	
#endif
#define HCSR04_NUMBER                        ((float)0.01718) //brzina zvuka, v=343m/s => v=34300cm/10^6micros=0.0343 => uzimamo pola =>0.0171 zbog udaljenosti predmeta
typedef struct {

        float Distance;              /*!< Distance measured from sensor in centimeters */
	
        GPIO_TypeDef* ECHO_GPIOx;    /*!< Pointer to GPIOx PORT for ECHO pin. Meant for private use only */
	
        uint16_t ECHO_GPIO_Pin;      /*!< GPIO Pin for ECHO pin. Meant for private use only */
	
        GPIO_TypeDef* TRIGGER_GPIOx; /*!< Pointer to GPIOx PORT for TRIGGER pin. Meant for private use only */
	
        uint16_t TRIGGER_GPIO_Pin;   /*!< GPIO Pin for ECHO pin. Meant for private use only */
	
} TM_HCSR04_t;
		
uint8_t TM_HCSR04_Init(TM_HCSR04_t* HCSR04, uint32_t HCSR_RCC_GPIOx, GPIO_TypeDef* ECHO_GPIOx, uint16_t ECHO_GPIO_Pin, GPIO_TypeDef* TRIGGER_GPIOx, uint16_t TRIGGER_GPIO_Pin);
	
float TM_HCSR04_Read(TM_HCSR04_t* HCSR04);
	
#ifdef __cplusplus
	
}
#endif	
#endif
