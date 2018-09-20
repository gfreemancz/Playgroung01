/*
 * cGLSLprogram.cpp
 *
 *  Created on: 4. 3. 2017
 *      Author: GFreeman
 */

#ifndef STDAFX_H
#include "stdafx.h"
#endif
#include <GLI/cGLSLprogram.h>
#include <iostream>
#include <sstream>

namespace nsGLI {

cGLSLprogram::cGLSLprogram():
    VProgramSource(),
    FProgramSource(),
    GProgramSource(),
    ProgramID(0),
    V_ShaderID(0),
    F_ShaderID(0),
    G_ShaderID(0)
{
  // TODO Auto-generated constructor stub

}

cGLSLprogram::~cGLSLprogram()
{
  VProgramSource.clear();
  FProgramSource.clear();
  GProgramSource.clear();
  if(V_ShaderID!=0U)glDeleteShader(V_ShaderID);
  if(F_ShaderID!=0U)glDeleteShader(F_ShaderID);
  if(G_ShaderID!=0U)glDeleteShader(G_ShaderID);
  if(ProgramID!=0U) glDeleteShader(ProgramID);

}

bool cGLSLprogram::InitShader(GLenum arg_eShaderType, const std::string& arg_strShaderSource)
{
  bool loc_ReturnValue = true;
  GLuint * loc_NewShader;
  std::string& loc_NewShaderSource = VProgramSource;
  switch(arg_eShaderType)
  {
    case GL_VERTEX_SHADER:
      loc_NewShader = &V_ShaderID;
      loc_NewShaderSource = VProgramSource;
      break;
    case GL_GEOMETRY_SHADER:
      loc_NewShader = &G_ShaderID;
      loc_NewShaderSource = GProgramSource;
      break;
    case GL_FRAGMENT_SHADER:
      loc_NewShader = &F_ShaderID;
      loc_NewShaderSource = FProgramSource;
      break;
    default:
      loc_ReturnValue = false;
      std::cerr<<"Wrong shader type selected"<<std::endl;
      break;
  }
  loc_NewShaderSource.clear();
  loc_NewShaderSource.append(arg_strShaderSource);

  if(loc_NewShader !=0)
  {
    glDeleteShader(*loc_NewShader);
  }

  *loc_NewShader = glCreateShader(arg_eShaderType);
  glShaderSource(*loc_NewShader, 1, reinterpret_cast<const char * const*>(loc_NewShaderSource.c_str()), NULL);
  glCompileShader(*loc_NewShader);

  GLint status;
  glGetShaderiv(*loc_NewShader, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE)
  {
    GLint infoLogLength;
    glGetShaderiv(*loc_NewShader, GL_INFO_LOG_LENGTH, &infoLogLength);

    GLchar *strInfoLog = new GLchar[infoLogLength + 1];
    glGetShaderInfoLog(*loc_NewShader, infoLogLength, NULL, strInfoLog);

    const char *strShaderType = NULL;
    switch(arg_eShaderType)
    {
      case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
      case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
      case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
    }
    std::cerr<<"chybicka"<<std::endl;
    std::cerr<< "Compile failure in %s shader:\n%s\n" << strShaderType << strInfoLog << std::endl;

    delete[] strInfoLog;
    loc_ReturnValue = false;
  }

  return loc_ReturnValue;
}

void cGLSLprogram::Start(void)
{
  glUseProgram(ProgramID);
}


void cGLSLprogram::Stop(void)
{
  glUseProgram(0);
}


bool cGLSLprogram::InitUniformVariables(void)
{
  bool loc_RetrunValue = true;

  if(V_ShaderID != 0)
  {
    std::istringstream loc_SourceStream(VProgramSource);
    std::string loc_Word;
    while(!loc_SourceStream.eof())
    {
      loc_SourceStream >> loc_Word;
      if(loc_Word.compare("uniform"))
      {

      }
    }

  }



  return loc_RetrunValue;
}



} /* namespace nsGLI */
