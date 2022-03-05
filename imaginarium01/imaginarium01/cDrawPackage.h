#pragma once

#include <iostream>
#include <vector>
#include "cGL_Texture.h"
#include "GLI/cVertexArrayObject.h"
#include "cMesh.h"

class cDrawPackage
{
public:
  ui8 AddMesh(cMeshT* arg_Mesh);




private:
  std::vector<cMeshT>  MeshStorage;
};

