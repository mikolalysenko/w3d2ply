/*	Functions for dealing with matrix and quaternion data
	Copyright 2004 Jonathan Wilson

	This file is part of W3DView
	W3DView is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
*/
void MatrixMultiply(float32 Matrix1[16], float32 Matrix2[16], float32 Dest[16]); //multiply 2 matricies
void MatrixMultiplyVector(W3dVectorStruct *Vector, float32 Matrix[16], W3dVectorStruct *Dest); //multiply a matrix and a vector
void QuatToMatrix(W3dQuaternionStruct Quat, float32 Matrix[16]); //convert a quaternion into a matrix
