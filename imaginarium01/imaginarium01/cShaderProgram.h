#pragma once

#include <iostream>
#include <vector>
#include "cShader.h"



class cShaderProgram
{
  GLuint ShaderProgID;
  std::vector<cShader*> ShaderList;

public:
  ui8   InitShaderProgram(cShader *arg_VertexShader, cShader *arg_FragmentShader);
  ui8   InitShaderProgram(cShader *arg_VertexShader, cShader *arg_FragmentShader, cShader *arg_GeometryShader);
  void  Use(void);
  

  cShaderProgram();
  ~cShaderProgram();
};

