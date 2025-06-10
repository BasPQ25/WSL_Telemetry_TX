#include"main.h"

//extern variables, from main.c
extern CAN_HandleTypeDef hcan;
extern UART_HandleTypeDef huart1;
extern struct RTC_TIME RealTime[2];// 2 buffers
extern uint8_t First_Buffer_Flag;
extern uint8_t Second_Buffer_Flag;

uint8_t Dashboard_Rtc_Request = 0;

void USB_LP_CAN_RX0_IRQHandler(void)
{
	//Function variables
	static uint8_t dma_buffer[DMA_BUFFER_SIZE] = { 0 };
	static uint8_t *const p_buffer = (uint8_t *)&dma_buffer;
	static uint8_t dma_offset = 0;
	static union CanData can_data;
	static CAN_RxHeaderTypeDef header;

	HAL_CAN_IRQHandler(&hcan);

	HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &header,
				can_data.byte);

	if( header.StdId == DASHBOARD_TX_RTC_REQUEST )//Dashboard request for telemetry
	{
		Dashboard_Rtc_Request = 1; //enable transmit function in main
	}

	dma_buffer[UART_MSG_LEN * dma_offset +  0] = 0xFE; // Start padding

	dma_buffer[UART_MSG_LEN * dma_offset +  1] = (header.StdId & 0x000000FF) >> 0;
	dma_buffer[UART_MSG_LEN * dma_offset +  2] = (header.StdId & 0x0000FF00) >> 8;

	dma_buffer[UART_MSG_LEN * dma_offset +  3] = can_data.byte[0];
	dma_buffer[UART_MSG_LEN * dma_offset +  4] = can_data.byte[1];
	dma_buffer[UART_MSG_LEN * dma_offset +  5] = can_data.byte[2];
	dma_buffer[UART_MSG_LEN * dma_offset +  6] = can_data.byte[3];
	dma_buffer[UART_MSG_LEN * dma_offset +  7] = can_data.byte[4];
	dma_buffer[UART_MSG_LEN * dma_offset +  8] = can_data.byte[5];
	dma_buffer[UART_MSG_LEN * dma_offset +  9] = can_data.byte[6];
	dma_buffer[UART_MSG_LEN * dma_offset + 10] = can_data.byte[7];

	if( First_Buffer_Flag == 0 )
	{
		dma_buffer[UART_MSG_LEN * dma_offset + 11] = RealTime[0].seconds;
		dma_buffer[UART_MSG_LEN * dma_offset + 12] = RealTime[0].minutes;
		dma_buffer[UART_MSG_LEN * dma_offset + 13] = RealTime[0].hour;
		dma_buffer[UART_MSG_LEN * dma_offset + 14] = RealTime[0].dayofmonth;
	}
	else if( Second_Buffer_Flag == 0 )
	{
		dma_buffer[UART_MSG_LEN * dma_offset + 11] = RealTime[1].seconds;
		dma_buffer[UART_MSG_LEN * dma_offset + 12] = RealTime[1].minutes;
		dma_buffer[UART_MSG_LEN * dma_offset + 13] = RealTime[1].hour;
		dma_buffer[UART_MSG_LEN * dma_offset + 14] = RealTime[1].dayofmonth;
	}

	 	dma_buffer[UART_MSG_LEN * dma_offset + 15] = 0x7F; // End padding

	 if (++dma_offset == DMA_UART_MSG_CNT)
	 {
	 	dma_offset = 0;
	     HAL_UART_Transmit_DMA(&huart1, p_buffer, DMA_BUFFER_SIZE);
	 }


}
