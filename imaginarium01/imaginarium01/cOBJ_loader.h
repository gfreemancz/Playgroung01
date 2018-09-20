#pragma once
#include <iostream>
#include <string>
#include "cMesh.h"

class cOBJ_loader
{
  static ui8 StoreTriangle(std::vector<std::string>& arg_VertexIdxStr, cMesh * arg_ref_Mesh);
public:
  cOBJ_loader();
  ~cOBJ_loader();
  static ui8 LoadModel(std::string arg_FileName, cMesh *arg_ref_Mesh);
  static ui8 ProcessLine(std::string arg_line, cMesh * arg_ref_Mesh);
};

