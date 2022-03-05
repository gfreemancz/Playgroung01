/*
 * cVertexBuffer.cpp
 *
 *  Created on: 8. 1. 2018
 *      Author: GFreeman
 */

#ifndef STDAFX_H
#include "stdafx.h"
#endif
#include <GLI/cVertexBufferObject.h>

namespace nsGLI {

cVertexBufferObject::cVertexBufferObject():
  Data(),
  VBO_id(-1),
  VBOusage(0)
{
  // TODO Auto-generated constructor stub

}

cVertexBufferObject::cVertexBufferObject(ui16 arg_usage):
  Data(),
  VBO_id(-1),
  VBOusage(arg_usage)
{
}

cVertexBufferObject::~cVertexBufferObject()
{
  //if not empty, delete data in RAM
  if (Data.size() > 0)
  {
    Data.clear();
  //  delete &Data;
  }
  //if needed, delete VBO in GPU
  if (VBO_id != -1)
  {
    glDeleteBuffers(1, &VBO_id);
  }
}

void cVertexBufferObject::AddVertex(glm::vec3 arg_Pos, glm::vec3 arg_Normal, glm::vec2 arg_UV)
{
  sVertex loc_vertex;
  loc_vertex.Position = arg_Pos;
  loc_vertex.Normal= arg_Normal;
  loc_vertex.UV = arg_UV;
  Data.push_back(loc_vertex);
}

void cVertexBufferObject::Clean(void)
{
  glDeleteBuffers(1,&VBO_id);
  Data.clear();
}

} /* namespace nsGraphic */
