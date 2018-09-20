/*
 * cGeometryDataBuffer.cpp
 *
 *  Created on: 6. 3. 2017
 *      Author: GFreeman
 */

#ifndef STDAFX_H
#include "stdafx.h"
#endif
#include <graphic/cMesh.h>

namespace nsGraphic {

cMesh::cMesh():
    VertexArrayID(0U),
    VertexBufferID(0U),
    IndexBufferID(0U)
{
 // glGenVertexArrays(1U,&VertexArrayID);
//  glGenBuffers(1U,&VertexBufferID);
//  glGenBuffers(1U,&IndexBufferID);
}

cMesh::~cMesh()
{
  glDeleteFramebuffers(1U, &VertexBufferID);
  glDeleteFramebuffers(1U, &IndexBufferID);
  glGenVertexArrays(1U, &VertexArrayID);
}

void cMesh::InitGeometry(void* data, const ui32 dSize, void* dataI,
    const ui32 dSizeI, const GLenum usage)
{
  // create buffer of raw geometric data (vetices)
  glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
  glBufferData(GL_ARRAY_BUFFER, 32U, data, usage);
  // create buffer of indexes
  glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, IndexBufferID);
  glBufferData( GL_ELEMENT_ARRAY_BUFFER, dSizeI * sizeof(GLuint), dataI, usage);
  //unbind buffers from GPU context
  glBindBuffer( GL_ARRAY_BUFFER, 0U);
  glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0U );
}

void cMesh::BindBuffer(void)
{
  glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
  glVertexPointer(3 ,GL_FLOAT,32 ,NULL );
  glNormalPointer(GL_FLOAT,32 ,(void*)12 );
  glTexCoordPointer(2, GL_FLOAT, 32, (void*)24);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferID );
}

} /* namespace nsGLI */
