#pragma once

#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"



class cCamera
{
public:
  cCamera();
  cCamera(glm::vec3 arg_pos, glm::vec3 arg_target, glm::vec3 arg_Up);
  glm::mat4x4 GetViewMatrix(void);
  void        SetCameraScale(float arg_Scale) { ScaleFactor = arg_Scale; }
  void        MoveForwardBackward(float arg_step);
  void        MoveLeftRight(float arg_step);
  void        MoveUpDown(float arg_step);
  void        RotateLeftRight(float arg_step);
  void        RotateUpDown(float arg_step);
private:
  glm::vec3 vPosition;
  glm::vec3 vTarget;
  glm::vec3 vUp;

  glm::mat4 Projection;

  

  float     ScaleFactor;

};

