/*
 * cGeometryDataBuffer.h
 *
 *  Created on: 6. 3. 2017
 *      Author: GFreeman
 */

#ifndef GLI_CMESH_H_
#define GLI_CMESH_H_

#ifndef STDAFX_H
  #include "stdafx.h"
#endif
#include <vector>
#ifndef __glew_h__
  #include <glew.h>
#endif

#ifndef MATH_NSMATH_H_
#include "math/nsMath.h"
#endif

namespace nsGraphic {

struct sVertex
{
  nsMath::tVector3f Position;
  nsMath::tVector3f Normal;
  nsMath::tVector2f UVCoordinates;
};

class cMesh
{
private:
  struct sMeshElement
  {
    ui32 IdxOffset;
    ui32 IdxCount;
    ui32 MaterialID;
  };

  GLuint VertexArrayID;
  GLuint VertexBufferID;
  GLuint IndexBufferID;
  std::vector<sVertex> VertexData;
  std::vector<ui32>    IdxData;
  std::vector<sMeshElement> Elements;
public:
  cMesh();
  ~cMesh();
  void InitGeometry(void * data,const ui32 dSize, void * dataI,const  ui32 dSizeI,const GLenum  usage);
  void BindBuffer(void);

  GLuint getIndexBufferId() const
  {
    return IndexBufferID;
  }

  GLuint getVertexBufferId() const
  {
    return VertexBufferID;
  }

  GLuint getVertexArrayId() const
  {
    return VertexArrayID;
  }

};

} /* namespace nsGLI */

#endif /* GLI_CMESH_H_ */
