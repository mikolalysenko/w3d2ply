/*	Functions for dealing with matrix and quaternion data
	Copyright 2004 Jonathan Wilson

	This file is part of W3DView
	W3DView is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
*/
#include "w3d.h"
/*
Function to multiply 2 matricies
inputs: matricies to multiply
outputs: result matrix
*/
void MatrixMultiply(float32 Matrix1[16], float32 Matrix2[16], float32 Dest[16])
{
	Dest[0] = (Matrix1[0] * Matrix2[0]) + (Matrix1[1] * Matrix2[4]) + (Matrix1[2] * Matrix2[8]) + (Matrix1[3] * Matrix2[12]);
	Dest[1] = (Matrix1[0] * Matrix2[1]) + (Matrix1[1] * Matrix2[5]) + (Matrix1[2] * Matrix2[9]) + (Matrix1[3] * Matrix2[13]);
	Dest[2] = (Matrix1[0] * Matrix2[2]) + (Matrix1[1] * Matrix2[6]) + (Matrix1[2] * Matrix2[10]) + (Matrix1[3] * Matrix2[14]);
	Dest[3] = (Matrix1[0] * Matrix2[3]) + (Matrix1[1] * Matrix2[7]) + (Matrix1[2] * Matrix2[11]) + (Matrix1[3] * Matrix2[15]);
	Dest[4] = (Matrix1[4] * Matrix2[0]) + (Matrix1[5] * Matrix2[4]) + (Matrix1[6] * Matrix2[8]) + (Matrix1[7] * Matrix2[12]);
	Dest[5] = (Matrix1[4] * Matrix2[1]) + (Matrix1[5] * Matrix2[5]) + (Matrix1[6] * Matrix2[9]) + (Matrix1[7] * Matrix2[13]);
	Dest[6] = (Matrix1[4] * Matrix2[2]) + (Matrix1[5] * Matrix2[6]) + (Matrix1[6] * Matrix2[10]) + (Matrix1[7] * Matrix2[14]);
	Dest[7] = (Matrix1[4] * Matrix2[3]) + (Matrix1[5] * Matrix2[7]) + (Matrix1[6] * Matrix2[11]) + (Matrix1[7] * Matrix2[15]);
	Dest[8] = (Matrix1[8] * Matrix2[0]) + (Matrix1[9] * Matrix2[4]) + (Matrix1[10] * Matrix2[8]) + (Matrix1[11] * Matrix2[12]);
	Dest[9] = (Matrix1[8] * Matrix2[1]) + (Matrix1[9] * Matrix2[5]) + (Matrix1[10] * Matrix2[9]) + (Matrix1[11] * Matrix2[13]);
	Dest[10] = (Matrix1[8] * Matrix2[2]) + (Matrix1[9] * Matrix2[6]) + (Matrix1[10] * Matrix2[10]) + (Matrix1[11] * Matrix2[14]);
	Dest[11] = (Matrix1[8] * Matrix2[3]) + (Matrix1[9] * Matrix2[7]) + (Matrix1[10] * Matrix2[11]) + (Matrix1[11] * Matrix2[15]);
	Dest[12] = (Matrix1[12] * Matrix2[0]) + (Matrix1[13] * Matrix2[4]) + (Matrix1[14] * Matrix2[8]) + (Matrix1[15] * Matrix2[12]);
	Dest[13] = (Matrix1[12] * Matrix2[1]) + (Matrix1[13] * Matrix2[5]) + (Matrix1[14] * Matrix2[9]) + (Matrix1[15] * Matrix2[13]);
	Dest[14] = (Matrix1[12] * Matrix2[2]) + (Matrix1[13] * Matrix2[6]) + (Matrix1[14] * Matrix2[10]) + (Matrix1[15] * Matrix2[14]);
	Dest[15] = (Matrix1[12] * Matrix2[3]) + (Matrix1[13] * Matrix2[7]) + (Matrix1[14] * Matrix2[11]) + (Matrix1[15] * Matrix2[15]);
}
/*
Function to multiply a matrix and a vector
inputs: matrix and vector to multiply
outputs: result vector
*/
void MatrixMultiplyVector(W3dVectorStruct *Vector, float32 Matrix[16], W3dVectorStruct *Dest)
{
	Dest->X = (Vector->X * Matrix[0]) + (Vector->Y * Matrix[1]) + (Vector->Z * Matrix[2]) + (1 * Matrix[3]);
	Dest->Y = (Vector->X * Matrix[4]) + (Vector->Y * Matrix[5]) + (Vector->Z * Matrix[6]) + (1 * Matrix[7]);
	Dest->Z = (Vector->X * Matrix[8]) + (Vector->Y * Matrix[9]) + (Vector->Z * Matrix[10]) + (1 * Matrix[11]);
}
/*
Function to convert a quaternion into a matrix
inputs: quaternion
outputs: result matrix
*/
void QuatToMatrix(W3dQuaternionStruct Quat, float32 Matrix[16])
{
	float32 X2, Y2, Z2;
	float32 XX2, YY2, ZZ2;
	float32 XY2, XZ2, XW2;
	float32 YZ2, YW2, ZW2;

	X2 = 2.0f * Quat.Q[0];
	XX2 = X2 * Quat.Q[0];
	XY2 = X2 * Quat.Q[1];
	XZ2 = X2 * Quat.Q[2];
	XW2 = X2 * Quat.Q[3];

	Y2 = 2.0f * Quat.Q[1];
	YY2 = Y2 * Quat.Q[1];
	YZ2 = Y2 * Quat.Q[2];
	YW2 = Y2 * Quat.Q[3];
	
	Z2 = 2.0f * Quat.Q[2];
	ZZ2 = Z2 * Quat.Q[2];
	ZW2 = Z2 * Quat.Q[3];
	
	Matrix[0] = 1.0f - YY2 - ZZ2;
	Matrix[1] = XY2 - ZW2;
	Matrix[2] = XZ2 + YW2;

	Matrix[4] = XY2 + ZW2;
	Matrix[5] = 1.0f - XX2 - ZZ2;
	Matrix[6] = YZ2 - XW2;

	Matrix[8] = XZ2 - YW2;
	Matrix[9] = YZ2 + XW2;
	Matrix[10] = 1.0f - XX2 - YY2;

	Matrix[3] = 0;
	Matrix[7] = 0;
	Matrix[11] = 0;
	Matrix[12] = 0;
	Matrix[13] = 0;
	Matrix[14] = 0;
	Matrix[15] = 1;
}
