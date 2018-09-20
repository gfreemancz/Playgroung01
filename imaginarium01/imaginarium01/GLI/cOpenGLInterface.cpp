/*
 * cOpenGLInterface.cpp
 *
 *  Created on: 19. 2. 2017
 *      Author: GFreeman
 */

#include "GLI/cOpenGLInterface.h"



#include <SDL.h>
#include <SDL_opengl.h>

#include <iostream>

namespace nsGLI {

ui8 cOpenGL_Interface::Init(cMyWindow * arg_Wokynko)
{
  ui8 loc_ReturnValue = 0U;

  GLContext = SDL_GL_CreateContext( arg_Wokynko->getWinPtr());

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << "inicializace glew se posrala "<< std::endl;
		loc_ReturnValue = 1U;
	}

	GLenum error = GL_NO_ERROR;

  //Initialize Projection Matrix
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();

  //Check for error
  error = glGetError();
  if( error != GL_NO_ERROR )
  {
    //  printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
      loc_ReturnValue = 2U;
  }

  //Initialize Modelview Matrix
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  //Check for error
  error = glGetError();
  if( error != GL_NO_ERROR )
  {
//      printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
      loc_ReturnValue = 3U;
  }
  //Initialize clear color
  ClearColor[0] = 0.0f;
  ClearColor[1] = 0.0f;
  ClearColor[2] = 0.0f;
  ClearColor[3] = 1.0f;
  glClearColor( ClearColor[0], ClearColor[1], ClearColor[2], ClearColor[3] );

  //Check for error
  error = glGetError();
  if( error != GL_NO_ERROR )
  {
//      printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
      loc_ReturnValue = 4U;
  }
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  glFrontFace(GL_CCW);
  glEnable(GL_CULL_FACE);

  glClearDepth(1.0); // Nastavení hloubkového bufferu

  glDepthFunc(GL_LESS);// Typ hloubkového testování


  glEnable(GL_DEPTH_TEST);// Zapne hloubkové testování

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  const ui8 * test = glGetString(GL_VERSION);
  OpenGLVersion.append(reinterpret_cast<const char *>(test));

	return loc_ReturnValue;
}

ui8 nsGLI::cOpenGL_Interface::Clean(cMyWindow* arg_Wokynko)
{
  (void)arg_Wokynko; //TODO check if needed
  SDL_GL_DeleteContext( GLContext);
  return 0U;
}

void cOpenGL_Interface::setClearColor(float arg_R, float arg_G,
    float arg_B, float arg_A)
{
  ClearColor[0] = arg_R;
  ClearColor[1] = arg_G;
  ClearColor[2] = arg_B;
  ClearColor[3] = arg_A;
  glClearColor( ClearColor[0], ClearColor[1], ClearColor[2], ClearColor[3] );
}

si32 cOpenGL_Interface::readGLIngo(GLenum  arg_parameter)
{
  si32 loc_Data;
  glGetIntegerv(arg_parameter,reinterpret_cast<int*>(&loc_Data));
  GL_Info.insert(std::make_pair(arg_parameter, loc_Data));
  return loc_Data;
}

si32 cOpenGL_Interface::getGLIngo(GLenum  arg_parameter)
{
  return GL_Info[arg_parameter];
}

cOpenGL_Interface iGlInterface;



}
