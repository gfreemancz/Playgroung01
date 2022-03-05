#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "cMesh.h"

class cOBJ_loader
{
  ui8 StoreTriangle(std::vector<std::string>& arg_VertexIdxStr, cMeshT * arg_ref_Mesh);
  std::vector<glm::vec3>   tmp_VertexPositions;
  std::vector<glm::vec3>   tmp_VertexNormals;
  std::vector<glm::vec2>   tmp_VertexUVs;
public:
  cOBJ_loader();
  ~cOBJ_loader();
  ui8 LoadModel(std::string arg_FileName, cMeshT *arg_ref_Mesh);
  ui8 ProcessLine(std::string arg_line, cMeshT * arg_ref_Mesh);
};

