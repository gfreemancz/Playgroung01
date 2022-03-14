#pragma once

#include <iostream>
#include <vector>
#include "cShader.h"
#include "glm/mat4x4.hpp"



class cShaderProgram
{
  GLuint ShaderProgID;
  std::vector<cShader*> ShaderList;

public:
  ui8   InitShaderProgram(cShader *arg_VertexShader, cShader *arg_FragmentShader);
  ui8   InitShaderProgram(cShader *arg_VertexShader, cShader *arg_FragmentShader, cShader *arg_GeometryShader);
  void  Use(void);
  void  Stop(void);

  ui32 GetUniformLocation(std::string arg_UniformVariableName);
  void SetUniformMatrix4x4(ui32 arg_id , glm::mat4x4* arg_MatrixPtr);
  //TODO implement interfaces to other data types - ui32, float, vector (2 .. 4) and anz other needed
  

  cShaderProgram();
  ~cShaderProgram();
};

