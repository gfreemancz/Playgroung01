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

cMesh g_testMesh;

int SDL_main(int argc, char *argv[])
{
	cEventHandler loc_EventHandler;
	bool loc_AppRunning = true;
	cMyWindow * loc_Wokynko = nullptr;

	LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;






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

  g_testMesh.LoadModel<cOBJ_loader>("C:\\development\\resources\\3d-model.obj");
		
	
	ui32 loc_cnt = 0;
	while (g_AppRunning)
	{
    
		QueryPerformanceCounter(&StartingTime);

		loc_EventHandler.cyclic();
		nsGLI::iGlInterface.RenderFrame();

		SDL_GL_SwapWindow(loc_Wokynko->getWinPtr());
		QueryPerformanceCounter(&EndingTime);
		ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
    
		if (loc_cnt < 100)
		{
			loc_cnt++;

		}
		else
		{
			loc_cnt = 0;
			std::cout << ElapsedMicroseconds.QuadPart << std::endl;
		}
	}

	nsGLI::iGlInterface.Clean(loc_Wokynko);

	std::cout << "!!!Fuck You World!!!" << std::endl;
  
  return 0; 
}

