/*	Functions for handling W3D file bone/hierarchy data
	Copyright 2004 Jonathan Wilson

	This file is part of W3DView
	W3DView is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
*/
#include "w3d.h"
/* 
Function for calculating the current transformation matrix for a given bone
inputs: bone index to calculate for, memory to hold transformation data, hierarchy to use
output: calculated transformation data, visibility flag
Note that if the mesh is invisible, no transformation calculations will be performed
*/
uint32 CalculateBoneTransform(uint32 PivotIdx,float32 Transform[16],uint32 HierarchyNo)
{
	sint32 Count;
	float32 Temp[16];
	float32 Translate[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
	uint32 *PivotArray;
	uint32 CurrentPivot = PivotIdx;
	uint32 PivotCount = 0;
	PivotCount++;
	PivotArray = (uint32*)malloc(PivotCount*sizeof(uint32));
	PivotArray[PivotCount-1] = CurrentPivot;
	if (AnimationHierarchy[HierarchyNo].Visible[CurrentPivot] == 0)
	{
		return 0;
	}
	while (AnimationHierarchy[HierarchyNo].Pivots[CurrentPivot].ParentIdx != -1)
	{
		CurrentPivot = AnimationHierarchy[HierarchyNo].Pivots[CurrentPivot].ParentIdx;
		PivotCount++;
		PivotArray = (uint32*)realloc(PivotArray,PivotCount*sizeof(uint32));
		PivotArray[PivotCount-1] = CurrentPivot;
	}
	Translate[3] = Hierarchy[HierarchyNo].Pivots[PivotArray[PivotCount-1]].Translation.X;
	Translate[7] = Hierarchy[HierarchyNo].Pivots[PivotArray[PivotCount-1]].Translation.Y;
	Translate[11] = Hierarchy[HierarchyNo].Pivots[PivotArray[PivotCount-1]].Translation.Z;
	memcpy(Transform,&Translate,(sizeof(float32)*16));
	MatrixMultiply(Transform,&Hierarchy[HierarchyNo].RotateMatrix[PivotArray[PivotCount-1]*16],Temp);
	memcpy(Transform,&Temp,(sizeof(float32)*16));
	Translate[3] = AnimationHierarchy[HierarchyNo].Pivots[PivotArray[PivotCount-1]].Translation.X;
	Translate[7] = AnimationHierarchy[HierarchyNo].Pivots[PivotArray[PivotCount-1]].Translation.Y;
	Translate[11] = AnimationHierarchy[HierarchyNo].Pivots[PivotArray[PivotCount-1]].Translation.Z;
	MatrixMultiply(Transform,Translate,Temp);
	memcpy(Transform,&Temp,(sizeof(float32)*16));
	MatrixMultiply(Transform,&AnimationHierarchy[HierarchyNo].RotateMatrix[PivotArray[PivotCount-1]*16],Temp);
	memcpy(Transform,&Temp,(sizeof(float32)*16));
	for (Count=PivotCount-2;Count>=0;Count--)
	{
		Translate[3] = Hierarchy[HierarchyNo].Pivots[PivotArray[Count]].Translation.X;
		Translate[7] = Hierarchy[HierarchyNo].Pivots[PivotArray[Count]].Translation.Y;
		Translate[11] = Hierarchy[HierarchyNo].Pivots[PivotArray[Count]].Translation.Z;
		MatrixMultiply(Transform,Translate,Temp);
		memcpy(Transform,&Temp,(sizeof(float32)*16));
		MatrixMultiply(Transform,&Hierarchy[HierarchyNo].RotateMatrix[PivotArray[Count]*16],Temp);
		memcpy(Transform,&Temp,(sizeof(float32)*16));
		Translate[3] = AnimationHierarchy[HierarchyNo].Pivots[PivotArray[Count]].Translation.X;
		Translate[7] = AnimationHierarchy[HierarchyNo].Pivots[PivotArray[Count]].Translation.Y;
		Translate[11] = AnimationHierarchy[HierarchyNo].Pivots[PivotArray[Count]].Translation.Z;
		MatrixMultiply(Transform,Translate,Temp);
		memcpy(Transform,&Temp,(sizeof(float32)*16));
		MatrixMultiply(Transform,&AnimationHierarchy[HierarchyNo].RotateMatrix[PivotArray[Count]*16],Temp);
		memcpy(Transform,&Temp,(sizeof(float32)*16));
	}
	return 1;
}
