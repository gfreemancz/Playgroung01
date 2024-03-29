#include "stdafx.h"
#include "cTexture.h"
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_error.h"



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
  delete TextureDataPtr;
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

ui8 cTexture::LoadPictureFromFile(std::string arg_FileName)
{
  ui8 loc_ReturnValue = 0U;
  SDL_Surface* loc_PictureSurface;
  ui8* loc_DataPtr;
  ui8* loc_SrcPtr;
  ui32 loc_DataSize;
  ui16 loc_colorFormat = GL_RGBA;
  ui32 loc_LineDataSize;


  loc_PictureSurface = IMG_Load(arg_FileName.c_str());
  if (loc_PictureSurface)
  {
    loc_LineDataSize = loc_PictureSurface->h * loc_PictureSurface->format->BytesPerPixel;

    loc_DataSize = loc_PictureSurface->w * loc_LineDataSize;

    loc_DataPtr = new ui8[loc_DataSize];

    loc_SrcPtr = (ui8*)loc_PictureSurface->pixels;

    for (ui32 loc_idx = 0; loc_idx < loc_PictureSurface->h; loc_idx++)
    {
      memcpy(&loc_DataPtr[loc_idx* loc_LineDataSize], &loc_SrcPtr[(loc_PictureSurface->h-loc_idx+1)* loc_LineDataSize], loc_LineDataSize);

    }

    if (loc_PictureSurface->format->BytesPerPixel == 3)
    {
      loc_colorFormat = GL_RGB;
    }

    Init(loc_PictureSurface->w, loc_PictureSurface->h, loc_colorFormat,loc_DataPtr,1);


    SDL_FreeSurface(loc_PictureSurface);

  }
  else
  {
    std::cout << IMG_GetError() << std::endl;
  }
  return loc_ReturnValue;
}


