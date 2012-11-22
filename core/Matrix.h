#ifndef MATRIX_H
#define	MATRIX_H

#include "Vector3.h"

class Matrix
{
public:
	double indices[3][3];
	Matrix()
	{
		indices[0][0] = 1;
		indices[0][1] = 0;
		indices[0][2] = 0;
		//
		indices[1][0] = 0;
		indices[1][1] = 1;
		indices[1][2] = 0;
		//
		indices[2][0] = 0;
		indices[2][1] = 0;
		indices[2][2] = 1;
	}
	
	void SetRotationX(double x)
	{
		indices[0][0] = 1;
		indices[0][1] = 0;
		indices[0][2] = 0;
		//
		indices[1][0] = 0;
		indices[1][1] = cos(x);
		indices[1][2] = -sin(x);
		//
		indices[2][0] = 0;
		indices[2][1] = sin(x);
		indices[2][2] = cos(x);
	}
	
	void SetRotationY(double x)
	{
		indices[0][0] = cos(x);
		indices[0][1] = 0;
		indices[0][2] = sin(x);
		//
		indices[1][0] = 0;
		indices[1][1] = 1;
		indices[1][2] = 0;
		//
		indices[2][0] = -sin(x);
		indices[2][1] = 0;
		indices[2][2] = cos(x);
	}
	
	void SetRotationZ(double x)
	{
		indices[0][0] = cos(x);
		indices[0][1] = -sin(x);
		indices[0][2] = 0;
		//
		indices[1][0] = sin(x);
		indices[1][1] = cos(x);
		indices[1][2] = 0;
		//
		indices[2][0] = 0;
		indices[2][1] = 0;
		indices[2][2] = 1;
	}
	
	Matrix operator*(Vector3 v)
	{
		Vector3 ret = *this;
		ret.x = indices[0][0]*v.x+indices[0][1]*v.y+indices[0][2]*v.z;
		ret.y = indices[1][0]*v.x+indices[1][1]*v.y+indices[1][2]*v.z;
		ret.z = indices[2][0]*v.x+indices[2][1]*v.y+indices[2][2]*v.z;
		return ret;
	}
	
	Matrix operator*(Matrix m)
	{
		Matrix ret;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
			{
				ret[j][i] = 0;
				for (int k = 0; k < 3; k++)
					ret[j][i] += indices[k][i]*m.indices[j][k];
			}
		return ret;
	}
};

#endif	/* MATRIX_H */

