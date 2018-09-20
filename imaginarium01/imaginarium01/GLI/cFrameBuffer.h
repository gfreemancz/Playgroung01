/*
 * cFrameBuffer.h
 *
 *  Created on: 5. 3. 2017
 *      Author: GFreeman
 */

#ifndef GLI_CFRAMEBUFFER_H_
#define GLI_CFRAMEBUFFER_H_

#include <vector>

#ifndef STDAFX_H
#include "stdafx.h"
#endif

#ifndef __glew_h__
  #include <glew.h>
#endif

namespace nsGLI {

enum eFBOAttachementType
{
  TEXTURE_2D,
  RENDERBUFFER
};

class cFrameBuffer
{
  struct sFBOAtta
  {
    GLuint ID;
    eFBOAttachementType Type;
  };
  GLuint FrameBufferID;
  std::vector<sFBOAtta> ColorAttachements;
  GLuint  DepthAttachement;
  GLuint  StencilAttachement;

public:
  cFrameBuffer();
  ~cFrameBuffer();
  void BindFBO(void);
  ui8 AddColorAttachement(eFBOAttachementType arg_Type,ui32 arg_Width,ui32 arg_Height);
};

} /* namespace nsGLI */

#endif /* GLI_CFRAMEBUFFER_H_ */
