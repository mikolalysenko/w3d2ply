/*	Data types used in W3D files
	Based on information provided by Westwood Studios

	This file is part of W3DView
	W3DView is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
*/
typedef unsigned long uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef signed long sint32;
typedef signed short sint16;
typedef float float32;
typedef struct {
float32 X; float32 Y; float32 Z;
} IOVector3Struct;
typedef struct {
float32 Q[4];
} IOQuaternionStruct;
typedef struct {
uint32 x; uint32 y; uint32 z;
} Vector3i;
#define WWMATH_FLOAT_MAX FLT_MAX
