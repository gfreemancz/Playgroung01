



#include "stdafx.h"
#include "cMyWindow.h"



cMyWindow::cMyWindow(void):
  windowTitle("default window title"),
  Width(50),
  Height(50),
  PosX(800),
  PosY(600),
  Opacity(0.0f)
{
 
  myWindow = SDL_CreateWindow( windowTitle.c_str() , PosX, PosY, Width, Height, SDL_WINDOW_OPENGL ); 
  if( myWindow == NULL ) 
  { 
    std::cout << "Window could not be created! SDL_Error:" << SDL_GetError() << std::endl;
  }
  SDL_SetWindowOpacity(myWindow, 1.0f);
}

cMyWindow::cMyWindow(std::string arg_title,int arg_px,int arg_py,int arg_width,int arg_height, float arg_Opacity):
  windowTitle(arg_title),
  Width(arg_width),
  Height(arg_height),
  PosX(arg_px),
  PosY(arg_py),
  Opacity(arg_Opacity)
{
  myWindow = SDL_CreateWindow(windowTitle.c_str(), PosX, PosY, Width, Height, SDL_WINDOW_OPENGL );
  //myWindow = SDL_CreateWindow( windowTitle.c_str() , PosX, PosY, Width, Height, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS);

  if( myWindow == NULL ) 
  { 
    std::cout << "Window could not be created! SDL_Error:" << SDL_GetError() << std::endl;
  }
  SDL_SetWindowOpacity(myWindow, arg_Opacity);
}


cMyWindow::~cMyWindow(void)
{
    SDL_DestroyWindow( myWindow );
}

void cMyWindow::setOpacity(float arg_opacity)
{
  Opacity = arg_opacity;
  SDL_SetWindowOpacity(myWindow, arg_opacity);
}

void cMyWindow::SwapOglBuffers(void)
{
  SDL_GL_SwapWindow(myWindow);
}

void cMyWindow::GetWindowPosition(si32 * arg_x, si32 * arg_y)
{
  SDL_GetWindowPosition(myWindow, (int *)arg_x, (int *)arg_y);
  PosX = *arg_x;
  PosY = *arg_y;
}

void cMyWindow::UpdateWinTitle(std::string arg_NewTitle)
{
  SDL_SetWindowTitle(myWindow, arg_NewTitle.c_str());
  windowTitle.clear();
  windowTitle.append(arg_NewTitle);
}
