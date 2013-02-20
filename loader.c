/*	Functions for loading W3D files into the internal data structures
	Copyright 2004 Jonathan Wilson

	This file is part of W3DView
	W3DView is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2, or (at your option) any later
	version. See the file COPYING for more details.
*/
#include "w3d.h"
/*
Function to load a W3D Material
inputs: memory for a W3dMaterialStruct, file handle to read data from and size of material chunk
outputs: loaded material struct
*/
void LoadW3dMaterialStruct(W3dMaterialStruct *Material, FILE *Input, uint32 ChunkSize)
{
	W3dChunkHeader CurrentChunk;
	uint32 LoadedSize = 0;
	unsigned int Count;
	do {
		LoadedSize += sizeof(CurrentChunk);
		fread(&CurrentChunk,sizeof(CurrentChunk),1,Input);
		CurrentChunk.ChunkSize &= 0x7FFFFFFF;
		LoadedSize += CurrentChunk.ChunkSize;
		switch (CurrentChunk.ChunkType) {
		case W3D_CHUNK_VERTEX_MATERIAL_NAME:
			Material->Name = (char *)malloc(CurrentChunk.ChunkSize);
			memset(Material->Name,0,CurrentChunk.ChunkSize);
			fread(Material->Name,CurrentChunk.ChunkSize,1,Input);
			break;
		case W3D_CHUNK_VERTEX_MAPPER_ARGS0:
			Material->MapperArgs0 = (char *)malloc(CurrentChunk.ChunkSize);
			memset(Material->MapperArgs0,0,CurrentChunk.ChunkSize);
			fread(Material->MapperArgs0,CurrentChunk.ChunkSize,1,Input);
			break;
		case W3D_CHUNK_VERTEX_MAPPER_ARGS1:
			Material->MapperArgs1 = (char *)malloc(CurrentChunk.ChunkSize);
			memset(Material->MapperArgs1,0,CurrentChunk.ChunkSize);
			fread(Material->MapperArgs1,CurrentChunk.ChunkSize,1,Input);
			break;
		case W3D_CHUNK_VERTEX_MATERIAL_INFO:
			fread(&Material->VertexMaterialInfo,sizeof(Material->VertexMaterialInfo),1,Input);
			break;
		default:
			for (Count = 0;Count < (CurrentChunk.ChunkSize);Count++)
			{
				fgetc(Input);
			}
			break;
		}
	} while (LoadedSize < ChunkSize);
}
/*
Function to load a W3D Texure
inputs: memory for a W3dTextureStruct, file handle to read data from and size of texture chunk
outputs: loaded texture struct
*/
void LoadW3dTextureStruct(W3dTextureStruct *Texture, FILE *Input, uint32 ChunkSize)
{
	W3dChunkHeader CurrentChunk;
	uint32 LoadedSize = 0;
	unsigned int Count;
	do {
		LoadedSize += sizeof(CurrentChunk);
		fread(&CurrentChunk,sizeof(CurrentChunk),1,Input);
		CurrentChunk.ChunkSize &= 0x7FFFFFFF;
		LoadedSize += CurrentChunk.ChunkSize;
		switch (CurrentChunk.ChunkType) {
		case W3D_CHUNK_TEXTURE_NAME:
			Texture->Name = (char *)malloc(CurrentChunk.ChunkSize);
			memset(Texture->Name,0,CurrentChunk.ChunkSize);
			fread(Texture->Name,CurrentChunk.ChunkSize,1,Input);
			break;
		case W3D_CHUNK_TEXTURE_INFO:
			fread(&Texture->TextureInfo,sizeof(Texture->TextureInfo),1,Input);
			Texture->TextureInfoLoaded = 1;
			break;
		default:
			for (Count = 0;Count < (CurrentChunk.ChunkSize);Count++)
			{
				fgetc(Input);
			}
			break;
		}
	} while (LoadedSize < ChunkSize);
}
/*
Function to load a W3D Texure Stage
inputs: memory for a W3dTextureStageStruct, file handle to read data from and size of texture stage chunk
outputs: loaded texture stage struct
*/
void LoadW3dTextureStageStruct(W3dTextureStageStruct *TextureStage, FILE *Input, uint32 ChunkSize)
{
	W3dChunkHeader CurrentChunk;
	uint32 LoadedSize = 0;
	unsigned int Count;
	do {
		LoadedSize += sizeof(CurrentChunk);
		fread(&CurrentChunk,sizeof(CurrentChunk),1,Input);
		CurrentChunk.ChunkSize &= 0x7FFFFFFF;
		LoadedSize += CurrentChunk.ChunkSize;
		switch (CurrentChunk.ChunkType) {
		case W3D_CHUNK_TEXTURE_IDS:
			TextureStage->TextureIDCount = CurrentChunk.ChunkSize / sizeof(uint32);
			TextureStage->TextureIDs = (uint32*)malloc(TextureStage->TextureIDCount*sizeof(uint32));
			memset(TextureStage->TextureIDs,0,TextureStage->TextureIDCount*sizeof(uint32));
			for (Count = 0;Count < TextureStage->TextureIDCount;Count++)
			{
				fread(&TextureStage->TextureIDs[Count],sizeof(uint32),1,Input);
			}
			break;
		case W3D_CHUNK_PER_FACE_TEXCOORD_IDS:
			TextureStage->PerFaceTexCoordIDCount = CurrentChunk.ChunkSize / sizeof(uint32);
			TextureStage->PerFaceTexCoordIDs = (Vector3i*)malloc(TextureStage->PerFaceTexCoordIDCount*sizeof(Vector3i));
			memset(TextureStage->PerFaceTexCoordIDs,0,TextureStage->PerFaceTexCoordIDCount*sizeof(Vector3i));
			for (Count = 0;Count < TextureStage->PerFaceTexCoordIDCount;Count++)
			{
				fread(&TextureStage->PerFaceTexCoordIDs[Count],sizeof(Vector3i),1,Input);
			}
			break;
		case W3D_CHUNK_STAGE_TEXCOORDS:
			TextureStage->TexCoords = (W3dTexCoordStruct*)malloc(CurrentChunk.ChunkSize);
			memset(TextureStage->TexCoords,0,CurrentChunk.ChunkSize);
			for (Count = 0;Count < CurrentChunk.ChunkSize / sizeof(W3dTexCoordStruct);Count++)
			{
				fread(&TextureStage->TexCoords[Count],sizeof(W3dTexCoordStruct),1,Input);
			}
			break;
		default:
			for (Count = 0;Count < (CurrentChunk.ChunkSize);Count++)
			{
				fgetc(Input);
			}
			break;
		}
	} while (LoadedSize < ChunkSize);
}
/*
Function to load a W3D Material Pass
inputs: memory for a W3dMaterialPassStruct, file handle to read data from and size of material pass chunk
outputs: loaded material pass struct
*/
void LoadW3dMaterialPassStruct(W3dMaterialPassStruct *Pass, FILE *Input, uint32 ChunkSize)
{
	W3dChunkHeader CurrentChunk;
	uint32 LoadedSize = 0;
	unsigned int Count;
	do {
		LoadedSize += sizeof(CurrentChunk);
		fread(&CurrentChunk,sizeof(CurrentChunk),1,Input);
		CurrentChunk.ChunkSize &= 0x7FFFFFFF;
		LoadedSize += CurrentChunk.ChunkSize;
		switch (CurrentChunk.ChunkType) {
		case W3D_CHUNK_VERTEX_MATERIAL_IDS:
			Pass->VertexMaterialIDCount = CurrentChunk.ChunkSize / sizeof(uint32);
			Pass->VertexMaterialIDs = (uint32*)malloc(Pass->VertexMaterialIDCount*sizeof(uint32));
			memset(Pass->VertexMaterialIDs,0,Pass->VertexMaterialIDCount*sizeof(uint32));
			for (Count = 0;Count < Pass->VertexMaterialIDCount;Count++)
			{
				fread(&Pass->VertexMaterialIDs[Count],sizeof(uint32),1,Input);
			}
			break;
		case W3D_CHUNK_SHADER_IDS:
			Pass->ShaderIDCount = CurrentChunk.ChunkSize / sizeof(uint32);
			Pass->ShaderIDs = (uint32*)malloc(Pass->ShaderIDCount*sizeof(uint32));
			memset(Pass->ShaderIDs,0,Pass->ShaderIDCount*sizeof(uint32));
			for (Count = 0;Count < Pass->ShaderIDCount;Count++)
			{
				fread(&Pass->ShaderIDs[Count],sizeof(uint32),1,Input);
			}
			break;
		case W3D_CHUNK_DCG:
			Pass->DCG = (W3dRGBAStruct*)malloc(CurrentChunk.ChunkSize);
			memset(Pass->DCG,0,CurrentChunk.ChunkSize);
			for (Count = 0;Count < CurrentChunk.ChunkSize / sizeof(W3dRGBAStruct);Count++)
			{
				fread(&Pass->DCG[Count],sizeof(W3dRGBAStruct),1,Input);
			}
			break;
		case W3D_CHUNK_DIG:
			Pass->DIG = (W3dRGBAStruct*)malloc(CurrentChunk.ChunkSize);
			memset(Pass->DIG,0,CurrentChunk.ChunkSize);
			for (Count = 0;Count < CurrentChunk.ChunkSize / sizeof(W3dRGBAStruct);Count++)
			{
				fread(&Pass->DIG[Count],sizeof(W3dRGBAStruct),1,Input);
			}
			break;
		case W3D_CHUNK_SCG:
			Pass->SCG = (W3dRGBAStruct*)malloc(CurrentChunk.ChunkSize);
			memset(Pass->SCG,0,CurrentChunk.ChunkSize);
			for (Count = 0;Count < CurrentChunk.ChunkSize / sizeof(W3dRGBAStruct);Count++)
			{
				fread(&Pass->SCG[Count],sizeof(W3dRGBAStruct),1,Input);
			}
			break;
		case W3D_CHUNK_TEXTURE_STAGE:
			Pass->StageCount++;
			LoadW3dTextureStageStruct(&Pass->TextureStage[Pass->StageCount-1],Input,CurrentChunk.ChunkSize);
			break;
		default:
			for (Count = 0;Count < (CurrentChunk.ChunkSize);Count++)
			{
				fgetc(Input);
			}
			break;
		}
	} while (LoadedSize < ChunkSize);
}
/*
Function to load a W3D Mesh
inputs: memory for a W3dMeshStruct, file handle to read data from and size of mesh chunk
outputs: loaded mesh struct
*/
void LoadW3dMeshStruct(W3dMeshStruct *Mesh, FILE *Input, uint32 ChunkSize)
{
	W3dChunkHeader CurrentChunk;
	int CurrentMaterialPass = 0;
	uint32 LoadedSize = 0;
	unsigned int Count;
	do {
		LoadedSize += sizeof(CurrentChunk);
		fread(&CurrentChunk,sizeof(CurrentChunk),1,Input);
		CurrentChunk.ChunkSize &= 0x7FFFFFFF;
		LoadedSize += CurrentChunk.ChunkSize;
		switch (CurrentChunk.ChunkType) {
		case W3D_CHUNK_MESH_HEADER3:
			fread(&Mesh->Header,sizeof(Mesh->Header),1,Input);
			Mesh->Vertices = (W3dVectorStruct*)malloc(sizeof(W3dVectorStruct)*Mesh->Header.NumVertices);
			memset(Mesh->Vertices,0,sizeof(W3dVectorStruct)*Mesh->Header.NumVertices);
			Mesh->Normals = (W3dVectorStruct*)malloc(sizeof(W3dVectorStruct)*Mesh->Header.NumVertices);
			memset(Mesh->Normals,0,sizeof(W3dVectorStruct)*Mesh->Header.NumVertices);
			Mesh->ShadeIndices = (uint32*)malloc(sizeof(uint32)*Mesh->Header.NumVertices);
			memset(Mesh->ShadeIndices,0,sizeof(uint32)*Mesh->Header.NumVertices);
			Mesh->Triangles = (W3dTriStruct*)malloc(sizeof(W3dTriStruct)*Mesh->Header.NumTris);
			memset(Mesh->Triangles,0,sizeof(W3dTriStruct)*Mesh->Header.NumTris);
			Mesh->Influences = (W3dVertInfStruct*)malloc(sizeof(W3dVertInfStruct)*Mesh->Header.NumVertices);
			memset(Mesh->Influences,0,sizeof(W3dVertInfStruct)*Mesh->Header.NumVertices);
			break;
		case W3D_CHUNK_VERTICES:
			for (Count = 0;Count < Mesh->Header.NumVertices;Count++)
			{
				fread(&Mesh->Vertices[Count],sizeof(Mesh->Vertices[Count]),1,Input);
			}
			break;
		case W3D_CHUNK_VERTEX_NORMALS:
			for (Count = 0;Count < Mesh->Header.NumVertices;Count++)
			{
				fread(&Mesh->Normals[Count],sizeof(Mesh->Normals[Count]),1,Input);
			}
			break;
		case W3D_CHUNK_VERTEX_INFLUENCES:
			for (Count = 0;Count < Mesh->Header.NumVertices;Count++)
			{
				fread(&Mesh->Influences[Count],sizeof(Mesh->Influences[Count]),1,Input);
			}
			break;
		case W3D_CHUNK_TRIANGLES:
			for (Count = 0;Count < Mesh->Header.NumTris;Count++)
			{
				fread(&Mesh->Triangles[Count],sizeof(Mesh->Triangles[Count]),1,Input);
			}
			break;
		case W3D_CHUNK_VERTEX_SHADE_INDICES:
			for (Count = 0;Count < Mesh->Header.NumVertices;Count++)
			{
				fread(&Mesh->ShadeIndices[Count],sizeof(Mesh->ShadeIndices[Count]),1,Input);
			}
			break;
		case W3D_CHUNK_MATERIAL_INFO:
			fread(&Mesh->MaterialInfo,sizeof(Mesh->MaterialInfo),1,Input);
			Mesh->Materials = (W3dMaterialStruct*)malloc(sizeof(W3dMaterialStruct)*Mesh->MaterialInfo.VertexMaterialCount);
			memset(Mesh->Materials,0,sizeof(W3dMaterialStruct)*Mesh->MaterialInfo.VertexMaterialCount);
			Mesh->Shaders = (W3dShaderStruct*)malloc(sizeof(W3dShaderStruct)*Mesh->MaterialInfo.ShaderCount);
			memset(Mesh->Shaders,0,sizeof(W3dShaderStruct)*Mesh->MaterialInfo.ShaderCount);
			Mesh->Textures = (W3dTextureStruct*)malloc(sizeof(W3dTextureStruct)*Mesh->MaterialInfo.TextureCount);
			memset(Mesh->Textures,0,sizeof(W3dTextureStruct)*Mesh->MaterialInfo.TextureCount);
			Mesh->MaterialPass = (W3dMaterialPassStruct*)malloc(sizeof(W3dMaterialPassStruct)*Mesh->MaterialInfo.PassCount);
			memset(Mesh->MaterialPass,0,sizeof(W3dMaterialPassStruct)*Mesh->MaterialInfo.PassCount);
			break;
		case W3D_CHUNK_VERTEX_MATERIALS:
			for (Count = 0;Count < Mesh->MaterialInfo.VertexMaterialCount;Count++)
			{
				fread(&CurrentChunk,sizeof(CurrentChunk),1,Input);
				CurrentChunk.ChunkSize &= 0x7FFFFFFF;
				if (CurrentChunk.ChunkType == W3D_CHUNK_VERTEX_MATERIAL)
				{
					LoadW3dMaterialStruct(&Mesh->Materials[Count],Input,CurrentChunk.ChunkSize);
				}
				else
				{
					for (Count = 0;Count < (CurrentChunk.ChunkSize);Count++)
					{
						fgetc(Input);
					}
				}
			}
			break;
		case W3D_CHUNK_SHADERS:
			for (Count = 0;Count < Mesh->MaterialInfo.ShaderCount;Count++)
			{
				fread(&Mesh->Shaders[Count],sizeof(Mesh->Shaders[Count]),1,Input);
			}
			break;
		case W3D_CHUNK_TEXTURES:
			for (Count = 0;Count < Mesh->MaterialInfo.TextureCount;Count++)
			{
				fread(&CurrentChunk,sizeof(CurrentChunk),1,Input);
				CurrentChunk.ChunkSize &= 0x7FFFFFFF;
				if (CurrentChunk.ChunkType == W3D_CHUNK_TEXTURE)
				{
					LoadW3dTextureStruct(&Mesh->Textures[Count],Input,CurrentChunk.ChunkSize);
				}
				else
				{
					for (Count = 0;Count < (CurrentChunk.ChunkSize);Count++)
					{
						fgetc(Input);
					}
				}
			}
			break;
		case W3D_CHUNK_MATERIAL_PASS:
			LoadW3dMaterialPassStruct(&Mesh->MaterialPass[CurrentMaterialPass],Input,CurrentChunk.ChunkSize);
			CurrentMaterialPass++;
			break;
		default:
			for (Count = 0;Count < (CurrentChunk.ChunkSize);Count++)
			{
				fgetc(Input);
			}
			break;
		}
	} while (LoadedSize < ChunkSize);
}
/*
Function to load a W3D Hierarchy
inputs: memory for a W3dHierarchyDefStruct for the Hierarchy, memory for a W3dHierarchyDefStruct for the animation Hierarchy, file handle to read data from and size of Hierarchy chunk
outputs: loaded Hierarchy struct
*/
void LoadW3dHierarchyDefStruct(W3dHierarchyDefStruct *AnimationHierarchy, W3dHierarchyDefStruct *Hierarchy, FILE *Input, uint32 ChunkSize)
{
	W3dChunkHeader CurrentChunk;
	uint32 LoadedSize = 0;
	float32 Trans[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
	unsigned int Count;
	do {
		LoadedSize += sizeof(CurrentChunk);
		fread(&CurrentChunk,sizeof(CurrentChunk),1,Input);
		CurrentChunk.ChunkSize &= 0x7FFFFFFF;
		LoadedSize += CurrentChunk.ChunkSize;
		switch (CurrentChunk.ChunkType) {
		case W3D_CHUNK_HIERARCHY_HEADER:
			fread(&AnimationHierarchy->Header,sizeof(AnimationHierarchy->Header),1,Input);
			memcpy(&Hierarchy->Header,&AnimationHierarchy->Header,sizeof(Hierarchy->Header));
			AnimationHierarchy->Pivots = (W3dPivotStruct*)malloc(AnimationHierarchy->Header.NumPivots*sizeof(W3dPivotStruct));
			AnimationHierarchy->RotateMatrix = (float32*)malloc(AnimationHierarchy->Header.NumPivots*sizeof(float32)*16);
			AnimationHierarchy->Visible = (uint32*)malloc(AnimationHierarchy->Header.NumPivots*sizeof(uint32));
			Hierarchy->Pivots = (W3dPivotStruct*)malloc(Hierarchy->Header.NumPivots*sizeof(W3dPivotStruct));
			Hierarchy->RotateMatrix = (float32*)malloc(Hierarchy->Header.NumPivots*sizeof(float32)*16);
			Hierarchy->Visible = (uint32*)malloc(Hierarchy->Header.NumPivots*sizeof(uint32));
			memset(AnimationHierarchy->Pivots,0,AnimationHierarchy->Header.NumPivots*sizeof(W3dPivotStruct));
			memset(AnimationHierarchy->RotateMatrix,0,AnimationHierarchy->Header.NumPivots*sizeof(float32)*16);
			memset(AnimationHierarchy->Visible,1,AnimationHierarchy->Header.NumPivots*sizeof(uint32));
			memset(Hierarchy->Pivots,0,Hierarchy->Header.NumPivots*sizeof(W3dPivotStruct));
			memset(Hierarchy->RotateMatrix,0,Hierarchy->Header.NumPivots*sizeof(float32)*16);
			memset(Hierarchy->Visible,1,Hierarchy->Header.NumPivots*sizeof(uint32));
			break;
		case W3D_CHUNK_PIVOTS:
			for (Count = 0;Count < AnimationHierarchy->Header.NumPivots;Count++)
			{
				fread(&AnimationHierarchy->Pivots[Count],sizeof(AnimationHierarchy->Pivots[Count]),1,Input);
				memcpy(&Hierarchy->Pivots[Count],&AnimationHierarchy->Pivots[Count],sizeof(Hierarchy->Pivots[Count]));
				AnimationHierarchy->Pivots[Count].Translation.X = 0;
				AnimationHierarchy->Pivots[Count].Translation.Y = 0;
				AnimationHierarchy->Pivots[Count].Translation.Z = 0;
				QuatToMatrix(Hierarchy->Pivots[Count].Rotation,&Hierarchy->RotateMatrix[Count*16]);
				memcpy(&AnimationHierarchy->RotateMatrix[Count*16],&Trans,sizeof(float32)*16);
		}
			break;
		default:
			for (Count = 0;Count < (CurrentChunk.ChunkSize);Count++)
			{
				fgetc(Input);
			}
			break;
		}
	} while (LoadedSize < ChunkSize);
}
/*
Function to load a W3D LOD array
inputs: memory for a W3dLodArrayStruct, file handle to read data from and size of LOD array chunk
outputs: loaded LOD array struct
*/
void LoadW3dLODArrayStruct(W3dLODArrayStruct *LODArray, FILE *Input, uint32 ChunkSize)
{
	W3dChunkHeader CurrentChunk;
	uint32 LoadedSize = 0;
	uint32 CurrentSubObject = 0;
	unsigned int Count;
	do {
		LoadedSize += sizeof(CurrentChunk);
		fread(&CurrentChunk,sizeof(CurrentChunk),1,Input);
		CurrentChunk.ChunkSize &= 0x7FFFFFFF;
		LoadedSize += CurrentChunk.ChunkSize;
		switch (CurrentChunk.ChunkType) {
		case W3D_CHUNK_HLOD_SUB_OBJECT_ARRAY_HEADER:
			fread(&LODArray->Header,sizeof(LODArray->Header),1,Input);
			LODArray->SubObjects = (W3dHLodSubObjectStruct*)malloc(sizeof(W3dHLodSubObjectStruct)*LODArray->Header.ModelCount);
			memset(LODArray->SubObjects,0,sizeof(W3dHLodSubObjectStruct)*LODArray->Header.ModelCount);
			break;
		case W3D_CHUNK_HLOD_SUB_OBJECT:
			fread(&LODArray->SubObjects[CurrentSubObject],sizeof(LODArray->SubObjects[CurrentSubObject]),1,Input);
			CurrentSubObject++;
			break;
		default:
			for (Count = 0;Count < (CurrentChunk.ChunkSize);Count++)
			{
				fgetc(Input);
			}
			break;
		}
	} while (LoadedSize < ChunkSize);
}
/*
Function to load a W3D HLOD
inputs: memory for a W3dHLODStruct, file handle to read data from and size of HLOD chunk
outputs: loaded HLOD struct
*/
void LoadW3dHLODStruct(W3dHLODStruct *HLOD, FILE *Input, uint32 ChunkSize)
{
	W3dChunkHeader CurrentChunk;
	uint32 LoadedSize = 0;
	unsigned int Count;
	unsigned int CurrentLODArray = 0;
	do {
		LoadedSize += sizeof(CurrentChunk);
		fread(&CurrentChunk,sizeof(CurrentChunk),1,Input);
		CurrentChunk.ChunkSize &= 0x7FFFFFFF;
		LoadedSize += CurrentChunk.ChunkSize;
		switch (CurrentChunk.ChunkType) {
		case W3D_CHUNK_HLOD_HEADER:
			fread(&HLOD->Header,sizeof(HLOD->Header),1,Input);
			HLOD->LODs = (W3dLODArrayStruct*)malloc(sizeof(W3dLODArrayStruct)*HLOD->Header.LodCount);
			memset(HLOD->LODs,0,sizeof(W3dLODArrayStruct)*HLOD->Header.LodCount);
			break;
		case W3D_CHUNK_HLOD_LOD_ARRAY:
			LoadW3dLODArrayStruct(&HLOD->LODs[CurrentLODArray],Input,CurrentChunk.ChunkSize);
			CurrentLODArray++;
			break;
		default:
			for (Count = 0;Count < (CurrentChunk.ChunkSize);Count++)
			{
				fgetc(Input);
			}
			break;
		}
	} while (LoadedSize < ChunkSize);
}
/*
Function to load a W3D HModel (an older form of HLOD) and convert it into a HLOD
inputs: memory for a W3dHLODStruct, file handle to read data from and size of HModel chunk
outputs: loaded HLOD struct
*/
void LoadW3dHModelStruct(W3dHLODStruct *HLOD, FILE *Input, uint32 ChunkSize)
{
	W3dChunkHeader CurrentChunk;
	uint32 LoadedSize = 0;
	unsigned int Count;
	W3dHModelHeaderStruct Header;
	W3dHModelNodeStruct Node;
	uint32 CurrentNode = 0;
	do {
		LoadedSize += sizeof(CurrentChunk);
		fread(&CurrentChunk,sizeof(CurrentChunk),1,Input);
		CurrentChunk.ChunkSize &= 0x7FFFFFFF;
		LoadedSize += CurrentChunk.ChunkSize;
		switch (CurrentChunk.ChunkType) {
		case W3D_CHUNK_HMODEL_HEADER:
			fread(&Header,sizeof(Header),1,Input);
			strncpy(HLOD->Header.HierarchyName,Header.HierarchyName,W3D_NAME_LEN);
			strncpy(HLOD->Header.Name,Header.Name,W3D_NAME_LEN);
			HLOD->Header.LodCount = 1;
			HLOD->Header.Version = 65536;
			HLOD->LODs = (W3dLODArrayStruct*)malloc(sizeof(W3dLODArrayStruct));
			memset(HLOD->LODs,0,sizeof(W3dLODArrayStruct));
			HLOD->LODs[0].Header.MaxScreenSize = NO_MAX_SCREEN_SIZE;
			HLOD->LODs[0].Header.ModelCount = Header.NumConnections;
			HLOD->LODs[0].SubObjects = (W3dHLodSubObjectStruct*)malloc(sizeof(W3dHLodSubObjectStruct)*HLOD->LODs[0].Header.ModelCount);
			memset(HLOD->LODs[0].SubObjects,0,sizeof(W3dHLodSubObjectStruct)*HLOD->LODs[0].Header.ModelCount);
			break;
		case W3D_CHUNK_NODE:
		case W3D_CHUNK_SKIN_NODE:
		case W3D_CHUNK_COLLISION_NODE:
			fread(&Node,sizeof(Node),1,Input);
			HLOD->LODs[0].SubObjects[CurrentNode].BoneIndex = Node.PivotIdx;
			sprintf(HLOD->LODs[0].SubObjects[CurrentNode].Name,"%s.%s",HLOD->Header.Name,Node.RenderObjName);
			CurrentNode++;
			break;
		default:
			for (Count = 0;Count < (CurrentChunk.ChunkSize);Count++)
			{
				fgetc(Input);
			}
			break;
		}
	} while (LoadedSize < ChunkSize);
}
/*
Function to load a W3D Animation Channel
inputs: memory for a W3dAnimChannelDefStruct, file handle to read data from and size of anim channel chunk
outputs: loaded animation channel struct
*/
void LoadW3dAnimChannelDefStruct(W3dAnimChannelDefStruct *Channel, FILE *Input, uint32 ChunkSize)
{
	fread(&Channel->Header,sizeof(Channel->Header),1,Input);
	Channel->Data = malloc(ChunkSize - sizeof(Channel->Header));
	memset(Channel->Data,0,(Channel->Header.LastFrame - Channel->Header.FirstFrame + 1) * Channel->Header.VectorLen);
	fread(Channel->Data,ChunkSize - sizeof(Channel->Header),1,Input);
};
/*
Function to load a W3D Visibility Animation Channel
inputs: memory for a W3dBitChannelDefStruct, file handle to read data from and size of bit channel chunk
outputs: loaded visibiliyu animation channel struct
*/
void LoadW3dBitChannelDefStruct(W3dBitChannelDefStruct *Channel, FILE *Input, uint32 ChunkSize)
{
	uint32 Remainder,DataSize,DataCount;
	fread(&Channel->Header,sizeof(Channel->Header),1,Input);
	fseek(Input,-1,SEEK_CUR);
	DataCount = (Channel->Header.LastFrame - Channel->Header.FirstFrame + 1);
	DataSize = (DataCount / 8);
	Remainder = (DataCount % 8);
	if (Remainder != 0)
	{
		DataSize++;
	}
	Channel->Data = malloc(DataSize);
	memset(Channel->Data,0,DataSize);
	fread(Channel->Data,DataSize,1,Input);
};
/*
Function to load a W3D Animation
inputs: memory for a W3dAnimationStruct, file handle to read data from and size of animation chunk
outputs: loaded animation struct
*/
void LoadW3dAnimationStruct(W3dAnimationStruct *Animation, FILE *Input, uint32 ChunkSize)
{
	W3dChunkHeader CurrentChunk;
	uint32 LoadedSize = 0;
	unsigned int Count;
	do {
		LoadedSize += sizeof(CurrentChunk);
		fread(&CurrentChunk,sizeof(CurrentChunk),1,Input);
		CurrentChunk.ChunkSize &= 0x7FFFFFFF;
		LoadedSize += CurrentChunk.ChunkSize;
		switch (CurrentChunk.ChunkType) {
		case W3D_CHUNK_ANIMATION_HEADER:
			fread(&Animation->Header,sizeof(Animation->Header),1,Input);
			break;
		case W3D_CHUNK_ANIMATION_CHANNEL:
			Animation->W3dAnimChannelCount++;
			if (Animation->AnimationChannels == NULL)
			{
				Animation->AnimationChannels = malloc(Animation->W3dAnimChannelCount*sizeof(W3dAnimChannelDefStruct));
			}
			else
			{
				Animation->AnimationChannels = realloc(Animation->AnimationChannels,Animation->W3dAnimChannelCount*sizeof(W3dAnimChannelDefStruct));
			}
			memset(&Animation->AnimationChannels[Animation->W3dAnimChannelCount-1],0,sizeof(W3dAnimChannelDefStruct));
			LoadW3dAnimChannelDefStruct(&Animation->AnimationChannels[Animation->W3dAnimChannelCount-1],Input,CurrentChunk.ChunkSize);
			break;
		case W3D_CHUNK_BIT_CHANNEL:
			Animation->W3dBitChannelCount++;
			if (Animation->BitChannels == NULL)
			{
				Animation->BitChannels = malloc(Animation->W3dBitChannelCount*sizeof(W3dBitChannelDefStruct));
			}
			else
			{
				Animation->BitChannels = realloc(Animation->BitChannels,Animation->W3dBitChannelCount*sizeof(W3dBitChannelDefStruct));
			}
			memset(&Animation->BitChannels[Animation->W3dBitChannelCount-1],0,sizeof(W3dBitChannelDefStruct));
			LoadW3dBitChannelDefStruct(&Animation->BitChannels[Animation->W3dBitChannelCount-1],Input,CurrentChunk.ChunkSize);
			break;
		default:
			for (Count = 0;Count < (CurrentChunk.ChunkSize);Count++)
			{
				fgetc(Input);
			}
			break;
		}
	} while (LoadedSize < ChunkSize);
}
/*
Function to load a W3D file from a FILE *
inputs: file handle to read from, size of w3d file data
outputs: none
*/
void LoadW3d(FILE *Input, uint32 FileSize)
{
	unsigned int Count;
	unsigned int LoadedSize = 0;
	W3dChunkHeader CurrentChunk;
	do {
		ChunkCount++;
		LoadedSize += sizeof(CurrentChunk);
		fread(&CurrentChunk,sizeof(CurrentChunk),1,Input);
		CurrentChunk.ChunkSize &= 0x7FFFFFFF;
		LoadedSize += CurrentChunk.ChunkSize;
		switch (CurrentChunk.ChunkType) {
		case W3D_CHUNK_MESH:
			MeshCount++;
			if (Mesh == NULL)
			{
				Mesh = malloc(MeshCount*sizeof(W3dMeshStruct));
			}
			else
			{
				Mesh = realloc(Mesh,MeshCount*sizeof(W3dMeshStruct));
			}
			memset(&Mesh[MeshCount-1],0,sizeof(W3dMeshStruct));
			LoadW3dMeshStruct(&Mesh[MeshCount-1],Input,CurrentChunk.ChunkSize);
			break;
		case W3D_CHUNK_HIERARCHY:
			if (HierarchyLoaded == 0)
			{
				LoadW3dHierarchyDefStruct(&AnimationHierarchy[0],&Hierarchy[0],Input,CurrentChunk.ChunkSize);
				HierarchyLoaded = 1;
			}
			else
			{
				LoadW3dHierarchyDefStruct(&AnimationHierarchy[1],&Hierarchy[1],Input,CurrentChunk.ChunkSize);
			}
			break;
		case W3D_CHUNK_ANIMATION:
			AnimationCount++;
			if (Animation == NULL)
			{
				Animation = malloc(AnimationCount*sizeof(W3dAnimationStruct));
			}
			else
			{
				Animation = realloc(Animation,AnimationCount*sizeof(W3dAnimationStruct));
			}
			memset(&Animation[AnimationCount-1],0,sizeof(W3dAnimationStruct));
			LoadW3dAnimationStruct(&Animation[AnimationCount-1],Input,CurrentChunk.ChunkSize);
			break;
		case W3D_CHUNK_HMODEL:
			if (HLODLoaded == 0)
			{
				LoadW3dHModelStruct(&HLOD[0],Input,CurrentChunk.ChunkSize);
				HLODLoaded = 1;
			}
			else
			{
				LoadW3dHModelStruct(&HLOD[1],Input,CurrentChunk.ChunkSize);
			}
			break;
		case W3D_CHUNK_HLOD:
			if (HLODLoaded == 0)
			{
				LoadW3dHLODStruct(&HLOD[0],Input,CurrentChunk.ChunkSize);
				HLODLoaded = 1;
			}
			else
			{
				LoadW3dHLODStruct(&HLOD[1],Input,CurrentChunk.ChunkSize);
			}
			break;
		default:
			for (Count = 0;Count < (CurrentChunk.ChunkSize);Count++)
			{
				fgetc(Input);
			}
			break;
		}
	} while (LoadedSize < FileSize);
}
/*
Function to load a W3D file from a disk file
inputs: filename to load
outputs: none
*/
void LoadW3dFromFile(char *Filename)
{
	unsigned int FileSize;
	FILE *Input = fopen(Filename,"rb");
	if (Input == NULL)
	{
		printf("File not found, %s",Filename);
		exit(1);
	}
	fseek(Input,0,SEEK_END);
	FileSize = ftell(Input);
	fseek(Input,0,SEEK_SET);
	LoadW3d(Input,FileSize);
	fclose(Input);
}
