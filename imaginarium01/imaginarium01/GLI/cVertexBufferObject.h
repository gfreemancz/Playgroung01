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


#include "glm/vec3.hpp"
#include "glm/vec2.hpp"


#include "vector"

namespace nsGLI {


class cVertexBufferObject
{
  struct sVertex
  {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 UV;
  };

  std::vector<sVertex> Data;
public:
  cVertexBufferObject();
  ~cVertexBufferObject();
  void AddVertex(glm::vec3 arg_Pos, glm::vec3 arg_Normal, glm::vec2 arg_UV);
  void Clean(void);
};

} /* namespace nsGraphic */

#endif /* GLI_CVERTEXBUFFEROBJECT_H_ */
