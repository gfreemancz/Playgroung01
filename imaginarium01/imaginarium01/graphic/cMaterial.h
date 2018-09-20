/*
 * cMaterial.h
 *
 *  Created on: 12. 3. 2017
 *      Author: GFreeman
 */

#ifndef GRAPHIC_CMATERIAL_H_
#define GRAPHIC_CMATERIAL_H_

#ifndef STDAFX_H
#include "stdafx.h"
#endif

#include <vector>
#include <string>

#ifndef __glew_h__
  #include <glew.h>
#endif

namespace nsGraphic {

class cMaterial
{
  struct sTextureDataInfo
  {
    ui32 Width;
    ui32 Height;
    ui8  PixelSize;
  };
  std::vector<GLuint> TexteureID;
  std::vector<void *> TexteureDataPtr;
  std::vector<sTextureDataInfo> TexteureDataInfo;
  std::string         MaterialName;
public:
  cMaterial();
  ~cMaterial();
};

} /* namespace nsGraphic */

#endif /* GRAPHIC_CMATERIAL_H_ */
