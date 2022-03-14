#include "stdafx.h"
#include "cRenderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


cRenderer::cRenderer():
  TargetFrameBuffer(0),
  ShaderProgram(0),
  CleaningFlags(0),
  ClearColor_R(0.0f),
  ClearColor_G(0.0f),
  ClearColor_B(0.0f),
  ClearColor_A(1.0f),
  tmp_mesh()
{
}

cRenderer::cRenderer(nsGLI::cFrameBuffer* arg_TargetFBO):
  TargetFrameBuffer(arg_TargetFBO), 
  ShaderProgram(0),
  CleaningFlags(0),
  ClearColor_R(0.0f),
  ClearColor_G(0.0f),
  ClearColor_B(0.0f),
  ClearColor_A(1.0f),
  tmp_mesh()
{
}


cRenderer::~cRenderer()
{
}

void cRenderer::SetCleanColor(float arg_R, float arg_G, float arg_B, float arg_A)
{
  ClearColor_R = arg_R;
  ClearColor_G = arg_G;
  ClearColor_B = arg_B;
  ClearColor_A = arg_A;
  
}

void cRenderer::Draw(void)
{
  if (TargetFrameBuffer != 0)
  {
  //  TargetFrameBuffer->BindFBO();
  }

  glClearColor(ClearColor_R, ClearColor_G, ClearColor_B, ClearColor_A);
  glClear(CleaningFlags);


  // activate/bind shader program if attached
  if (ShaderProgram != 0)
  {
    ShaderProgram->Use();
  }

  //TODO setup projection (matrix to shader or ogl setting?) - implement camera
  ui32 loc_MVP_id = ShaderProgram->GetUniformLocation("MVP");

  glm::mat4x4 loc_VP = ActiveCamera->GetViewMatrix();
  glm::mat4x4 loc_M = glm::mat4x4(1.0f);
  glm::mat4x4 loc_MVP = loc_VP * loc_M;

  ShaderProgram->SetUniformMatrix4x4(loc_MVP_id, &loc_MVP);

 

  //TODO call "draw package" draw call
  tmp_mesh.Draw();

  //unbind last texture
  //unbind shader program
  if (ShaderProgram != 0)
  {
    ShaderProgram->Stop();
  }

  if (TargetFrameBuffer != 0)
  {
   // TargetFrameBuffer->UnBindFBO();
  }
}

void cRenderer::AsignCamera(cCamera* arg_Camera)
{
  ActiveCamera = arg_Camera;
}
