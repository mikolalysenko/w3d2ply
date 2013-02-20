/*	Global Definitions for W3DView
	Copyright 2004 Jonathan Wilson

	This file is part of W3DView
	W3DView is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
*/
#include "w3d.h"
W3dHLODStruct HLOD[2]; //the current HLOD
uint32 HLODLoaded = 0; //has there been a HLOD loaded yet
W3dHierarchyDefStruct AnimationHierarchy[2]; //the Hierarchy holding animation data
W3dHierarchyDefStruct Hierarchy[2]; //the Hierarchy holding the skelleton data
uint32 HierarchyLoaded = 0; //has there been a Hierarchy loaded yet
W3dMeshStruct *Mesh = NULL; //the currently loaded meshes
W3dAnimationStruct *Animation = NULL; //the currently loaded animations
uint32 MeshCount = 0; //count of meshes loaded
uint32 AnimationCount = 0; //count of animations loaded
uint32 ChunkCount = 0; //total chunk count
uint32 Frame = 0; //current animation frame
uint32 BitFrame = 0; //current visiblity frame
uint32 IsVehicle = 0; //is this a vehicle model
float Zoom = 0; //camera zoom value
float Pan = 0; //horizontal camera value
float Tilt = 0; //vertical camera value
uint32 Rotate = 0; //current camera view
float32 Speed = 0; //current speed of vehicle
float32 Suspension = 0; //suspension travel value

/*
Function to initalize the global defnions
inputs: none
outputs: none
*/
void Initdefs()
{
	memset(&HLOD,0,sizeof(W3dHLODStruct));
	memset(&AnimationHierarchy,0,sizeof(W3dHierarchyDefStruct)*2);
	memset(&Hierarchy,0,sizeof(W3dHierarchyDefStruct)*2);
}
