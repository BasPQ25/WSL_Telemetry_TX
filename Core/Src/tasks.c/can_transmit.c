#include"main.h"

//extern variables, from main.c
extern CAN_HandleTypeDef hcan;
extern struct RTC_TIME RealTime[2];// 2 buffers
extern TIM_HandleTypeDef htim2;

void Transmit_RTC_To_Dashboard()
{
		static uint8_t telemetry_data[8] = { 0 };
		static const CAN_TxHeaderTypeDef RTC_Header =
		{ RTC_HEADER, 0x00, CAN_RTR_DATA, CAN_ID_STD, 8, DISABLE };
		static uint32_t RTC_mailbox;

		//both buffers are finished, so it's not relevant which one to collect data from
		telemetry_data[0] = RealTime[1].seconds;
		telemetry_data[1] = RealTime[1].minutes;
		telemetry_data[2] = RealTime[1].hour;
		telemetry_data[3] = RealTime[1].dayofweek;
		telemetry_data[4] = RealTime[1].dayofmonth;

		HAL_CAN_AddTxMessage(&hcan, &RTC_Header, telemetry_data, &RTC_mailbox);

}

void TIM2_IRQHandler(void) //Activity Check, always transmits at 100ms
{
  /* USER CODE BEGIN TIM1_CC_IRQn 0 */

	static const CAN_TxHeaderTypeDef Activity_Header =
	{ ACTIVITY_CHECK, 0x00, CAN_RTR_DATA, CAN_ID_STD, 8, DISABLE };
	static uint32_t Activity_mailbox;

  /* USER CODE END TIM1_CC_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM1_CC_IRQn 1 */
   HAL_CAN_AddTxMessage(&hcan, &Activity_Header, 0x00, &Activity_mailbox);


  /* USER CODE END TIM1_CC_IRQn 1 */
}
