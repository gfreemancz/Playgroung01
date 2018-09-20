/*
 * cGLSLprogram.h
 *
 *  Created on: 4. 3. 2017
 *      Author: GFreeman
 */

#ifndef GLI_CGLSLPROGRAM_H_
#define GLI_CGLSLPROGRAM_H_

#ifndef STDAFX_H
#include "stdafx.h"
#endif

#include <string>

#ifndef __glew_h__
  #include <glew.h>
#endif


namespace nsGLI {

//enum
//{
//  eFLOAT,
//  eINT,
//  eUINT,
//  eVEC2I,
//  eVEC3I,
//  eVEC4I,
//  eVEC2UI,
//  eVEC3UI,
//  eVEC4UI,
//  eVEC2F,
//  eVEC3F,
//  eVEC4F,
//  eMATRIX2F,
//  eMATRIX3F,
//  eMATRIX4F
//} eUniformVarType;

struct sUniformVarInfo
{
};


class cGLSLprogram
{
  std::string VProgramSource;
  std::string FProgramSource;
  std::string GProgramSource;
  GLuint      ProgramID;
  GLuint      V_ShaderID;
  GLuint      F_ShaderID;
  GLuint      G_ShaderID;

public:
  cGLSLprogram();
  ~cGLSLprogram();
  
  bool InitProgram(void);
  bool InitShader(GLenum eShaderType, const std::string &strShaderSource);
  bool InitUniformVariables(void);

  void Start(void);
  void Stop(void);

  std::string& getVProgramSource(void){return VProgramSource;}
  std::string& getFProgramSource(void){return FProgramSource;}
  std::string& getGProgramSource(void){return GProgramSource;}

};

} /* namespace nsGLI */

#endif /* GLI_CGLSLPROGRAM_H_ */
