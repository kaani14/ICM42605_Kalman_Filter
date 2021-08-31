/*
 * Kalman.cpp
 *
 *  Created on: May 23, 2021
 *
 */

#include "kalman.h"
#include "assert.h"
#include "math.h"

Kalman::Kalman(matrix Q, matrix A, matrix B, matrix x_e, matrix p_e, matrix I, matrix H)
{
	Q_ = Q;
	A_ = A;
	B_ = B;
	x_e_ = x_e;
	p_e_ = p_e;
	I_ = I;
	H_ = H;
};

Kalman::~Kalman(){};

void Kalman::Prediction(matrix U)
{
    x_p_ = A_ * x_e_ + (B_ * U);
    p_p_ = A_ * p_e_ * transpose(A_) + Q_;
}

void Kalman::KalmanGain(matrix R)
{
  S_ = H_ * p_p_ * transpose(H_) + R;
  K_G_ = p_p_ * transpose(H_) *  inverse(S_);		//S is a diagonal matrix
}

void Kalman::Update(matrix P)
{
  x_e_ = x_p_ + K_G_ * (P - x_p_);
  p_e_ = (I_ - (K_G_ * H_)) * p_p_;
}

kf_math::kf_math()
{
	i_ = 0;
	sum_ = 0;
	window_ = 0;
	readings_[100] = {0};
	mean_ = 0;
}

kf_math::~kf_math(){};

float kf_math::variance(float data_, int window_)
{
  sqDiff_ = 0;
  sum_ = sum_ - readings_[i_];
  readings_[i_] = data_;
  sum_ = sum_ + data_;
  mean_ = (float)sum_ / (float)window_;		//Mean


  i_++;
  if (i_ == window_ - 1)
 	  i_ = 0;

  for (int j = 0; j<window_; j++)
	  sqDiff_ += (readings_[j] - mean_) * (readings_[j] - mean_);


  return sqDiff_/window_;
}
