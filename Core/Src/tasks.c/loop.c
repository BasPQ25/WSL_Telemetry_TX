#include"main.h"

extern I2C_HandleTypeDef hi2c1;
extern struct RTC_TIME RealTime[2];

uint8_t First_Buffer_Flag = 0;
uint8_t Second_Buffer_Flag = 0;

void Loop()
{
	 if( HAL_I2C_IsDeviceReady(&hi2c1, DS323_ADRESS, 10, 100) != HAL_OK)
		  {
			  HAL_I2C_DeInit(&hi2c1);
			  HAL_Delay(10);
			  HAL_I2C_Init(&hi2c1);
		  }

		  GetTime( &First_Buffer_Flag , &RealTime[0] );
		  GetTime( &Second_Buffer_Flag, &RealTime[1] );
}
