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

cVertexBufferObject::cVertexBufferObject()
{
  // TODO Auto-generated constructor stub

}

cVertexBufferObject::~cVertexBufferObject()
{
  if(Data.size()>0) delete &Data;
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
  Data.clear();
}

} /* namespace nsGraphic */
