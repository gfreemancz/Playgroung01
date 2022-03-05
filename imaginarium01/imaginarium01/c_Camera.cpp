#include "c_Camera.h"

cCamera::cCamera() :
  vPosition(glm::vec3(0, 0, 0)),
  vTarget(glm::vec3(0, 0, 0)),
  vUp(glm::vec3(0, 1, 0)),
  ScaleFactor(0.5f)
{
}

cCamera::cCamera(glm::vec3 arg_pos, glm::vec3 arg_target, glm::vec3 arg_Up) :
  vPosition(arg_pos),
  vTarget(arg_target),
  vUp(arg_Up),
  ScaleFactor(0.5f)
{
}

glm::mat4x4 cCamera::GetViewMatrix(void)
{
  glm::mat4x4 loc_ViewMatrix = glm::lookAt(vPosition, vTarget, vUp);
  return loc_ViewMatrix;
}

void cCamera::MoveForwardBackward(float arg_step)
{
  vPosition += glm::normalize(vTarget) * arg_step;
}

void cCamera::MoveLeftRight(float arg_step)
{
  glm::vec3 loc_SideNormal = glm::cross(vTarget, vUp);
  vPosition += glm::normalize(loc_SideNormal) * arg_step;
}

void cCamera::MoveUpDown(float arg_step)
{
  vPosition += glm::normalize(vUp) * arg_step;
}
