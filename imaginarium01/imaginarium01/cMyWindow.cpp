



#include "stdafx.h"
#include "cMyWindow.h"



cMyWindow::cMyWindow(void)
{
  windowTitle.append("default window title");
  PosX = 50;
  PosY = 50;
  Width = 800;
  Height = 600;
  myWindow = SDL_CreateWindow( windowTitle.c_str() , PosX, PosY, Width, Height, SDL_WINDOW_OPENGL ); 
  if( myWindow == NULL ) 
  { 
    std::cout << "Window could not be created! SDL_Error:" << SDL_GetError() << std::endl;
  }
}

cMyWindow::cMyWindow(std::string arg_title,int arg_px,int arg_py,int arg_width,int arg_height)
{
  windowTitle.append(arg_title);
  PosX = arg_px;
  PosY = arg_py;
  Width = arg_width;
  Height = arg_height;

  myWindow = SDL_CreateWindow( windowTitle.c_str() , PosX, PosY, Width, Height, SDL_WINDOW_OPENGL );

  if( myWindow == NULL ) 
  { 
    std::cout << "Window could not be created! SDL_Error:" << SDL_GetError() << std::endl;
  }
}


cMyWindow::~cMyWindow(void)
{
    SDL_DestroyWindow( myWindow );
}
