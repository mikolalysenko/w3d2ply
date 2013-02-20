/*	Global Definitions for W3DView
	Copyright 2004 Jonathan Wilson

	This file is part of W3DView
	W3DView is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
*/
extern uint32 TextureCount; //count of textures
extern W3dHLODStruct HLOD[2]; //the current HLOD
extern uint32 HLODLoaded; //has there been a HLOD loaded yet
extern W3dHierarchyDefStruct AnimationHierarchy[2]; //the Hierarchy holding animation data
extern W3dHierarchyDefStruct Hierarchy[2]; //the Hierarchy holding the skelleton data
extern uint32 HierarchyLoaded; //has there been a Hierarchy loaded yet
extern W3dMeshStruct *Mesh; //the currently loaded meshes
extern W3dAnimationStruct *Animation; //the currently loaded animations
extern uint32 MeshCount; //count of meshes loaded
extern uint32 AnimationCount; //count of animations loaded
extern void Initdefs(); //function to initialize global variables
extern uint32 ChunkCount; //total chunk count for the file
extern uint32 Frame; //current animation frame
extern float Zoom; //camera zoom value
extern uint32 BitFrame; //current visiblity frame
extern uint32 Rotate; //current camera view
extern float Pan; //horizontal camera value
extern float Tilt; //vertical camera value
extern float32 Speed; //current speed of vehicle
extern float32 Suspension; //suspension travel value
extern uint32 IsVehicle; //is this a vehicle model
static float RotateMat[6][16] = {{0,0,1,0,1,0,0,0,0,1,0,0,0,0,0,1},{0,0,-1,0,-1,0,0,0,0,1,0,0,0,0,0,1},{1,0,0,0,0,0,-1,0,0,1,0,0,0,0,0,1},{-1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1},{0,-1,0,0,1,0,0,0,0,0,1,0,0,0,0,1},{0,1,0,0,1,0,0,0,0,0,-1,0,0,0,0,1}}; //rotation matricies for the various camera views
