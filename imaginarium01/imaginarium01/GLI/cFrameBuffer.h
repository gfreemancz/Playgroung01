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

#include "cGL_Texture.h"

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
  ui32    Width;
  ui32    Height;
public:
  cFrameBuffer();
  cFrameBuffer(ui32 arg_Width, ui32 arg_Height);
  ~cFrameBuffer();
  void InitFBO(void);
  void BindFBO(void);
  void UnBindFBO(void);
  ui8 AddColorAttachement(cGL_Texture &arg_Texture);
  ui16 CheckFBStatus(void);
  
};

} /* namespace nsGLI */

#endif /* GLI_CFRAMEBUFFER_H_ */
