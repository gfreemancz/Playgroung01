/*
 * cVertexBuffer.h
 *
 *  Created on: 8. 1. 2018
 *      Author: GFreeman
 */

#ifndef GLI_CVERTEXBUFFEROBJECT_H_
#define GLI_CVERTEXBUFFEROBJECT_H_

#ifndef STDAFX_H
#include "stdafx.h"
#endif

#include <SDL.h>

//#define GLEW_STATIC
#include <glew.h>
#include <GL\GL.h>
#include <GL\GLU.h>

#include "glm/vec3.hpp"
#include "glm/vec2.hpp"


#include "vector"

namespace nsGLI {
typedef	struct sVertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 UV;
} tVertex;

class cVertexBufferObject
{
  std::vector<tVertex> Data;
  GLuint VBO_id;
  ui16 VBOusage;
  ui32 getDataSize(void)
  {
	  return static_cast<ui32>(Data.size()) * static_cast<ui32>(sizeof(tVertex));
  }
public:
  cVertexBufferObject();
  cVertexBufferObject(ui16 arg_usage);
  ~cVertexBufferObject();

  void AddVertex(glm::vec3 arg_Pos, glm::vec3 arg_Normal, glm::vec2 arg_UV);
  void Clean(void);

  //activate VBO in GPU
  void BindVBO(void)
  {
    glBindBuffer(GL_ARRAY_BUFFER, VBO_id);
  }
  void UnBindVBO(void)
  {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
  //create VBO in GPU
  void CreateVBO(void)
  {
    glGenBuffers(1, &VBO_id);
  }
  //create data storage in GPU and load data there
  void LoadDataToGPU(void)
  {
    glNamedBufferData(VBO_id, getDataSize(), &Data[0], VBOusage);
  }
  //update data of whole VBO in GPU 
  void UpdateDataInGPU(void)
  {
    glNamedBufferSubData(VBO_id, 0, getDataSize(), &Data[0]);
  }
  //update data of part of VBO in GPU 
  void UpdateDataInGPU(ui32 arg_offset, ui32 arg_UpdateVertexCount)
  {
    glNamedBufferSubData(VBO_id, arg_offset, arg_UpdateVertexCount * sizeof(tVertex), &Data[0]);
  }

};

} /* namespace nsGLI */

#endif /* GLI_CVERTEXBUFFEROBJECT_H_ */
