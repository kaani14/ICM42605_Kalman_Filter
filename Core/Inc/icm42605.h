/*
 * icm42605.h
 *
 *  Created on: Jul 3, 2021
 *
 */

#ifndef INC_ICM42605_H_
#define INC_ICM42605_H_

#include "matrix_math.h"
#include <cstdint>

using namespace std;

using int16_t_matrix = vector<int16_t>;

class ICM42605
{
	public:
		ICM42605();
		~ICM42605();
		matrix gyro_, acc_;
		void Init();
		void ReadAcc();
		void GyroCalibrate();
		void ReadGyro();
		bool gyro_calibration_flag_;

	private:
		static const uint8_t ICM_ADDR = 0x69 << 1;	//Sensor address
		matrix_1D gyro_cal;
		int16_t_matrix acc_raw_data_;
		int16_t_matrix gyro_raw_data;
};



#endif /* INC_ICM42605_H_ */
