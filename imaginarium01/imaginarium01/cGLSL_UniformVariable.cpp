#include "stdafx.h"
#include "cGLSL_UniformVariable.h"
#include <glew.h>
#include <GL\GL.h>
#include <GL\GLU.h>


cGLSL_UniformVariable::cGLSL_UniformVariable(ui32 arg_ShaderProgramID, std::string arg_VariableName, eDataType arg_type):
  VariableLocation(0UL),
  DataType(arg_type)
{
  VariableLocation = glGetUniformLocation(arg_ShaderProgramID, arg_VariableName.c_str());
}


cGLSL_UniformVariable::~cGLSL_UniformVariable()
{
  
}

void cGLSL_UniformVariable::SetValue(float arg_A)
{
  glUniform1f(VariableLocation, arg_A);
}

void cGLSL_UniformVariable::SetValue(float arg_A, float arg_B)
{
  glUniform2f(VariableLocation, arg_A, arg_B);
}

void cGLSL_UniformVariable::SetValue(float arg_A, float arg_B, float arg_C)
{
  glUniform3f(VariableLocation, arg_A, arg_B, arg_C);
}

void cGLSL_UniformVariable::SetValue(float arg_A, float arg_B, float arg_C, float arg_D)
{
  glUniform4f(VariableLocation, arg_A, arg_B, arg_C, arg_D);
}

void cGLSL_UniformVariable::SetValue(float * arg_A, ui32 arg_count)
{
  glUniform1fv(VariableLocation, arg_count, arg_A);
}

void cGLSL_UniformVariable::SetValue(glm::vec2 * arg_A, ui32 arg_count)
{
  glUniform2fv(VariableLocation, arg_count, reinterpret_cast<const GLfloat *>(arg_A));
}

void cGLSL_UniformVariable::SetValue(glm::vec3 * arg_A, ui32 arg_count)
{
  glUniform3fv(VariableLocation, arg_count, reinterpret_cast<const GLfloat *>(arg_A));
}

void cGLSL_UniformVariable::SetValue(glm::vec4 * arg_A, ui32 arg_count)
{
  glUniform4fv(VariableLocation, arg_count, reinterpret_cast<const GLfloat *>(arg_A));
}



