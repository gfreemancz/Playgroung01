/*
 * cOpenGLInterface.h
 *
 *  Created on: 19. 2. 2017
 *      Author: GFreeman
 */

#ifndef COPENGLINTERFACE_H_
#define COPENGLINTERFACE_H_
#include "StdAfx.h"
#include <string>
#include <map>

//#define GLEW_STATIC
#include <glew.h>
#include <GL\GL.h>
#include <GL\GLU.h>

#ifndef CMYWINDOW_H
  #include "cMyWindow.h"
#endif

namespace nsGLI {

class cOpenGL_Interface
{
  SDL_GLContext GLContext;
  std::string  OpenGLVersion;
  ui32 CleaningFlags;
  float ClearColor[4];
  std::map<GLenum , ui32>  GL_Info;
public:
	ui8 Init(cMyWindow * arg_Wokynko);
	ui8 Clean(cMyWindow * arg_Wokynko);

	std::string GetGLVersionStr(void){return OpenGLVersion;}
	void RenderFrame(void);
	void setCleaningFlags(ui32 arg_flag){CleaningFlags |=arg_flag;}
	void resetCleaningFlags(void){CleaningFlags =0;}
	void setClearColor(float arg_R, float arg_G, float arg_B, float arg_A);
	si32 getGLIngo(GLenum  arg_parameter);
	si32 readGLIngo(GLenum  arg_parameter);

};
extern cOpenGL_Interface iGlInterface;
}
#endif /* COPENGLINTERFACE_H_ */
