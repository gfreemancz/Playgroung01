#pragma once

#include <iostream>
#include <string>

//#define GLEW_STATIC
#include <glew.h>
#include <GL\GL.h>
#include <GL\GLU.h>



class cShader
{
  ui32 ShaderID;
  ui16 ShaderType;
  std::string ShaderProgramString;
public:
  cShader() :ShaderID(0UL), ShaderType(0U),ShaderProgramString(""){}
  cShader(std::string arg_ShaderFileName, ui16 arg_ShaderType );
  ui8  InitShader(void);
  ui32 getID(void) { return ShaderID; }
  ~cShader();
};

