#include "stdafx.h"
#include "cMesh.h"


cMesh::cMesh()
{
}


cMesh::~cMesh()
{
}

void cMesh::AddVertexPosition(glm::vec3 arg_Position)
{
  VertexPositions.push_back(arg_Position);
}

void cMesh::AddVertexNormal(glm::vec3 arg_Normal)
{
  VertexNormals.push_back(arg_Normal);
}

void cMesh::AddVertexUV(glm::vec2 arg_UV)
{
  VertexUVs.push_back(arg_UV);
}

void cMesh::AddTriangle(glm::ivec3  arg_VertexA, glm::ivec3  arg_VertexB, glm::ivec3  arg_VertexC)
{
  sTriangle triangle;

  triangle.Vertex[0].Position = VertexPositions[arg_VertexA.x];
  triangle.Vertex[0].UV       = VertexUVs[arg_VertexA.y];
  triangle.Vertex[0].Normal   = VertexNormals[arg_VertexA.z];

  triangle.Vertex[1].Position = VertexPositions[arg_VertexB.x];
  triangle.Vertex[1].UV       = VertexUVs[arg_VertexB.y];
  triangle.Vertex[1].Normal   = VertexNormals[arg_VertexB.z];

  triangle.Vertex[2].Position = VertexPositions[arg_VertexC.x];
  triangle.Vertex[2].UV       = VertexUVs[arg_VertexC.y];
  triangle.Vertex[2].Normal   = VertexNormals[arg_VertexC.z];
  
  Triangles.push_back(triangle);
}

void cMesh::CreateVBO(void)
{
}

void cMesh::UpdateVBO(void)
{
}
