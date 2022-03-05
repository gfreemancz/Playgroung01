/*
 * cVertexArrayObject.h
 *
 *  Created on: 8. 1. 2018
 *      Author: GFreeman
 */

#ifndef GLI_CVERTEXARRAYOBJECT_H_
#define GLI_CVERTEXARRAYOBJECT_H_

#ifndef STDAFX_H
#include "stdafx.h"
#endif

//#define GLEW_STATIC
#include <glew.h>
#include <GL\GL.h>
#include <GL\GLU.h>

namespace nsGLI {

class cVertexArrayObject
{
  GLuint VAO_id;
public:

  //create VAO in GPU
  void CreateVAO(void)
  {
    glGenVertexArrays(1, &VAO_id);
  }

  //activate VAO in GPU
  void BindVAO(void)
  {
    glBindVertexArray(VAO_id);
  }
  //activate VAO in GPU
  void UnBindVAO(void)
  {
    glBindVertexArray(0);
  }


  cVertexArrayObject();
  ~cVertexArrayObject();
};

} /* namespace nsGLI */

#endif /* GLI_CVERTEXARRAYOBJECT_H_ */
