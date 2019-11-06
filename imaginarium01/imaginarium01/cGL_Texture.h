



#ifndef GLI_CGL_TEXTURE_H
#define GLI_CGL_TEXTURE_H

#ifndef STDAFX_H
#include "stdafx.h"
#endif

#ifndef __glew_h__
#include <glew.h>
#endif

namespace nsGLI {



  class cGL_Texture
  {
  public:
    cGL_Texture();
    cGL_Texture(ui16 Width, ui16 Height, ui16 arg_TypeOpt,ui16 arg_FormatOpt);
    ~cGL_Texture();

    void GenerateTexture(void);
    void BindTexture(void);
    void UnBindTexture(void);
    void AlocateDataSpace(void);
    void AlocateDataSpaceB(void);
    void LoadDataToGpu(void * arg_Data, ui16 arg_DataFormat);
    void SetParameter(ui16 arg_Parameter, ui16 arg_Value);

    GLuint GetTextureId(void) {
      return TextureID;
    }
    ui16 GetTypeOpt(void) {
      return TypeOpt;
    }
    ui16 GetWidth(void) {
      return Width;
    }
    ui16 GetHeight(void) {
      return Height;
    }

  private:
    GLuint TextureID;
    ui16 Width;
    ui16 Height;
    ui16 TypeOpt;
    ui16 FormatOpt;
    ui16 FilterOpt;
    ui16 WrapingOpt;

  };

}
#endif
