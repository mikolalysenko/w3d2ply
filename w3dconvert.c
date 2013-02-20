#include <stdlib.h>
#include "w3d.h"


void convertMesh(W3dMeshStruct *mesh, FILE* fout) {

  //Write PLY header
  fprintf(fout,
    "ply\n"
    "format ascii 1.0\n"
    "comment w3d2ply converted %s\n"
    "element vertex %d\n"
    "property float x\n"
    "property float y\n"
    "property float z\n"
    "property float nx\n"
    "property float ny\n"
    "property float nz\n"
    "property list uchar float influences\n"
    "element faces %d\n"
    "property list uchar int vertex_index\n",
    
      mesh->Header.MeshName,
      mesh->Header.
  );

}

/*
void DisplayMesh(char *MeshName,float32 Transform[16],uint32 HierarchyNo)
{
	GLfloat Color[4];
	float32 TextureTrans[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
	W3dMeshStruct *Mesh = FindMesh(MeshName);
	W3dShaderStruct Shader;
	W3dMaterialStruct Material;
	W3dTexCoordStruct *TexCoords = NULL;
	W3dTriStruct CurrentTri;
	uint32 Load;
	uint32 Length;
	GLenum SrcAlpha;
	GLenum DstAlpha;
	uint32 Count;
	sint32 Count2;
	W3dVectorStruct Vertex1,Vertex2,Vertex3,Vertex1Trans,Vertex2Trans,Vertex3Trans,NormalTrans;
	if (Mesh == 0)
	{
		return;
	}
	if (((Mesh->Header.Attributes & W3D_MESH_FLAG_HIDDEN) == W3D_MESH_FLAG_HIDDEN) || (stricmp(MeshName,"BOUNDINGBOX") == 0))
	{
		return;
	}
	if ((Mesh->Header.Attributes & W3D_MESH_FLAG_TWO_SIDED) == W3D_MESH_FLAG_TWO_SIDED)
	{
		glDisable(GL_CULL_FACE);
	}
	else
	{
		glEnable(GL_CULL_FACE);
	}
	for (Count2 = Mesh->MaterialInfo.PassCount-1;Count2 >= 0;Count2--)
	{
		if (Mesh->MaterialPass[Count2].ShaderIDCount == 1)
		{
			Shader = Mesh->Shaders[Mesh->MaterialPass[Count2].ShaderIDs[0]];
			glDepthFunc(Shader.DepthCompare);
			if (Shader.DepthMask == 0)
			{
				glEnable(GL_DEPTH_TEST);
				glDepthMask(GL_FALSE);
			}
			else
			{
				glEnable(GL_DEPTH_TEST);
				glDepthMask(GL_TRUE);
			}
			switch (Shader.DestBlend)
			{
			case W3DSHADER_DESTBLENDFUNC_ZERO:
				DstAlpha = GL_ZERO;
				break;
			case W3DSHADER_DESTBLENDFUNC_ONE:
				DstAlpha = GL_ONE;
				break;
			case W3DSHADER_DESTBLENDFUNC_SRC_COLOR:
				DstAlpha = GL_SRC_COLOR;
				break;
			case W3DSHADER_DESTBLENDFUNC_ONE_MINUS_SRC_COLOR:
				glDepthMask(GL_TRUE);
				DstAlpha = GL_ONE_MINUS_SRC_COLOR;
				break;
			case W3DSHADER_DESTBLENDFUNC_SRC_ALPHA:
				DstAlpha = GL_SRC_ALPHA;
				break;
			case W3DSHADER_DESTBLENDFUNC_ONE_MINUS_SRC_ALPHA:
				DstAlpha = GL_ONE_MINUS_SRC_ALPHA;
				break;
			default:
				DstAlpha = W3DSHADER_DESTBLENDFUNC_DEFAULT;
				break;
			}
			switch (Shader.SrcBlend)
			{
			case W3DSHADER_SRCBLENDFUNC_ZERO:
				SrcAlpha = GL_ZERO;
				break;
			case W3DSHADER_SRCBLENDFUNC_ONE:
				SrcAlpha = GL_ONE;
				break;
			case W3DSHADER_SRCBLENDFUNC_SRC_ALPHA:
				SrcAlpha = GL_SRC_ALPHA;
				break;
			case W3DSHADER_SRCBLENDFUNC_ONE_MINUS_SRC_ALPHA:
				SrcAlpha = GL_ONE_MINUS_SRC_ALPHA;
				break;
			default:
				SrcAlpha = W3DSHADER_SRCBLENDFUNC_DEFAULT;
				break;
			}
			glBlendFunc(SrcAlpha,DstAlpha);
			if (Shader.AlphaTest == W3DSHADER_ALPHATEST_ENABLE)
			{
				glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
			}
		}
		if (Mesh->MaterialPass[Count2].VertexMaterialIDCount == 1)
		{
			Material = Mesh->Materials[Mesh->MaterialPass[Count2].VertexMaterialIDs[0]];
			Color[0] = Material.VertexMaterialInfo.Ambient.R/255.0;
			Color[1] = Material.VertexMaterialInfo.Ambient.G/255.0;
			Color[2] = Material.VertexMaterialInfo.Ambient.B/255.0;
			Color[3] = Material.VertexMaterialInfo.Opacity;
			glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,Color);
			Color[0] = Material.VertexMaterialInfo.Diffuse.R/255.0;
			Color[1] = Material.VertexMaterialInfo.Diffuse.G/255.0;
			Color[2] = Material.VertexMaterialInfo.Diffuse.B/255.0;
			Color[3] = Material.VertexMaterialInfo.Opacity;
			glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,Color);
			Color[0] = Material.VertexMaterialInfo.Specular.R/255.0;
			Color[1] = Material.VertexMaterialInfo.Specular.G/255.0;
			Color[2] = Material.VertexMaterialInfo.Specular.B/255.0;
			Color[3] = Material.VertexMaterialInfo.Opacity;
			glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,Color);
			Color[0] = Material.VertexMaterialInfo.Emissive.R/255.0;
			Color[1] = Material.VertexMaterialInfo.Emissive.G/255.0;
			Color[2] = Material.VertexMaterialInfo.Emissive.B/255.0;
			Color[3] = Material.VertexMaterialInfo.Opacity;
			glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Color);
			glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,Material.VertexMaterialInfo.Shininess);
			glMatrixMode(GL_TEXTURE);
			glLoadIdentity();
			TextureTrans[12] = Material.CurrentU;
			TextureTrans[13] = Material.CurrentV;
			glLoadMatrixf(TextureTrans);
			glMatrixMode(GL_MODELVIEW);
		}
		if (Mesh->MaterialPass[Count2].StageCount >= 1)
		{
			if (Mesh->MaterialPass[Count2].TextureStage->TextureIDCount == 1)
			{
				if (Mesh->MaterialPass[Count2].TextureStage->TextureIDs[0] != 0xFFFFFFFF)
				{
					Load = 0;
					Load = LoadTexture(Mesh->Textures[Mesh->MaterialPass[Count2].TextureStage->TextureIDs[0]].Name);
					if (Load == 0)
					{
						Length = strlen(Mesh->Textures[Mesh->MaterialPass[Count2].TextureStage->TextureIDs[0]].Name);
						Mesh->Textures[Mesh->MaterialPass[Count2].TextureStage->TextureIDs[0]].Name[Length-3] = 'd';
						Mesh->Textures[Mesh->MaterialPass[Count2].TextureStage->TextureIDs[0]].Name[Length-2] = 'd';
						Mesh->Textures[Mesh->MaterialPass[Count2].TextureStage->TextureIDs[0]].Name[Length-1] = 's';
						Load = LoadTexture(Mesh->Textures[Mesh->MaterialPass[Count2].TextureStage->TextureIDs[0]].Name);
						Mesh->Textures[Mesh->MaterialPass[Count2].TextureStage->TextureIDs[0]].Name[Length-3] = 't';
						Mesh->Textures[Mesh->MaterialPass[Count2].TextureStage->TextureIDs[0]].Name[Length-2] = 'g';
						Mesh->Textures[Mesh->MaterialPass[Count2].TextureStage->TextureIDs[0]].Name[Length-1] = 'a';
					}
					glEnable(GL_TEXTURE_2D);
				}
			}
			TexCoords = Mesh->MaterialPass[Count2].TextureStage->TexCoords;
		} 
		for (Count = 0;Count <Mesh->Header.NumTris;Count++)
		{
			CurrentTri = Mesh->Triangles[Count];
			Vertex1 = Mesh->Vertices[CurrentTri.Vindex[0]];
			Vertex2 = Mesh->Vertices[CurrentTri.Vindex[1]];
			Vertex3 = Mesh->Vertices[CurrentTri.Vindex[2]];
			if ((Mesh->Header.VertexChannels & W3D_VERTEX_CHANNEL_BONEID) != 0)
			{
				CalculateBoneTransform(Mesh->Influences[CurrentTri.Vindex[0]].BoneIdx,Transform,HierarchyNo);
			}
			MatrixMultiplyVector(&Vertex1,Transform,&Vertex1Trans);
			if ((Mesh->Header.VertexChannels & W3D_VERTEX_CHANNEL_BONEID) != 0)
			{
				CalculateBoneTransform(Mesh->Influences[CurrentTri.Vindex[1]].BoneIdx,Transform,HierarchyNo);
			}
			MatrixMultiplyVector(&Vertex2,Transform,&Vertex2Trans);
			if ((Mesh->Header.VertexChannels & W3D_VERTEX_CHANNEL_BONEID) != 0)
			{
				CalculateBoneTransform(Mesh->Influences[CurrentTri.Vindex[2]].BoneIdx,Transform,HierarchyNo);
			}
			MatrixMultiplyVector(&Vertex3,Transform,&Vertex3Trans);
			if (Mesh->MaterialPass[Count2].StageCount >= 1)
			{
				if (Mesh->MaterialPass[Count2].TextureStage->TextureIDCount != 1)
				{
					if (Mesh->MaterialPass[Count2].TextureStage->TextureIDs[Count] != 0xFFFFFFFF)
					{
						Load = 0;
						Load = LoadTexture(Mesh->Textures[Mesh->MaterialPass[Count2].TextureStage->TextureIDs[Count]].Name);
						if (Load == 0)
						{
							Length = strlen(Mesh->Textures[Mesh->MaterialPass[Count2].TextureStage->TextureIDs[Count]].Name);
							Mesh->Textures[Mesh->MaterialPass[Count2].TextureStage->TextureIDs[Count]].Name[Length-3] = 'd';
							Mesh->Textures[Mesh->MaterialPass[Count2].TextureStage->TextureIDs[Count]].Name[Length-2] = 'd';
							Mesh->Textures[Mesh->MaterialPass[Count2].TextureStage->TextureIDs[Count]].Name[Length-1] = 's';
							Load = LoadTexture(Mesh->Textures[Mesh->MaterialPass[Count2].TextureStage->TextureIDs[Count]].Name);
							Mesh->Textures[Mesh->MaterialPass[Count2].TextureStage->TextureIDs[Count]].Name[Length-3] = 't';
							Mesh->Textures[Mesh->MaterialPass[Count2].TextureStage->TextureIDs[Count]].Name[Length-2] = 'g';
							Mesh->Textures[Mesh->MaterialPass[Count2].TextureStage->TextureIDs[Count]].Name[Length-1] = 'a';
						}
						glEnable(GL_TEXTURE_2D);
					}
				}
			}
			if (Mesh->MaterialPass[Count2].ShaderIDCount != 1)
			{
				Shader = Mesh->Shaders[Mesh->MaterialPass[Count2].ShaderIDs[Count]];
				glDepthFunc(Shader.DepthCompare);
				if (Shader.DepthMask == 0)
				{
					glEnable(GL_DEPTH_TEST);
					glDepthMask(GL_FALSE);
				}
				else
				{
					glEnable(GL_DEPTH_TEST);
					glDepthMask(GL_TRUE);
				}
				switch (Shader.DestBlend)
				{
				case W3DSHADER_DESTBLENDFUNC_ZERO:
					DstAlpha = GL_ZERO;
					break;
				case W3DSHADER_DESTBLENDFUNC_ONE:
					DstAlpha = GL_ONE;
					break;
				case W3DSHADER_DESTBLENDFUNC_SRC_COLOR:
					DstAlpha = GL_SRC_COLOR;
					break;
				case W3DSHADER_DESTBLENDFUNC_ONE_MINUS_SRC_COLOR:
					DstAlpha = GL_ONE_MINUS_SRC_COLOR;
					break;
				case W3DSHADER_DESTBLENDFUNC_SRC_ALPHA:
					DstAlpha = GL_SRC_ALPHA;
					break;
				case W3DSHADER_DESTBLENDFUNC_ONE_MINUS_SRC_ALPHA:
					DstAlpha = GL_ONE_MINUS_SRC_ALPHA;
					break;
				default:
					DstAlpha = W3DSHADER_DESTBLENDFUNC_DEFAULT;
					break;
				}
				switch (Shader.SrcBlend)
				{
				case W3DSHADER_SRCBLENDFUNC_ZERO:
					SrcAlpha = GL_ZERO;
					break;
				case W3DSHADER_SRCBLENDFUNC_ONE:
					SrcAlpha = GL_ONE;
					break;
				case W3DSHADER_SRCBLENDFUNC_SRC_ALPHA:
					SrcAlpha = GL_SRC_ALPHA;
					break;
				case W3DSHADER_SRCBLENDFUNC_ONE_MINUS_SRC_ALPHA:
					SrcAlpha = GL_ONE_MINUS_SRC_ALPHA;
					break;
				default:
					SrcAlpha = W3DSHADER_SRCBLENDFUNC_DEFAULT;
					break;
				}
				glBlendFunc(SrcAlpha,DstAlpha);
				if (Shader.AlphaTest == W3DSHADER_ALPHATEST_ENABLE)
				{
					glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
				}
			}
			if (Mesh->MaterialPass[Count2].VertexMaterialIDCount != 1)
			{	
				Material = Mesh->Materials[Mesh->MaterialPass[Count2].VertexMaterialIDs[CurrentTri.Vindex[0]]];
				glMatrixMode(GL_TEXTURE);
				glLoadIdentity();
				TextureTrans[12] = Material.CurrentU;
				TextureTrans[13] = Material.CurrentV;
				glLoadMatrixf(TextureTrans);
				glMatrixMode(GL_MODELVIEW);
			}
			glBegin(GL_TRIANGLES);
				if (Mesh->MaterialPass[Count2].VertexMaterialIDCount != 1)
				{	
					Material = Mesh->Materials[Mesh->MaterialPass[Count2].VertexMaterialIDs[CurrentTri.Vindex[0]]];
					Color[0] = Material.VertexMaterialInfo.Ambient.R/255.0;
					Color[1] = Material.VertexMaterialInfo.Ambient.G/255.0;
					Color[2] = Material.VertexMaterialInfo.Ambient.B/255.0;
					Color[3] = Material.VertexMaterialInfo.Opacity;
					glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,Color);
					Color[0] = Material.VertexMaterialInfo.Diffuse.R/255.0;
					Color[1] = Material.VertexMaterialInfo.Diffuse.G/255.0;
					Color[2] = Material.VertexMaterialInfo.Diffuse.B/255.0;
					Color[3] = Material.VertexMaterialInfo.Opacity;
					glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,Color);
					Color[0] = Material.VertexMaterialInfo.Specular.R/255.0;
					Color[1] = Material.VertexMaterialInfo.Specular.G/255.0;
					Color[2] = Material.VertexMaterialInfo.Specular.B/255.0;
					Color[3] = Material.VertexMaterialInfo.Opacity;
					glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,Color);
					Color[0] = Material.VertexMaterialInfo.Emissive.R/255.0;
					Color[1] = Material.VertexMaterialInfo.Emissive.G/255.0;
					Color[2] = Material.VertexMaterialInfo.Emissive.B/255.0;
					Color[3] = Material.VertexMaterialInfo.Opacity;
					glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Color);
					glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,Material.VertexMaterialInfo.Shininess);
				}
				MatrixMultiplyVector(&Mesh->Normals[CurrentTri.Vindex[0]],Transform,&NormalTrans);
				glNormal3f(NormalTrans.X,NormalTrans.Y,NormalTrans.Z);
				if (TexCoords)
					glTexCoord2f(TexCoords[CurrentTri.Vindex[0]].U,TexCoords[CurrentTri.Vindex[0]].V);
				if (Mesh->MaterialPass[Count2].DCG != 0)
				{
					Color[0] = Mesh->MaterialPass[Count2].DCG[CurrentTri.Vindex[0]].R/255.0;
					Color[1] = Mesh->MaterialPass[Count2].DCG[CurrentTri.Vindex[0]].G/255.0;
					Color[2] = Mesh->MaterialPass[Count2].DCG[CurrentTri.Vindex[0]].B/255.0;
					Color[3] = Mesh->MaterialPass[Count2].DCG[CurrentTri.Vindex[0]].A/255.0;
					glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,Color);
				}
				glVertex3f(Vertex1Trans.X,Vertex1Trans.Y,Vertex1Trans.Z);
				if (Mesh->MaterialPass[Count2].VertexMaterialIDCount != 1)
				{	
					Material = Mesh->Materials[Mesh->MaterialPass[Count2].VertexMaterialIDs[CurrentTri.Vindex[1]]];
					Color[0] = Material.VertexMaterialInfo.Ambient.R/255.0;
					Color[1] = Material.VertexMaterialInfo.Ambient.G/255.0;
					Color[2] = Material.VertexMaterialInfo.Ambient.B/255.0;
					Color[3] = Material.VertexMaterialInfo.Opacity;
					glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,Color);
					Color[0] = Material.VertexMaterialInfo.Diffuse.R/255.0;
					Color[1] = Material.VertexMaterialInfo.Diffuse.G/255.0;
					Color[2] = Material.VertexMaterialInfo.Diffuse.B/255.0;
					Color[3] = Material.VertexMaterialInfo.Opacity;
					glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,Color);
					Color[0] = Material.VertexMaterialInfo.Specular.R/255.0;
					Color[1] = Material.VertexMaterialInfo.Specular.G/255.0;
					Color[2] = Material.VertexMaterialInfo.Specular.B/255.0;
					Color[3] = Material.VertexMaterialInfo.Opacity;
					glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,Color);
					Color[0] = Material.VertexMaterialInfo.Emissive.R/255.0;
					Color[1] = Material.VertexMaterialInfo.Emissive.G/255.0;
					Color[2] = Material.VertexMaterialInfo.Emissive.B/255.0;
					Color[3] = Material.VertexMaterialInfo.Opacity;
					glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Color);
					glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,Material.VertexMaterialInfo.Shininess);
				}
				MatrixMultiplyVector(&Mesh->Normals[CurrentTri.Vindex[1]],Transform,&NormalTrans);
				glNormal3f(NormalTrans.X,NormalTrans.Y,NormalTrans.Z);
				if (TexCoords)
					glTexCoord2f(TexCoords[CurrentTri.Vindex[1]].U,TexCoords[CurrentTri.Vindex[1]].V);
				if (Mesh->MaterialPass[Count2].DCG != 0)
				{
					Color[0] = Mesh->MaterialPass[Count2].DCG[CurrentTri.Vindex[1]].R/255.0;
					Color[1] = Mesh->MaterialPass[Count2].DCG[CurrentTri.Vindex[1]].G/255.0;
					Color[2] = Mesh->MaterialPass[Count2].DCG[CurrentTri.Vindex[1]].B/255.0;
					Color[3] = Mesh->MaterialPass[Count2].DCG[CurrentTri.Vindex[1]].A/255.0;
					glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,Color);
				}
				glVertex3f(Vertex2Trans.X,Vertex2Trans.Y,Vertex2Trans.Z);
				if (Mesh->MaterialPass[Count2].VertexMaterialIDCount != 1)
				{	
					Material = Mesh->Materials[Mesh->MaterialPass[Count2].VertexMaterialIDs[CurrentTri.Vindex[2]]];
					Color[0] = Material.VertexMaterialInfo.Ambient.R/255.0;
					Color[1] = Material.VertexMaterialInfo.Ambient.G/255.0;
					Color[2] = Material.VertexMaterialInfo.Ambient.B/255.0;
					Color[3] = Material.VertexMaterialInfo.Opacity;
					glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,Color);
					Color[0] = Material.VertexMaterialInfo.Diffuse.R/255.0;
					Color[1] = Material.VertexMaterialInfo.Diffuse.G/255.0;
					Color[2] = Material.VertexMaterialInfo.Diffuse.B/255.0;
					Color[3] = Material.VertexMaterialInfo.Opacity;
					glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,Color);
					Color[0] = Material.VertexMaterialInfo.Specular.R/255.0;
					Color[1] = Material.VertexMaterialInfo.Specular.G/255.0;
					Color[2] = Material.VertexMaterialInfo.Specular.B/255.0;
					Color[3] = Material.VertexMaterialInfo.Opacity;
					glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,Color);
					Color[0] = Material.VertexMaterialInfo.Emissive.R/255.0;
					Color[1] = Material.VertexMaterialInfo.Emissive.G/255.0;
					Color[2] = Material.VertexMaterialInfo.Emissive.B/255.0;
					Color[3] = Material.VertexMaterialInfo.Opacity;
					glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Color);
					glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,Material.VertexMaterialInfo.Shininess);
				}
				MatrixMultiplyVector(&Mesh->Normals[CurrentTri.Vindex[2]],Transform,&NormalTrans);
				glNormal3f(NormalTrans.X,NormalTrans.Y,NormalTrans.Z);
				if (TexCoords)
					glTexCoord2f(TexCoords[CurrentTri.Vindex[2]].U,TexCoords[CurrentTri.Vindex[2]].V);
				if (Mesh->MaterialPass[Count2].DCG != 0)
				{
					Color[0] = Mesh->MaterialPass[Count2].DCG[CurrentTri.Vindex[2]].R/255.0;
					Color[1] = Mesh->MaterialPass[Count2].DCG[CurrentTri.Vindex[2]].G/255.0;
					Color[2] = Mesh->MaterialPass[Count2].DCG[CurrentTri.Vindex[2]].B/255.0;
					Color[3] = Mesh->MaterialPass[Count2].DCG[CurrentTri.Vindex[2]].A/255.0;
					glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,Color);
				}
				glVertex3f(Vertex3Trans.X,Vertex3Trans.Y,Vertex3Trans.Z);
			glEnd();
		}
	}
}
*/


char * concatenate(const char* a, const char* b) {
  int a_len = strlen(a), b_len = strlen(b);
  int buf_size = a_len + b_len + 1;
  char* result = (char*)malloc(buf_size);
  memcpy(result, a, a_len);
  memcpy(result+a_len, b, b_len);
  result[a_len+b_len] = 0;
  return result;
}

int main(int argc, char* argv[]) {
	Initdefs();
	if(fseek(stdin,0,SEEK_END)) {
    fprintf(stderr, "stdin must be a seekable stream");
    return -1;
  }
	size_t input_size = ftell(stdin);
  fseek(stdin,0,SEEK_SET);
	LoadW3d(stdin, input_size);
  const char *prefix;
  if(argc >= 2) {
    prefix = argv[1];
  } else {
    prefix = "./";
  }
  for (int i=0;i<MeshCount;++i) {
    char* filename = concatenate(prefix, Mesh[Count].Header.MeshName);
    FILE* fout = fopen(filename, "w");
    if(!fout) {
      fprintf(stderr, "Error creating file %s\n", filename);
      free(filename);
      continue;
    }
    free(filename);
    convertMesh(&Mesh[i], fout);
    fclose(fout);
	}
  return 0;
}
