
#ifndef CMYWINDOW_H
#define CMYWINDOW_H

#include <iostream>
#include <string>
#include <SDL.h>
#undef main


class cMyWindow
{
  SDL_Window*		myWindow;
  std::string   windowTitle;
  ui32 Width;
  ui32 Height;
  ui32 PosX;
  ui32 PosY;
public:
  SDL_Window * getWinPtr(void){return myWindow;}
  cMyWindow(void);
  cMyWindow(std::string arg_title,int arg_px,int arg_py,int arg_width,int arg_height);
  ~cMyWindow(void);
};
#endif
