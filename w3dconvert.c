  #include <stdlib.h>
#include "w3d.h"


void convertMesh(W3dMeshStruct *mesh, FILE* fout) {
  int i;
  
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
    //"property float u\n"
    //"property float v\n"
    //"property list uchar float influences\n"
    "element faces %d\n"
    "property list uchar int vertex_index\n"
    "end header\n",
    mesh->Header.MeshName,
    (int)mesh->Header.NumVertices,
    (int)mesh->Header.NumTris
  );

  //Export all of the vertices
  for(i=0; i<mesh->Header.NumVertices; ++i) {
  
    W3dVectorStruct position = mesh->Vertices[i];
    fprintf(fout, "%f %f %f", (float)position.X, (float)position.Y, (float)position.Z);
    
    W3dVectorStruct normal = mesh->Normals[i];
    fprintf(fout, " %f %f %f", (float)normal.X, (float)normal.Y, (float)normal.Z);
    
    //W3dVertInfStruct influences = mesh->Influences[i];
    
    fprintf(fout, "\n");
  }
  
  //Export all of the triangles
  for(i=0; i<mesh->Header.NumTris; ++i) {
    W3dTriStruct cell = mesh->Triangles[i];
    fprintf(fout, "%d %d %d\n", (int)cell.Vindex[0], (int)cell.Vindex[1], (int)cell.Vindex[2]);
  }
}


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
  int i;
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
  for(i=0;i<MeshCount;++i) {
    char* filename = concatenate(prefix, Mesh[i].Header.MeshName);
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
