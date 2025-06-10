#include"main.h"

struct RTC_TIME RealTime[2];// 2 buffers

extern I2C_HandleTypeDef hi2c1;

void SetTime( uint8_t sec, uint8_t min, uint8_t hour, uint8_t dow, uint8_t dom, uint8_t month, uint8_t year)
{
	uint8_t set_time[7];
	set_time[0] = DecToBcd(sec);
	set_time[1] = DecToBcd(min);
	set_time[2] = DecToBcd(hour);
	set_time[3] = DecToBcd(dow);
	set_time[4] = DecToBcd(dom);
	set_time[5] = DecToBcd(month);
	set_time[6] = DecToBcd(year);

	HAL_I2C_Mem_Write(&hi2c1, DS323_ADRESS, 0x00, 1, set_time, 7, 1000);
}

void GetTime( uint8_t* FillingFlag, struct RTC_TIME* RealTime )
{
	*FillingFlag = 1;

	uint8_t get_time[7] = {0};

	HAL_I2C_Mem_Read(&hi2c1,DS323_ADRESS , 0x00, 1, get_time, 7, 1000);

	RealTime->seconds    = BcdToDec(get_time[0]);
	RealTime->minutes    = BcdToDec(get_time[1]);
	RealTime->hour       = BcdToDec(get_time[2]);
	RealTime->dayofweek  = BcdToDec(get_time[3]);
	RealTime->dayofmonth = BcdToDec(get_time[4]);
	RealTime->month      = BcdToDec(get_time[5]);
	RealTime->year       = BcdToDec(get_time[6]);

	*FillingFlag = 0;
}

uint8_t DecToBcd(int val)
{
	return (uint8_t)( (val/10*16) + (val%10) );
}

int BcdToDec(uint8_t val)
{
	return (int)( (val/16*10) + ( val%16) );
}
