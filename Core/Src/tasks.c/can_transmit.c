#include"main.h"

//extern variables, from main.c
extern CAN_HandleTypeDef hcan;
extern struct RTC_TIME RealTime[2];// 2 buffers
extern TIM_HandleTypeDef htim2;
extern uint8_t First_Buffer_Flag;
extern uint8_t Second_Buffer_Flag;

static uint8_t telemetry_data[8] = { 0 };

void TIM2_IRQHandler(void) //Activity Check, always transmits at 100ms
{
  /* USER CODE BEGIN TIM1_CC_IRQn 0 */

	static const CAN_TxHeaderTypeDef Activity_Header =
	{ ACTIVITY_CHECK, 0x00, CAN_RTR_DATA, CAN_ID_STD, 8, DISABLE };
	static uint32_t Activity_mailbox;

  /* USER CODE END TIM1_CC_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM1_CC_IRQn 1 */
  if( First_Buffer_Flag == 0 )
  {
	  telemetry_data[0] = RealTime[0].seconds;
	  telemetry_data[1] = RealTime[0].minutes;
	  telemetry_data[2] = RealTime[0].hour;
	  telemetry_data[3] = RealTime[0].dayofweek;
	  telemetry_data[4] = RealTime[0].dayofmonth;
	  telemetry_data[5] = RealTime[0].month;
  }
  else if( Second_Buffer_Flag == 0 )
  {
	  telemetry_data[0] = RealTime[1].seconds;
	  telemetry_data[1] = RealTime[1].minutes;
	  telemetry_data[2] = RealTime[1].hour;
	  telemetry_data[3] = RealTime[1].dayofweek;
	  telemetry_data[4] = RealTime[1].dayofmonth;
	  telemetry_data[5] = RealTime[1].month;
  }
  HAL_CAN_AddTxMessage(&hcan, &Activity_Header, telemetry_data, &Activity_mailbox);


  /* USER CODE END TIM1_CC_IRQn 1 */
}
