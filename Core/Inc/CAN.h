/*
 * CAN.h
 *
 *  Created on: May 8, 2025
 *      Author: paulb
 */

#ifndef INC_CAN_H_
#define INC_CAN_H_

#define UART_MSG_LEN (16)
#define DMA_UART_MSG_CNT (20)
#define DMA_BUFFER_SIZE (UART_MSG_LEN * DMA_UART_MSG_CNT)
#define CAN_MSG_LEN (8)
#define CRC_LEN (((CAN_MSG_LEN) * (sizeof(uint8_t))) / (sizeof(uint32_t)))

union CanData{
  uint8_t byte[CAN_MSG_LEN];
  uint32_t word[CRC_LEN];
};

#define RTC_HEADER            0x110
#define ACTIVITY_CHECK        0x130
#define DASHBOARD_TX_RTC_REQUEST 0x310

void Transmit_RTC_To_Dashboard();

#endif /* INC_CAN_H_ */
