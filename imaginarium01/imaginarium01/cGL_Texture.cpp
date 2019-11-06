

#ifndef GLI_CGL_TEXTURE_H
  #include "cGL_Texture.h"
#endif


nsGLI::cGL_Texture::cGL_Texture():
  TextureID(0),
  Width(0),
  Height(0),
  TypeOpt(GL_TEXTURE_2D),
  FormatOpt(GL_RGB),
  FilterOpt(GL_NEAREST),
  WrapingOpt(0)
{
}

nsGLI::cGL_Texture::cGL_Texture(ui16 Width, ui16 Height,ui16 arg_TypeOpt, ui16 arg_FormatOpt) :
  TextureID(0),
  Width(Width),
  Height(Height),
  TypeOpt(arg_TypeOpt),
  FormatOpt(arg_FormatOpt),
  FilterOpt(GL_NEAREST),
  WrapingOpt(0)
{
}

nsGLI::cGL_Texture::~cGL_Texture()
{
  GLboolean loc_TexState;
  glAreTexturesResident(1, &TextureID, &loc_TexState);
  if (loc_TexState)
  {
    glDeleteTextures(1, &TextureID);
  }
}

void nsGLI::cGL_Texture::GenerateTexture(void)
{
  glGenTextures(1, &TextureID);
}

void nsGLI::cGL_Texture::BindTexture(void)
{
  glBindTexture(TypeOpt, TextureID);
}
void nsGLI::cGL_Texture::UnBindTexture(void)
{
  glBindTexture(TypeOpt, 0);
}

void nsGLI::cGL_Texture::AlocateDataSpace(void)
{
  glTexImage2D(TypeOpt,0, FormatOpt,Width,Height,0,FormatOpt, GL_UNSIGNED_BYTE, 0);
}

void nsGLI::cGL_Texture::AlocateDataSpaceB(void)
{
  glBindTexture(TypeOpt, TextureID);
  glTexImage2D(TypeOpt, 0, FormatOpt, Width, Height, 0, FormatOpt, GL_UNSIGNED_BYTE, 0);
  glBindTexture(TypeOpt, 0);
}



void nsGLI::cGL_Texture::LoadDataToGpu(void* arg_Data, ui16 arg_DataFormat)
{
  glTexImage2D(TypeOpt, 0, FormatOpt, Width, Height, 0, arg_DataFormat, GL_UNSIGNED_BYTE, arg_Data);
  glGenerateMipmap(TypeOpt);
}

void nsGLI::cGL_Texture::SetParameter(ui16 arg_Parameter, ui16 arg_Value)
{
  glTexParameterf(TypeOpt, arg_Parameter, arg_Value);
}
