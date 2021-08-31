/*
 * Kalman.h
 *
 *  Created on: May 21, 2021
 *
 */

#pragma once
#ifndef INC_KALMAN_H_
#define INC_KALMAN_H_
#include "matrix_math.h"

class Kalman
{

	public:

		Kalman(matrix Q_, matrix A_, matrix B_, matrix x_e_,matrix p_e_, matrix I_, matrix H);
		~Kalman();

		matrix x_e_;

		void Prediction(matrix U);
		void KalmanGain(matrix R);
		void Update(matrix P);
		void Reset();

	private:

		matrix A_, B_;
		matrix S_;
		matrix p_u_;
	    matrix Q_;
	    matrix I_;
	    matrix p_e_;
	    matrix p_p_, x_p_, K_G_, H_;
};


class kf_math{

  public:
	kf_math();
	~kf_math();
    float variance(float data,int window);


    int i_;
    float mean_, sum_;
    float sqDiff_;
    int window_;
    float readings_[100];

};
#endif /* INC_KALMAN_H_ */
