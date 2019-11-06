#pragma once
#include <vector>
#include <string>

#include <glew.h>
#include <GL\GL.h>
#include <GL\GLU.h>

class cTexture
{
  ui16 TextureUnitUsed;
  GLuint TextureID;
  ui8* TextureDataPtr;
  ui32 Widht;
  ui32 Height;
  ui16 DataFormat;
  ui16 WrapType_U;
  ui16 WrapType_W;
  ui16 FilterTypeMin;
  ui16 FilterTypeMag;

public:
  cTexture();
  cTexture(bool arg_StoreData);
  ~cTexture();
  // GETers and SETers
  void Set_TextureUnitUsed(ui8 arg_value) { TextureUnitUsed = arg_value; }
  ui16 Get_TextureUnitUsed(void) { return TextureUnitUsed; }
  ui32 Get_TextureID(void) { return TextureID; }
  ui8* Get_TextureDataPtr(void) { return TextureDataPtr; }
  ui32 GetWidth(void) { return Widht; }
  ui32 GetHeight(void) { return Height; }
  ui16 GetDataFormat(void) { return DataFormat; }
  ui16 Get_FilterTypeMag(void) { return FilterTypeMag; }
  void Set_FilterTypeMag(ui16 arg_Value){FilterTypeMag = arg_Value;}
  ui16 Get_FilterTypeMin(void) { return FilterTypeMin; }
  void Set_FilterTypeMin(ui16 arg_Value) { FilterTypeMin = arg_Value; }
  ui16 Get_WrapType_U(void) { return WrapType_U; }
  void Set_WrapType_U(ui16 arg_Value) { WrapType_U = arg_Value; }
  ui16 Get_WrapType_W(void) { return WrapType_W; }
  void Set_WrapType_W(ui16 arg_Value) { WrapType_W = arg_Value; }

  // other methods
  void Init(ui32 arg_width, ui32 arg_height, ui16 arg_DataFormat, ui8 * arg_DataPtr,  ui16 arg_TextureUnitUsed);
  void InitAndLoadToGpu(ui32 arg_width, ui32 arg_height, ui16 arg_DataFormat, ui8 * arg_DataPtr, ui16 arg_TextureUnitUsed);
  ui8  LoadToGpu(void);
  void BindTexture(void);
  void UnBindTexture(void);

};

