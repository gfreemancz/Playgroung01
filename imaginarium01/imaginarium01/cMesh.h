#pragma once
#include "glm\vec3.hpp"
#include "glm\vec2.hpp"
#include <vector>
#include <string>
#include "GLI\cVertexBufferObject.h"

#include "cGLBufferObject.h"
#include "GLI/cVertexArrayObject.h"





#define READOUT_OF_OGL_ERRORS 0


class cVertex
{
public:
  cVertex() :Position(glm::vec3(0, 0, 0)), Normal(glm::vec3(0, 0, 0)), UV(glm::vec2(0, 0)) {}
  glm::vec3 Position;
  glm::vec3 Normal;
  glm::vec2 UV;
};

typedef struct sVertexIdx
{
  ui32 pos_id;
  ui32 normal_id;
  ui32 UV_id;
} tVertexIdx;

class cMeshT
{
public:
  cMeshT();
  ~cMeshT();
  void AddVertexPosition(glm::vec3 arg_Position);
  void AddVertexNormal(glm::vec3 arg_Normal);
  void AddVertexUV(glm::vec2 arg_UV);
  void AddTriangle(cVertex arg_VertexA, cVertex arg_VertexB, cVertex arg_VertexC);
  void AddQuad(cVertex arg_VertexA, cVertex arg_VertexB, cVertex arg_VertexC, cVertex arg_VertexD);
  void CreateVBO(void);
  void UpdateVBO(void);
  template<class LOADER> ui8 LoadModel(std::string arg_FileName);
  void Draw(void);



  typedef struct
  {
    ui32 VertexID[3];
  } sTriangle;

private:


  ui32 CheckAndAddVertex(cVertex arg_Vertex);
   
  ui32 CheckPosList(glm::vec3 arg_PositioToCheck);
  ui32 CheckNormalPosList(glm::vec3 arg_PositioToCheck);
  ui32 CheckUVPosList(glm::vec2 arg_PositioToCheck);
  ui32 CheckVertexList(sVertexIdx arg_PositioToCheck);

  ui32 CheckBufferCombination(glm::vec3 arg_position, glm::vec3 arg_normal, glm::vec2 arg_uv);
  
  nsGLI::cGLBufferObject<ui32,  GL_UNSIGNED_INT> IndexBuffer;
  nsGLI::cGLBufferObject<glm::vec3,  GL_FLOAT>  PositionBuffer;
  nsGLI::cGLBufferObject<glm::vec3,  GL_FLOAT>  NormalBuffer;
  nsGLI::cGLBufferObject<glm::vec2,  GL_FLOAT>  UV_Buffer;

  nsGLI::cVertexArrayObject VertexArrayObject;

  std::vector<glm::vec3>   VertexPositions;
  std::vector<glm::vec3>   VertexNormals;
  std::vector<glm::vec2>   VertexUVs;
  std::vector<sVertexIdx>  VertexIdx;
  std::vector<sTriangle>   Triangles;

  //nsGLI::cVertexBufferObject VertexBuffer;

 

  std::string Name;

};

template<class LOADER>
inline ui8 cMeshT::LoadModel(std::string arg_FileName)
{
  LOADER  loc_loader;

  return loc_loader.LoadModel(arg_FileName, this);
}
