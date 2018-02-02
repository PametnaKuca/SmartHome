#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

//#define ANGLEmin	(float) 0 //0.35  					// minimal possible angle movement
//#define gearratio	(float) 5.182						//gear ratio
//#define ANGLE	(float)5							  //desired angle step
//#define ANGLEmax (float) 90							//ANGLEmax/ANGLE has to be integer


#define ANGLEmin	(int) 0 //0.35  					// minimal possible angle movement
#define gearratio	(float) 5.182						//gear ratio
#define ANGLE	(int) 30						  //desired angle step
#define ANGLEmax (int) 900
	

void init_step(void);
void move_positive(void);
void move_negative(void);
void delay_step(uint32_t ms);
