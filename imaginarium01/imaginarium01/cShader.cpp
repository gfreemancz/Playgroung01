#include "stdafx.h"
#include "cShader.h"
#include <fstream>
#include <sstream>



cShader::cShader(std::string arg_ShaderFileName, ui16 arg_ShaderType):
  ShaderID(0UL),
  ShaderType(arg_ShaderType),
  ShaderProgramString("")
{
  std::ifstream loc_ShaderFile;
 
  loc_ShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try //try to load Shader code from textfile
  {
    loc_ShaderFile.open(arg_ShaderFileName);
    std::stringstream loc_ShaderStream;
    loc_ShaderStream << loc_ShaderFile.rdbuf();
    loc_ShaderFile.close();
    ShaderProgramString = loc_ShaderStream.str();
  }
  catch(std::ifstream::failure e) 
  {    //if File is not possible to open, report error
    std::cout << "error: failed to open Shader Source file \""<< arg_ShaderFileName <<" \"" << std::endl;
  }  
}

ui8 cShader::InitShader(void)
{
  ui8 loc_RetValue = 0;
  GLint   loc_GL_ResultStatus;
  GLchar  loc_GL_infoLog[1024];
  const GLchar  *locP_ShaderSource = ShaderProgramString.c_str();

  ShaderID = glCreateShader(ShaderType);                   // create/alocate shader in GPU
  glShaderSource(ShaderID, 1, &locP_ShaderSource, NULL);   // load shader data
  glCompileShader(ShaderID);                               // compile Shader
  glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &loc_GL_ResultStatus); // check shader compilation status
  if (!loc_GL_ResultStatus)
  {  // if shader compilation failed - report error
    glGetShaderInfoLog(ShaderID, 1023, NULL, loc_GL_infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << loc_GL_infoLog << std::endl;
    loc_RetValue++;
  }
  return loc_RetValue;
}

cShader::~cShader()
{
  if (ShaderID != 0)
  {
    glDeleteShader(ShaderID);
  }
}
