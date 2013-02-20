/*	Data Structures for stoing the data from W3D files
	Origonally provided by Westwood Studios, some modifications to make things compile in C done by Jonathan Wilson

	This file is part of W3DView
	W3DView is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
*/
//Structure for holding data about a material
typedef struct 
{
	char *Name;
	W3dVertexMaterialStruct VertexMaterialInfo;
	char *MapperArgs0;
	char *MapperArgs1;
	float32 UPerSec;
	float32 VPerSec;
	float32 CurrentU;
	float32 CurrentV;
} W3dMaterialStruct;
//Structure for holding information about a texture
typedef struct 
{
	char *Name;
	uint32 TextureInfoLoaded;
	W3dTextureInfoStruct TextureInfo;
} W3dTextureStruct;
//Structure for holding information about a texture stage
typedef struct 
{
	uint32 TextureIDCount;
	uint32 *TextureIDs;
	W3dTexCoordStruct *TexCoords;
	uint32 PerFaceTexCoordIDCount;
	Vector3i *PerFaceTexCoordIDs;
} W3dTextureStageStruct;
//Structure for describing a material pass
typedef struct 
{
	uint32 *VertexMaterialIDs;
	uint32 VertexMaterialIDCount;
	uint32 *ShaderIDs;
	uint32 ShaderIDCount;
	W3dRGBAStruct *DCG;
	W3dRGBAStruct *DIG;
	W3dRGBAStruct *SCG;
	uint32 StageCount;
	W3dTextureStageStruct TextureStage[2];
} W3dMaterialPassStruct;
typedef struct 
{
	W3dMeshHeader3Struct Header;
	W3dVectorStruct *Vertices;
	W3dVectorStruct *Normals;
	W3dVertInfStruct *Influences;
	W3dTriStruct *Triangles;
	uint32 *ShadeIndices;
	W3dMaterialInfoStruct MaterialInfo;
	W3dMaterialStruct *Materials;
	W3dShaderStruct *Shaders;
	W3dTextureStruct *Textures;
	W3dMaterialPassStruct *MaterialPass;
} W3dMeshStruct;
typedef struct 
{
	W3dHierarchyStruct Header;
	W3dPivotStruct *Pivots;
	float32 *RotateMatrix;
	uint32 *Visible;
} W3dHierarchyDefStruct;
typedef struct
{
	W3dAnimChannelStruct Header;
	float32 *Data;
} W3dAnimChannelDefStruct;
typedef struct
{
	W3dBitChannelStruct Header;
	uint8 *Data;
} W3dBitChannelDefStruct;
typedef struct 
{
	W3dAnimHeaderStruct Header;
	uint32 W3dAnimChannelCount;
	uint32 W3dBitChannelCount;
	W3dAnimChannelDefStruct *AnimationChannels;
	W3dBitChannelDefStruct *BitChannels;
} W3dAnimationStruct;
typedef struct 
{
	W3dHLodArrayHeaderStruct Header;
	W3dHLodSubObjectStruct *SubObjects;
} W3dLODArrayStruct;
typedef struct 
{
	W3dHLodHeaderStruct Header;
	W3dLODArrayStruct *LODs;
} W3dHLODStruct;
