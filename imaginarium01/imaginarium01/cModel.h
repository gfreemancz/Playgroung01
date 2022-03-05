#pragma once

#include "cMesh.h"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "cTexture.h"

//***********************************************
// class cModel represents combination of 3d information (vertexes, UV coordinates, normals - mesh)
// testure information and OpenGL stuff to draw it
//***********************************************
class cModel
{
public:
  cMeshT Mesh;
  glm::mat4x4 GetModelTransformaMatrix(void);
  void SetPosition(glm::vec3 arg_Position);
  void SetRotation(glm::vec3 arg_Rotation);
private:
  glm::vec3 Position;
  glm::vec3 Rotation;
  
  cTexture* pTexture;



};

