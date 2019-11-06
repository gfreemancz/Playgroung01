#pragma once
#include <string>
#include "glm.hpp"




class cGLSL_UniformVariable
{
  enum eDataType
  {
    e_Int,
    e_Float,
    e_Vec2F,
    e_Vec2I,
    e_Vec3F,
    e_Vec3I,
    e_Vec4F,
    e_Vec4I
  };

  ui32 VariableLocation;
  eDataType DataType;
public:
  cGLSL_UniformVariable( ui32 arg_ShaderProgramID, std::string arg_VariableName, eDataType arg_type);
  ~cGLSL_UniformVariable();

  //float
  void SetValue(float arg_A);
  void SetValue(float arg_A, float arg_B);
  void SetValue(float arg_A, float arg_B, float arg_C);
  void SetValue(float arg_A, float arg_B, float arg_C, float arg_D);
  //arrays (of float or float vectors)
  void SetValue(float *arg_A, ui32 arg_count);
  void SetValue(glm::vec2 *arg_A, ui32 arg_count);
  void SetValue(glm::vec3 *arg_A, ui32 arg_count);
  void SetValue(glm::vec4 *arg_A, ui32 arg_count);
};

