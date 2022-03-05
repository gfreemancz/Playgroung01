#include "stdafx.h"
#include "cOBJ_loader.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>


ui8 cOBJ_loader::StoreTriangle(std::vector<std::string>& arg_VertexIdxStr, cMeshT * arg_ref_Mesh)
{
  ui8 loc_RetValue = 0;
  glm::ivec3  loc_VertexA, loc_VertexB, loc_VertexC;

  if (arg_VertexIdxStr.size() == 3U)
  { 

    std::size_t found = arg_VertexIdxStr[0].find("//");

    if (found != std::string::npos)
    {
      arg_VertexIdxStr[0].insert(found+1, "0");
    }
    found = arg_VertexIdxStr[1].find("//");

    if (found != std::string::npos)
    {
      arg_VertexIdxStr[1].insert(found + 1, "0");
    }
    found = arg_VertexIdxStr[2].find("//");

    if (found != std::string::npos)
    {
      arg_VertexIdxStr[2].insert(found + 1, "0");
    }
    
    std::replace(arg_VertexIdxStr[0].begin(), arg_VertexIdxStr[0].end(), '/', ' ');
    std::replace(arg_VertexIdxStr[1].begin(), arg_VertexIdxStr[1].end(), '/', ' ');
    std::replace(arg_VertexIdxStr[2].begin(), arg_VertexIdxStr[2].end(), '/', ' ');
    std::string loc_Idx;
    std::stringstream loc_IdxStream;
    loc_IdxStream << arg_VertexIdxStr[0];
    loc_IdxStream >> loc_Idx;
    loc_VertexA.x = std::stoi(loc_Idx);
    loc_IdxStream >> loc_Idx;
    loc_VertexA.y = std::stoi(loc_Idx);
    loc_IdxStream >> loc_Idx;
    loc_VertexA.z = std::stoi(loc_Idx);

    loc_IdxStream << "";
    loc_IdxStream.clear();
    loc_IdxStream << arg_VertexIdxStr[1];
    loc_IdxStream >> loc_Idx;
    loc_VertexB.x = std::stoi(loc_Idx);
    loc_IdxStream >> loc_Idx;
    loc_VertexB.y = std::stoi(loc_Idx);
    loc_IdxStream >> loc_Idx;
    loc_VertexB.z = std::stoi(loc_Idx);

    loc_IdxStream << "";
    loc_IdxStream.clear();
    loc_IdxStream << arg_VertexIdxStr[2];
    loc_IdxStream >> loc_Idx;
    loc_VertexC.x = std::stoi(loc_Idx);
    loc_IdxStream >> loc_Idx;
    loc_VertexC.y = std::stoi(loc_Idx);
    loc_IdxStream >> loc_Idx;
    loc_VertexC.z = std::stoi(loc_Idx);

    cVertex loc_Vertex1;
    loc_Vertex1.Position = tmp_VertexPositions[loc_VertexA.x];
    loc_Vertex1.Normal   = tmp_VertexNormals[loc_VertexA.z];
    loc_Vertex1.UV       = tmp_VertexUVs[loc_VertexA.y];
    cVertex loc_Vertex2;
    loc_Vertex2.Position = tmp_VertexPositions[loc_VertexB.x];
    loc_Vertex2.Normal = tmp_VertexNormals[loc_VertexB.z];
    loc_Vertex2.UV = tmp_VertexUVs[loc_VertexB.y];
    cVertex loc_Vertex3;
    loc_Vertex3.Position = tmp_VertexPositions[loc_VertexC.x];
    loc_Vertex3.Normal = tmp_VertexNormals[loc_VertexC.z];
    loc_Vertex3.UV = tmp_VertexUVs[loc_VertexC.y];


    arg_ref_Mesh->AddTriangle(loc_Vertex1, loc_Vertex2, loc_Vertex3);
  }
  else
  {
    loc_RetValue = 1;
  } 

  return loc_RetValue;
}

cOBJ_loader::cOBJ_loader()
{
  tmp_VertexPositions.push_back(glm::vec3(0, 0, 0));
  tmp_VertexNormals.push_back(glm::vec3(0, 0, 0));
  tmp_VertexUVs.push_back(glm::vec2(0, 0));
}


cOBJ_loader::~cOBJ_loader()
{
  tmp_VertexPositions.clear();
  tmp_VertexNormals.clear();
  tmp_VertexUVs.clear();
}

ui8 cOBJ_loader::LoadModel(std::string arg_FileName, cMeshT * arg_ref_Mesh)
{
  ui8 loc_RetValue = 0;
  ui32 loc_LineCnt = 0;
  std::ifstream loc_File;
  std::vector<std::string> loc_lines;
  std::string loc_tmpLine;

  loc_File.open(arg_FileName.c_str(), std::ifstream::in);


  while(!std::getline(loc_File, loc_tmpLine).eof())
  {
    loc_LineCnt++;
    ProcessLine(loc_tmpLine, arg_ref_Mesh);
  }
  
  return loc_RetValue;
}

ui8 cOBJ_loader::ProcessLine(std::string arg_line, cMeshT * arg_ref_Mesh)
{
  std::istringstream loc_lineStream(arg_line);
  std::string loc_tmp;

  loc_lineStream >> loc_tmp;

  if (loc_tmp == "v") // process vertex position
  {
    loc_lineStream >> loc_tmp;
    float loc_Xpos = std::stof(loc_tmp);
    loc_lineStream >> loc_tmp;
    float loc_Ypos = std::stof(loc_tmp);
    loc_lineStream >> loc_tmp;
    float loc_Zpos = std::stof(loc_tmp);
    tmp_VertexPositions.push_back(glm::vec3(loc_Xpos, loc_Ypos, loc_Zpos));
    //arg_ref_Mesh->AddVertexPosition(glm::vec3(loc_Xpos, loc_Ypos, loc_Zpos));   
  } 
  if (loc_tmp == "vn") // process vertex normal
  {
    loc_lineStream >> loc_tmp;
    float loc_Xpos = std::stof(loc_tmp);
    loc_lineStream >> loc_tmp;
    float loc_Ypos = std::stof(loc_tmp);
    loc_lineStream >> loc_tmp;
    float loc_Zpos = std::stof(loc_tmp);
    tmp_VertexNormals.push_back(glm::vec3(loc_Xpos, loc_Ypos, loc_Zpos));
    //arg_ref_Mesh->AddVertexNormal(glm::vec3(loc_Xpos, loc_Ypos, loc_Zpos));
  }
  if (loc_tmp == "vt") // process texturing coordinates
  {
    loc_lineStream >> loc_tmp;
    float loc_Xpos = std::stof(loc_tmp);
    loc_lineStream >> loc_tmp;
    float loc_Ypos = std::stof(loc_tmp);
    tmp_VertexUVs.push_back(glm::vec2(loc_Xpos, loc_Ypos ));
    //arg_ref_Mesh->AddVertexUV(glm::vec2(loc_Xpos, loc_Ypos));
  }

  if (loc_tmp == "f") // process triangles (if poligon/quad - split to triangles)
  {
    std::vector<std::string> loc_VertexIdxComb;
    while (loc_lineStream >> loc_tmp)
    {
      loc_VertexIdxComb.push_back(loc_tmp);
    }
    if (loc_VertexIdxComb.size() > 3U)
    {
      if (loc_VertexIdxComb.size() == 4U)
      {
        std::vector<std::string> loc_VertexIdxCombA;

        loc_VertexIdxCombA.push_back(loc_VertexIdxComb[0]);
        loc_VertexIdxCombA.push_back(loc_VertexIdxComb[1]);
        loc_VertexIdxCombA.push_back(loc_VertexIdxComb[2]);
        StoreTriangle(loc_VertexIdxCombA, arg_ref_Mesh);
        loc_VertexIdxCombA.clear();
        loc_VertexIdxCombA.push_back(loc_VertexIdxComb[0]);
        loc_VertexIdxCombA.push_back(loc_VertexIdxComb[2]);
        loc_VertexIdxCombA.push_back(loc_VertexIdxComb[3]);
        StoreTriangle(loc_VertexIdxCombA, arg_ref_Mesh);

      }
      else
      {
        std::cout << "more then quad" << std::endl;
      }
    }
    else
    {      
      StoreTriangle(loc_VertexIdxComb, arg_ref_Mesh);
    }

  }

  return ui8(0);
}
