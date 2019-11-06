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
  StencilAttachement(0),
  Width(0),
  Height(0)
{

}

cFrameBuffer::cFrameBuffer(ui32 arg_Width, ui32 arg_Height) :
  FrameBufferID(0),
  DepthAttachement(0),
  StencilAttachement(0),
  Width(arg_Width),
  Height(arg_Height)
{

}


cFrameBuffer::~cFrameBuffer()
{
  if(FrameBufferID!=0)
  { 
    glDeleteFramebuffers(1, &FrameBufferID);
  }
}

void cFrameBuffer::InitFBO(void)
{
  glGenFramebuffers(1, &FrameBufferID);
}


void cFrameBuffer::BindFBO(void)
{
  glBindFramebuffer(GL_FRAMEBUFFER, FrameBufferID);
}

void cFrameBuffer::UnBindFBO(void)
{
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

ui8 cFrameBuffer::AddColorAttachement(cGL_Texture &arg_Texture)
{
  if ((arg_Texture.GetWidth() != Width) && (arg_Texture.GetHeight() != Height))
  {
    //TODO reaction when attached color buffer have different dimensions then frame buffer
  }
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, arg_Texture.GetTextureId() , 0);
	return ui8(0);
}

ui16 cFrameBuffer::CheckFBStatus(void)
{
  return ui16(glCheckFramebufferStatus(GL_FRAMEBUFFER));
}

} /* namespace nsGLI */
