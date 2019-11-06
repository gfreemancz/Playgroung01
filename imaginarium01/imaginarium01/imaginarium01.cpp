// imaginarium01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>

#ifndef SDL_h_
  #include <SDL.h>
#endif

#ifndef CMYWINDOW_H
  #include "cMyWindow.h"
#endif

#ifndef CEVENTHANDLER_H_
  #include "cEventHandler.h"
#endif

#ifndef COPENGLINTERFACE_H_
  #include "GLI/cOpenGLInterface.h"
#endif

#include "cMesh.h"
#include "cOBJ_loader.h"

#include "cBaseEngineObject.h"

#include "cShader.h"
#include "cShaderProgram.h"

#include "cTimeMeasure.h"

#include "cMainApp.h"




void nsGLI::cOpenGL_Interface::RenderFrame(void)
{
	glClear(CleaningFlags);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

class cQuitAppCommand : public cCommandBase
{
public:
	~cQuitAppCommand() {};
	void execute(void * arg_argument)
	{
		(void)arg_argument;
		extern bool g_AppRunning;
		g_AppRunning = false;
	}
};

bool g_AppRunning = true;


cTimeMeasure G_LoopTime;
cTimeMeasure G_SwapTime;

cMesh g_testMesh;

cShader testShader_V(std::string("../Shaders/VertexShader01.glsl"), GL_VERTEX_SHADER);
cShader testShader_F(std::string("../Shaders/FragmentShader01.glsl"),GL_FRAGMENT_SHADER);
cShaderProgram testShaderProgram;

int main(int argc, char *argv[])
{
	cEventHandler loc_EventHandler;
	bool loc_AppRunning = true;
	cMyWindow * loc_Wokynko = nullptr;



  std::cout << "hello world" << std::endl;

	loc_EventHandler.RegisterEvent(static_cast<ui32>(SDL_QUIT), new cQuitAppCommand());

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL could not initialize! SDL_Error:" << SDL_GetError() << std::endl;
	}
	else
	{
		loc_Wokynko = new cMyWindow("Imaginarium V0.1.0", 100, 100, 800, 600);
		if (nsGLI::iGlInterface.Init(loc_Wokynko) != 0)
		{
			std::cout << "initialization of OpenGL failed" << std::endl;
		}
	}


  testShader_V.InitShader();
  testShader_F.InitShader();

  testShaderProgram.InitShaderProgram(&testShader_V, &testShader_F);


  cMainApp::Init();



 // g_testMesh.LoadModel<cOBJ_loader>("C:\\development\\resources\\3d-model.obj");
  std::cout << "Starting Main Loop" << std::endl;
	
	ui32 loc_cnt = 0U;
	while (g_AppRunning)
	{
    
    G_LoopTime.Begin();

		loc_EventHandler.cyclic();
		nsGLI::iGlInterface.RenderFrame();
    G_LoopTime.End();

    G_SwapTime.Begin();
		SDL_GL_SwapWindow(loc_Wokynko->getWinPtr());
    G_SwapTime.End();
    
		if (loc_cnt < 100U)
	  {
			loc_cnt++;
		}
		else
		{
			loc_cnt = 0U;
			std::cout << G_LoopTime.Get_mSec() << std::endl;
		}
	}

	nsGLI::iGlInterface.Clean(loc_Wokynko);

	std::cout << "!!!Fuck You World!!!" << std::endl;
  
  return 0; 
}

