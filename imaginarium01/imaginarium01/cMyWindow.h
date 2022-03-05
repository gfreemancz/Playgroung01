
#ifndef CMYWINDOW_H
#define CMYWINDOW_H

#include <iostream>
#include <string>
#include <SDL.h>
#undef main


class cMyWindow
{
  std::string   windowTitle;
  ui32  Width;
  ui32  Height;
  ui32  PosX;
  ui32  PosY;
  float Opacity;
  SDL_Window* myWindow;
public:
  SDL_Window * getWinPtr(void){return myWindow;}
  cMyWindow(void);
  cMyWindow(std::string arg_title,int arg_px,int arg_py,int arg_width,int arg_height, float arg_Opacitz = 1.0f);
  ~cMyWindow(void);
  void setOpacity(float arg_opacity);
  void SwapOglBuffers(void);
  void GetWindowPosition(si32 * arg_x, si32 * arg_y);
  void UpdateWinTitle(std::string arg_NewTitle);
};
#endif
