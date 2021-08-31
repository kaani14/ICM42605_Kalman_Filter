/*
 * matrix_math.cpp
 *
 *  Created on: May 23, 2021
 *
 */

#include "matrix_math.h"

using namespace std;
extern int vector_size;

//operators
//Addition operation
matrix operator +(matrix p, matrix q)
{
	matrix t(vector_size , matrix_1D (vector_size, 0));
	for (int i = 0; i<vector_size; i++)
	{
		for (int j = 0; j<vector_size; j++)
			t[i][j] = (p[i][j]+q[i][j]);
	}
		return t;
}

//Difference operator
matrix operator -(matrix p, matrix q)
{
	matrix t( vector_size , matrix_1D (vector_size, 0));
	for (int i = 0; i<vector_size; i++)
	{
		for (int j = 0; j<vector_size; j++)
			t[i][j] = (p[i][j]-q[i][j]);
	}
		return t;
}

////multiplication operator
matrix operator*(matrix Mat_1, matrix Mat_2)
{

	matrix Mat_3( vector_size , matrix_1D (vector_size, 0));
    for(int i=0; i<vector_size;i++)
    {
        for(int j=0;j<vector_size;j++)
        {
            Mat_3[i][j] = 0;

            for(int k=0;k<vector_size;k++)
				Mat_3[i][j] += Mat_1[i][k] * Mat_2[k][j];

        }
    }

	return Mat_3;
}


//Inverse of a diagonal matrix
matrix inverse (matrix p)
{
	matrix t( 2 , matrix_1D (2, 0));

	for (int i = 0; i<vector_size; i++)
	{
		for (int j = 0; j<vector_size; j++)
			if (p[i][j] == 0)
				t[i][j] = 0;
			else
				t[i][j] = (1/p[i][j]);
	}
		return t;
}

matrix transpose (matrix p)
{
	matrix t( vector_size , matrix_1D (vector_size, 0));
	for (int i = 0; i<vector_size; i++)
	{
		for (int j = 0; j<vector_size; j++)
			t[i][j] = p[j][i];
	}

		return t;
}
