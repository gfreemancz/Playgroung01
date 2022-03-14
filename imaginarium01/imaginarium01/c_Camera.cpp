#include "c_Camera.h"

#include "glm/gtc/quaternion.hpp"

#include <iostream>


static const float RotationAngleStep = 1.0f;

cCamera::cCamera() :
  vPosition(glm::vec3(0, 0, 0)),
  vTarget(glm::vec3(0, 0, 0)),
  vUp(glm::vec3(0, 1, 0)),
  Projection(glm::mat4x4(1.0F)),
  ScaleFactor(0.5f)
{


}

cCamera::cCamera(glm::vec3 arg_pos, glm::vec3 arg_target, glm::vec3 arg_Up) :
  vPosition(arg_pos),
  vTarget(arg_target),
  vUp(arg_Up),
  Projection(glm::mat4x4(1.0F)),
  ScaleFactor(0.5f)
{
  Projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);

}

glm::mat4x4 cCamera::GetViewMatrix(void)
{
  glm::mat4x4 loc_ViewMatrix = glm::lookAt(vPosition, vPosition+vTarget, vUp);
  return Projection * loc_ViewMatrix;
}

void cCamera::MoveForwardBackward(float arg_step)
{
  vPosition += glm::normalize(-vTarget) * arg_step;
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

void cCamera::RotateLeftRight(float arg_step)
{
  float loc_AngleRad = arg_step / 180.0f;
  float w = glm::cos(loc_AngleRad / 2);
  float v = glm::sin(loc_AngleRad / 2);
  glm::vec3 qv = vUp * v;
  glm::quat qRotation;

  qRotation = glm::quat(w, qv);
  vTarget = glm::conjugate(qRotation) * vTarget * qRotation;
}

void cCamera::RotateUpDown(float arg_step)
{
  float loc_AngleRad = arg_step / 180.0f;
  float w = glm::cos(loc_AngleRad / 2);
  float v = glm::sin(loc_AngleRad / 2);
  glm::vec3 loc_SideNormal = glm::cross(vTarget, vUp);
  glm::vec3 qv = loc_SideNormal * v;
  glm::quat qRotation;
  qRotation = glm::quat(w, qv);
  vTarget = glm::conjugate(qRotation) * vTarget * qRotation;
}
