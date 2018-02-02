#include "main.h"
#include "tm_stm32f4_disco.h"
#include "step_motor.h"
#include "tm_stm32f4_delay.h"


int main()
{	
		// init sequence
		gpio_init();
		flash_init();
		DHT22_Init(DHT22_DATA_PIN1);
		DHT22_Init(DHT22_DATA_PIN2);
	
		TM_HCSR04_Init(&HCSR04, HCSR_RCC, HCSRPORT, HCSR_ECHO_PIN, HCSRPORT, HCSR_TRIG_PIN); //ultrasound sensor init
	
		TM_PWM_InitTimer(SERVO_TIM, &servo_timer, 50);	//initialize SERVO_TIM as pwm output with frequency of 50kHZ
		TM_PWM_InitTimer(SCANNER_TIM, &scanner_timer, 50);	//initialize SERVO_TIM as pwm output with frequency of 50kHZ
		TM_PWM_InitTimer(BUZZER_TIM, &buzzer_timer, 3000);	//initialize SERVO_TIM as pwm output with frequency of 50kHZ
	
		TM_PWM_InitChannel(&servo_timer, SERVO_CHANNEL, SERVO_PINSPACK);
		TM_PWM_InitChannel(&scanner_timer, SCANNER_CHANNEL, SCANNER_PINSPACK);
		TM_PWM_InitChannel(&buzzer_timer, BUZZER_CHANNEL, BUZZER_PINSPACK);	
	
		TM_PWM_SetChannelMicros(&servo_timer, SERVO_CHANNEL, SERVO_MAX);			//set initial postion as closed
	  TM_PWM_SetChannelMicros(&scanner_timer, SCANNER_CHANNEL, SCANNER_MIN);	
//		TM_PWM_SetChannelMicros(&buzzer_timer, BUZZER_CHANNEL, 1000);	
		TM_MFRC522_Init(); 		//rfid module init
		USART_Config();

	
		xTaskCreate(space_mapping, "space_mapping_task", STACK_SIZE_MIN, NULL, 2, &HCSRHhandle);
		xTaskCreate(rfid_task, "rfid_check_task", STACK_SIZE_MIN, NULL, 3, &RFIDhandle);
		xTaskCreate(dht_task1, "dht task", STACK_SIZE_MIN, NULL, 2, &tHandDHT);
		xTaskCreate(dht_task2, "dht task", STACK_SIZE_MIN, NULL, 2, &tHandDHT);

		vTaskStartScheduler();
		while(1);

}

/**
*	The DHT task executes periodically every DHT22_REFRESHRATE milliseconds.
*	While the task is reading data from the sensor, which is an extremely time critical operation, the task raises its own priority
*	in order to prevent being halted either by another task or an ISR.
*/

void dht_task1(void *prvParams)
{
	while(1)
    { GPIO_ResetBits(LEDPORT, LED2PIN);
			
        bool checksumValid1;
			
				// For every defined pin, read again, but after get functions.
        vTaskPrioritySet(NULL, 2);
        checksumValid1=DHT22_Read(DHT22_DATA_PIN1);
        vTaskPrioritySet(NULL, 1);
				  GPIO_SetBits(LEDPORT, LED3PIN);
				// Check whether the reading is valid. If so, send new data.		
				if(checksumValid1)
				{
        temperature1=DHT22getTemperature();
        humidity1=DHT22getHumidity();
				}			
				sendDHT22(temperature1,humidity1, DHT_SUB_ID0);
				GPIO_ResetBits(LEDPORT, LED3PIN);
        vTaskDelay(DHT22_REFRESHRATE*2/portTICK_RATE_MS);
		}
}

void dht_task2(void *prvParams)
{
	while(1)
    {
        bool checksumValid2;
        GPIO_SetBits(LEDPORT, LED4PIN);
				
				// For every defined pin, read again, but after get functions.
        vTaskPrioritySet(NULL, 2);
        checksumValid2=DHT22_Read(DHT22_DATA_PIN2);
        vTaskPrioritySet(NULL, 1);
				// Check whether the reading is valid. If so, send new data.
				
				if(checksumValid2)
				{
        temperature2=DHT22getTemperature();
        humidity2=DHT22getHumidity();
				}		
        GPIO_ResetBits(LEDPORT, LED4PIN);				
				sendDHT22(temperature2,humidity2, DHT_SUB_ID1);
				
        vTaskDelay(DHT22_REFRESHRATE/portTICK_RATE_MS);
		}
}



void space_mapping(void *prvParameters)
{
		static int i, direction=1;
		static  int number=(ANGLEmax/ANGLE);
		static float distance=0;
		int position = 0;
	
		int positionNum=ANGLEmax/ANGLE;
		float initial_map[number];
		float map[ANGLEmax/ANGLE];
		vTaskSuspendAll();
		int a = 5;
	
	
if  (TM_DISCO_ButtonPressed())//(a==1) 
	{
			GPIO_SetBits(LEDPORT, LED4PIN);

//			TM_DISCO_Reset_Button();

			TM_PWM_SetChannelMicros(&scanner_timer, SCANNER_CHANNEL, SCANNER_MIN);
			Delay(500000);	
			GPIO_ResetBits(LEDPORT, LED4PIN);
			Delay(1000000);
			a=2;
	}

int cnt=0;
	

		GPIO_SetBits(LEDPORT, LED2PIN);
	
		for (i=0;i<positionNum;i++) 
			{	
				initial_map[i] = TM_HCSR04_Read(&HCSR04);
				GPIO_ResetBits(LEDPORT, LED2PIN);
				
				TM_PWM_SetChannelMicros(&scanner_timer, SCANNER_CHANNEL, SCANNER_MIN+position);	
				Delay(500000);
				//move_positive();
				position+=ANGLE;
				cnt++;
			}
			
		position = ANGLEmax;
		direction = -1;
		sendInitialMap(&initial_map[0], positionNum);
		writeInitialMap(initial_map); //zapisivanje u flash
		xTaskResumeAll ();

		while(1)
		{		
			TM_PWM_SetChannelMicros(&buzzer_timer, BUZZER_CHANNEL, 50);	
			Delay(5000000);
			TM_PWM_SetChannelMicros(&buzzer_timer, BUZZER_CHANNEL, 0);	

			if (TM_DISCO_ButtonPressed())// (a==1) 
			{
				GPIO_SetBits(LEDPORT, LED4PIN);
				GPIO_SetBits(LEDPORT, LED3PIN);
//				TM_DISCO_Reset_Button();
			//postavi servo motor na pocetak
			  vTaskDelay(100/portTICK_RATE_MS);
		  	TM_PWM_SetChannelMicros(&scanner_timer, SCANNER_CHANNEL, SCANNER_MIN);
				Delay(500000);
		  	GPIO_ResetBits(LEDPORT, LED3PIN);
		    direction=1;
		   	a=3;
			 TM_PWM_SetChannelMicros(&scanner_timer, SCANNER_CHANNEL, SCANNER_MIDDLE);			
		}
		position=0;
			if(direction > 0)
			{
	
				for(i=0;i<positionNum;i++)
				{
						TM_PWM_SetChannelMicros(&scanner_timer, SCANNER_CHANNEL, SCANNER_MIN+position);
						Delay(500000);			// move_positive();  //Move the sensor in positive direction.
						map[i] = TM_HCSR04_Read(&HCSR04);		
						if(abs(map[i]-initial_map[i]) > DISTANCE_ERROR)		
						{		
							positionNum-=ANGLE;
							TM_PWM_SetChannelMicros(&scanner_timer, SCANNER_CHANNEL, SCANNER_MIN+position);
							if((abs(map[i])-initial_map[i]) > DISTANCE_ERROR)	
									TM_PWM_SetChannelMicros(&buzzer_timer, BUZZER_CHANNEL, 50);	
							
							Delay(5000000);
		          TM_PWM_SetChannelMicros(&buzzer_timer, BUZZER_CHANNEL, 0);
							position+=ANGLE;									
						}
					
				}					
			position+=ANGLE;									
			}
					
			else
			{	
				position=0;
				for(i=0;i<positionNum;i++)
				{
					
				TM_PWM_SetChannelMicros(&scanner_timer, SCANNER_CHANNEL, SCANNER_MAX+position);	// move_negative();  //Move the sensor in negative direction.
				map[i] = TM_HCSR04_Read(&HCSR04);	
				Delay(500000);
				if(abs(map[i]-initial_map[i]) > DISTANCE_ERROR)
				{				
					positionNum+=ANGLE;
					TM_PWM_SetChannelMicros(&scanner_timer, SCANNER_CHANNEL, SCANNER_MAX+position-ANGLE);
							
					if((abs(map[i]-initial_map[i])) > DISTANCE_ERROR)	
					TM_PWM_SetChannelMicros(&buzzer_timer, BUZZER_CHANNEL, 50);	
					
					Delay(5000000);
					TM_PWM_SetChannelMicros(&buzzer_timer, BUZZER_CHANNEL, 0);
					position-=ANGLE;
							//ALARM;
				}
					//provjerit jel došlo do greške, ako je vratit se korak nazad pa ponovno provjerit, možda je bila neka greška
					position-=ANGLE;		
					
				
				}
			}
					
			if(position >= ANGLEmax) //In final position change the direction of the motor.
			{
				direction=-direction;
				position=ANGLEmax;   
			}
			else if(position <= 0) //In final position change the direction of the motor.
			{
				direction=-direction;
				position=0;     
			}
	}
	 vTaskDelay(1000/portTICK_RATE_MS);
}

void rfid_task(void *prvParameters)
{
	static bool aux_flag=false;
	static uint32_t timerval=0;
	static uint8_t id[5];
	static User newUser;
	static User allUsers[MAX_USER];
	static uint8_t numberOfUsers = 0;

	numberOfUsers = initSuperUser(allUsers);
	writeSuperUser(allUsers);

//	 TM_PWM_SetChannelMicros(&buzzer_timer, BUZZER_CHANNEL, SERVO_MIN); //grant a
  while(1)
    {
        //checks if card is present
        if(TM_MFRC522_Check(id)==MI_OK){			
            //check if user is valid
            if(isUserValid(&allUsers[0], numberOfUsers, &id[0])){
                GPIO_SetBits(LEDPORT,LED1PIN);
							GPIO_SetBits(LEDPORT,LED3PIN);
							GPIO_SetBits(LEDPORT,LED4PIN);
                TM_PWM_SetChannelMicros(&servo_timer, SERVO_CHANNEL, SERVO_MIN); //grant access
                aux_flag=true;
                timerval=xTaskGetTickCount()/portTICK_RATE_MS;
            }
            else
                GPIO_SetBits(LEDPORT,LED3PIN); //red light for unauthorized user
        }
        else{
            GPIO_ResetBits(LEDPORT,LED3PIN | LED1PIN);
        }

        //prohibit enterance if timeout period expires
        if((xTaskGetTickCount()/portTICK_RATE_MS)-timerval > servo_const && aux_flag){
                TM_PWM_SetChannelMicros(&servo_timer, SERVO_CHANNEL, SERVO_MAX);

                aux_flag=false;
        }
				
        vTaskDelay(RFID_REFRESHRATE/portTICK_RATE_MS);
    }
		          GPIO_ResetBits(LEDPORT,LED1PIN);
							GPIO_ResetBits(LEDPORT,LED3PIN);
							GPIO_ResetBits(LEDPORT,LED4PIN);
}


