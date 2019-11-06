#include "stdafx.h"
#include "cRenderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


cRenderer::cRenderer():
  TargetFrameBuffer(0),
  CleaningFlags(0)
{
}

cRenderer::cRenderer(nsGLI::cFrameBuffer* arg_TargetFBO):
  TargetFrameBuffer(arg_TargetFBO),
  CleaningFlags(0)
{
}


cRenderer::~cRenderer()
{
}

void cRenderer::Draw(void)
{
  if (TargetFrameBuffer != 0)
  {
    TargetFrameBuffer->BindFBO();
  }

  glClear(CleaningFlags);

  glm::mat4 projMat = glm::ortho(0, 800, 0, 600, -1, 1);




  if (TargetFrameBuffer != 0)
  {
    TargetFrameBuffer->UnBindFBO();
  }
}
