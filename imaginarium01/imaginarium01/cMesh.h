#pragma once
#include "glm\vec3.hpp"
#include "glm\vec2.hpp"
#include <vector>
#include <string>
#include "GLI\cVertexBufferObject.h"



class cMesh
{
public:
  cMesh();
  ~cMesh();
  void AddVertexPosition(glm::vec3 arg_Position);
  void AddVertexNormal(glm::vec3 arg_Normal);
  void AddVertexUV(glm::vec2 arg_UV);
  void AddTriangle(glm::ivec3  arg_VertexA, glm::ivec3  arg_VertexB, glm::ivec3  arg_VertexC);
  void CreateVBO(void);
  void UpdateVBO(void);
  template<class LOADER> ui8 LoadModel(std::string arg_FileName);

  class cVertex
  {
  public:
    cVertex() :Position(glm::vec3(0,0,0)), Normal(glm::vec3(0, 0, 0)), UV(glm::vec2(0,  0) ){}
    glm::vec3 & Position;
    glm::vec3 & Normal;
    glm::vec2 & UV;
  };

  typedef struct
  {
    cVertex Vertex[3];
  } sTriangle;

private:

  std::string Name;
  std::vector<glm::vec3> VertexPositions;
  std::vector<glm::vec3> VertexNormals;
  std::vector<glm::vec2> VertexUVs;
  std::vector<sTriangle> Triangles;

  nsGLI::cVertexBufferObject VertexBuffer;


};

template<class LOADER>
inline ui8 cMesh::LoadModel(std::string arg_FileName)
{
  return LOADER::LoadModel(arg_FileName, this);
}
