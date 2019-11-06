#include "stdafx.h"
#include "cTexture.h"
#include <iostream>




cTexture::cTexture():
  TextureUnitUsed(0U),
  TextureID(0U),
  TextureDataPtr(nullptr),
  Widht(0U),
  Height(0U),
  DataFormat(GL_RGBA),
  WrapType_U(GL_REPEAT),
  WrapType_W(GL_REPEAT),
  FilterTypeMin(GL_LINEAR),
  FilterTypeMag(GL_LINEAR)
{
}

cTexture::cTexture(bool arg_StoreData) :
  TextureUnitUsed(0U),
  TextureID(0U),
  TextureDataPtr(nullptr),
  Widht(0U),
  Height(0U),
  DataFormat(GL_RGBA),
  WrapType_U(GL_REPEAT),
  WrapType_W(GL_REPEAT),
  FilterTypeMin(GL_LINEAR),
  FilterTypeMag(GL_LINEAR)
{
}


cTexture::~cTexture()
{
}

void cTexture::Init(ui32 arg_width, ui32 arg_height, ui16 arg_DataFormat, ui8 * arg_DataPtr, ui16 arg_TextureUnitUsed)
{
  Widht = arg_width;
  Height = arg_height;
  DataFormat = arg_DataFormat;
  TextureDataPtr = arg_DataPtr;
  TextureUnitUsed = arg_TextureUnitUsed;
}

void cTexture::InitAndLoadToGpu(ui32 arg_width, ui32 arg_height, ui16 arg_DataFormat, ui8 * arg_DataPtr, ui16 arg_TextureUnitUsed)
{
  Init(arg_width, arg_height, arg_DataFormat, arg_DataPtr,  arg_TextureUnitUsed);
  LoadToGpu();
}



ui8 cTexture::LoadToGpu(void)
{
  ui8 loc_ReturnValue = 0U;


  glGenTextures(1, &TextureID);
  glBindTexture(GL_TEXTURE_2D, TextureID);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WrapType_U);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WrapType_W);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FilterTypeMin);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FilterTypeMag);

  if (TextureDataPtr != nullptr)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, DataFormat, Widht, Height, 0, DataFormat, GL_UNSIGNED_BYTE, TextureDataPtr);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    loc_ReturnValue++;
    std::cout << "Failed to load texture to GPU (null pointer to texture data)" << std::endl;
    //TODO better error logging
  }

  return loc_ReturnValue;
}

void cTexture::BindTexture(void)
{
  glActiveTexture(TextureUnitUsed);
  glBindTexture(GL_TEXTURE_2D, TextureID);
}

void cTexture::UnBindTexture(void)
{
  glActiveTexture(TextureUnitUsed);
  glBindTexture(GL_TEXTURE_2D, 0);
}


