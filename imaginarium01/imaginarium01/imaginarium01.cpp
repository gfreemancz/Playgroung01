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

#include "cQuaternion.h"


void nsGLI::cOpenGL_Interface::RenderFrame(void)
{
	glClear(CleaningFlags);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


bool g_AppRunning = true;


cTimeMeasure G_LoopTime;
cTimeMeasure G_SwapTime;
cTimeMeasure G_QuatTime;

cMeshT g_testMesh;


void RegisterEventsToHandler(cEventHandler* arg_EventHandler);

cEventHandler G_EventHandler;

ui32 G_FrameTime;
cMyWindow * G_Wokynko = nullptr;

int main(int argc, char *argv[])
{
	
	bool loc_AppRunning = true;


  si32 loc_WinPosX = 255, loc_WinPosY = 512;

  std::cout << "hello world" << std::endl;
  

  RegisterEventsToHandler(&G_EventHandler);

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL could not initialize! SDL_Error:" << SDL_GetError() << std::endl;
	}
	else
	{
		G_Wokynko = new cMyWindow("Imaginarium V0.1.0", 100, 100, 800, 600);
		if (nsGLI::iGlInterface.Init(G_Wokynko) != 0)
		{
			std::cout << "initialization of OpenGL failed" << std::endl;
		}
	}

 
  

   

   cMainApp::Init();
  

   std::cout << "init time: " << std::dec << cMainApp::InitTime.Get_uSec() << std::endl;
//  g_testMesh.LoadModel<cOBJ_loader>("C:\\development\\resources\\Airplane.obj");
  std::cout << "Starting Main Loop" << std::endl;
	
	ui32 loc_cnt = 0U;
	while (g_AppRunning)
	{

    G_LoopTime.Begin();

    

    G_EventHandler.cyclic();
    cMainApp::RunLoop();
		//nsGLI::iGlInterface.RenderFrame();
    G_LoopTime.End();

    G_SwapTime.Begin();

    G_Wokynko->SwapOglBuffers();

    G_SwapTime.End();
    
		if (loc_cnt < 1000U)
	  {
			loc_cnt++;
		}
		else
		{
			loc_cnt = 0U;

      G_Wokynko->GetWindowPosition(&loc_WinPosX, &loc_WinPosY);

      G_FrameTime = G_LoopTime.Get_uSec() + G_SwapTime.Get_uSec();

      ui32 loc_FPS = 1000000 / G_FrameTime;

      std::string loc_NewWinTitpe = std::string("Imaginarium V0.1.0");

      loc_NewWinTitpe += std::string(" FPS :") + std::to_string(loc_FPS);
      loc_NewWinTitpe += std::string(" Frame Time :") + std::to_string(G_FrameTime);
      G_Wokynko->UpdateWinTitle(loc_NewWinTitpe);

		}
	}

	nsGLI::iGlInterface.Clean(G_Wokynko);

	std::cout << "!!!Fuck You World!!!" << std::endl;
  
  return 0; 
}

