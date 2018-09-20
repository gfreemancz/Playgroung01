/*
 * cFrameBuffer.cpp
 *
 *  Created on: 5. 3. 2017
 *      Author: GFreeman
 */

#ifndef STDAFX_H
#include "stdafx.h"
#endif
#include <GLI/cFrameBuffer.h>




namespace nsGLI {

cFrameBuffer::cFrameBuffer():
    FrameBufferID(0),
    DepthAttachement(0),
    StencilAttachement(0)
{
//  glGenFramebuffers(1, &FrameBufferID);
}

cFrameBuffer::~cFrameBuffer()
{
  glDeleteFramebuffers(1, &FrameBufferID);
}

void cFrameBuffer::BindFBO(void)
{
  glBindFramebuffer(GL_FRAMEBUFFER, FrameBufferID);
}

} /* namespace nsGLI */
