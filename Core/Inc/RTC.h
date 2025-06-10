/*
 * RTC.h
 *
 *  Created on: May 5, 2025
 *      Author: paulb
 */

#ifndef INC_RTC_H_
#define INC_RTC_H_

struct RTC_TIME
{
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hour;
	uint8_t dayofweek;
	uint8_t dayofmonth;
	uint8_t month;
	uint8_t year;
};

#define PRINTF_TESTING 0
#define DS323_ADRESS 0xD0

void RTC_handler(void);

void SetTime( uint8_t sec, uint8_t min, uint8_t hour, uint8_t dow, uint8_t dom, uint8_t month, uint8_t year);
void GetTime( uint8_t* FillingFlag, struct RTC_TIME* RealTime );

uint8_t DecToBcd(int val);
int BcdToDec(uint8_t val);




#endif /* INC_RTC_H_ */
