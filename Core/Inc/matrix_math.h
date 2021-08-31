/*
 * matrix_math.h
 *
 *  Created on: May 23, 2021
 *
 */

#ifndef INC_MATRIX_MATH_H_
#define INC_MATRIX_MATH_H_

#include <vector>

using namespace std;
using matrix =  vector<vector<float>>;	//Vector data type
using matrix_1D = vector<float>;

matrix operator +(matrix p, matrix q);
matrix operator -(matrix p, matrix q);
matrix operator *(matrix p, matrix q);
matrix operator /(matrix p, matrix q);
matrix inverse (matrix p);
matrix transpose (matrix p);

#endif /* INC_MATRIX_MATH_H_ */
