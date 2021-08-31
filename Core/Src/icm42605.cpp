/*
 *icm42605.cpp
 *
 *  Created on: May 23, 2021
 *
 */

#include <icm42605.h>
#include "main.h"
#include <math.h>
extern I2C_HandleTypeDef hi2c1;

ICM42605::ICM42605()
{
	gyro_cal = {0, 0};
}

ICM42605::~ICM42605()
{

}


void ICM42605::Init()
{

	  uint8_t data;

	  data = 0x2F;	//Sensor wake-up. Power-management register
	  HAL_I2C_Mem_Write (&hi2c1, ICM_ADDR, 0x4E, 1, &data, 1, 1000);
	  HAL_Delay(2);

	  data = 0x46;	//Configure Gyro Range, +/- 500dps
	  HAL_I2C_Mem_Write (&hi2c1, ICM_ADDR, 0x4F, 1, &data, 1, 1000);
	  HAL_Delay(2);

	  data = 0x26;	//Configure Acc Range, +/- 8g
	  HAL_I2C_Mem_Write (&hi2c1, ICM_ADDR, 0x50, 1, &data, 1, 1000);
	  HAL_Delay(2);
}

//Read acceleration and calculate orientation
void  ICM42605::ReadAcc()
{
	uint8_t acc_data[6];

	HAL_I2C_Mem_Read(&hi2c1, ICM_ADDR, 0x1F, 1, acc_data, 6, 1000);

	acc_raw_data_ = {
						(int16_t)(acc_data[0] << 8 | acc_data[1]),
						(int16_t)(acc_data[2] << 8 | acc_data[3]),
						(int16_t)(acc_data[4] << 8 | acc_data[5])
					};

	float acc_total_vector = sqrt((acc_raw_data_[0] * acc_raw_data_[0]) + (acc_raw_data_[1] * acc_raw_data_[1]) + (acc_raw_data_[2] * acc_raw_data_[2]));

	acc_ = 	{
				{-asin((float)acc_raw_data_[0] / acc_total_vector), 0},
				{ 0, asin((float)acc_raw_data_[1] / acc_total_vector)}
			};
}

void  ICM42605::GyroCalibrate()			//average of first 2000 readings
{
	//sum of first 2000 readings
	for (int i = 0; i < 2000; i++)
	{
		ReadGyro();
		for (int k = 0; k <2; k++)
			gyro_cal[k] +=gyro_raw_data[k];
		HAL_Delay(3);
	}

	//divide by 2000
	for(int i=0; i<2; i++)
		gyro_cal[i] = gyro_cal[i] / 2000;

	gyro_calibration_flag_ = true;
}

//Read Gyro
void  ICM42605::ReadGyro()
{
	uint8_t gyro_data[6];

	HAL_I2C_Mem_Read(&hi2c1, ICM_ADDR, 0x25, 1, gyro_data, 6, 1000);

	gyro_raw_data =	{
						((int16_t)(gyro_data[0] << 8 | gyro_data [1])),
						((int16_t)(gyro_data[2] << 8 | gyro_data [3]))
					};

	gyro_ = {
				{(gyro_raw_data[1] - gyro_cal[1]) / 65.5f / 57.296f, 0},
				{0, (gyro_raw_data[0] - gyro_cal[0]) / 65.5f / 57.296f}
			};			//65.5, gyro configuration, from datasheet
						//57.296, conversion to radians
}
