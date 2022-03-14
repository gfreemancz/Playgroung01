



#ifndef CEVENTHANDLER_H_
  #include "cEventHandler.h"
#endif

#include "cKeyBasedControlHandler.h"

#include "c_Camera.h"

#ifndef CMYWINDOW_H
#include "cMyWindow.h"
#endif




bool G_MouseControlCamera = false;

class cQuitAppCommand : public cCommandBase
{
public:
  ~cQuitAppCommand() {};
  void execute(void* arg_argument)
  {
    (void)arg_argument;
    extern bool g_AppRunning;
    g_AppRunning = false;
  }
};



class cCameraBackward : public cCommandBase
{
public:
  ~cCameraBackward() {};
  void execute(void* arg_argument)
  {
    (void)arg_argument;
    extern cCamera iMainCamera;
    extern ui32 G_FrameTime;
    float loc_Step = 1.0f * ((float)G_FrameTime / 1000000.0f);
    iMainCamera.MoveForwardBackward(loc_Step);
  }
};

class cCameraForward : public cCommandBase
{
public:
  ~cCameraForward() {};
  void execute(void* arg_argument)
  {
    (void)arg_argument;
    extern cCamera iMainCamera;
    extern ui32 G_FrameTime;
    float loc_Step = -1.0f * ((float)G_FrameTime / 1000000.0f);
    iMainCamera.MoveForwardBackward(loc_Step);
  }
};

class cCameraLeft : public cCommandBase
{
public:
  ~cCameraLeft() {};
  void execute(void* arg_argument)
  {
    (void)arg_argument;
    extern cCamera iMainCamera;
    extern ui32 G_FrameTime;
    float loc_Step = -1.0f * ((float)G_FrameTime / 1000000.0f);
    iMainCamera.MoveLeftRight(loc_Step);
  }
};

class cCameraRight : public cCommandBase
{
public:
  ~cCameraRight() {};
  void execute(void* arg_argument)
  {
    (void)arg_argument;
    extern cCamera iMainCamera;
    extern ui32 G_FrameTime;
    float loc_Step = 1.0f * ((float)G_FrameTime / 1000000.0f);
    iMainCamera.MoveLeftRight(loc_Step);
  }
};

class cCameraUp : public cCommandBase
{
public:
  ~cCameraUp() {};
  void execute(void* arg_argument)
  {
    (void)arg_argument;
    extern cCamera iMainCamera;
    extern ui32 G_FrameTime;
    float loc_Step = -1.0f * ((float)G_FrameTime / 1000000.0f);
    iMainCamera.MoveUpDown(loc_Step);
  }
};

class cCameraDown : public cCommandBase
{
public:
  ~cCameraDown() {};
  void execute(void* arg_argument)
  {
    (void)arg_argument;
    extern cCamera iMainCamera;
    extern ui32 G_FrameTime;
    float loc_Step = 1.0f * ((float)G_FrameTime / 1000000.0f);
    iMainCamera.MoveUpDown(loc_Step);
  }
};

class cMouseMoveHandling : public cCommandBase
{
public:
  ~cMouseMoveHandling() {};
  void execute(void* arg_argument)
  {
    extern cCamera iMainCamera;
    extern cMyWindow* G_Wokynko;
    SDL_Event * loc_EventPtr = (SDL_Event*)arg_argument;
    si32 mouseX, mouseY;
    int loc_WinWidth, loc_WinHeight;

    SDL_GetWindowSize(G_Wokynko->getWinPtr(), &loc_WinWidth, &loc_WinHeight);

    
    if (G_MouseControlCamera)
    {
      if (loc_EventPtr->motion.x != (loc_WinWidth / 2U)) 
      { 
        mouseX = loc_EventPtr->motion.x - (loc_WinWidth / 2U);
        iMainCamera.RotateLeftRight(0.1f * mouseX);
      }
      if (loc_EventPtr->motion.y != (loc_WinHeight / 2U))
      {
        mouseY = loc_EventPtr->motion.y - (loc_WinHeight / 2U);
        iMainCamera.RotateUpDown(0.1f * mouseY);
      }
      SDL_WarpMouseInWindow(G_Wokynko->getWinPtr(), G_Wokynko->GetWidth() / 2U, G_Wokynko->GetHeight() / 2U);
      
    }

  }
};


class cLockMouseToWindow : public cCommandBase
{
public:
  ~cLockMouseToWindow() {};
  void execute(void* arg_argument)
  {
    (void)arg_argument;
    extern cMyWindow* G_Wokynko;
    SDL_WarpMouseInWindow(G_Wokynko->getWinPtr(), G_Wokynko->GetWidth()/2U, G_Wokynko->GetHeight() / 2U);
    G_MouseControlCamera = true;
  }
};

class cUnLockMouseToWindow : public cCommandBase
{
public:
  ~cUnLockMouseToWindow() {};
  void execute(void* arg_argument)
  {
    (void)arg_argument;
    G_MouseControlCamera = false;
  }
};




void RegisterEventsToHandler(cEventHandler* arg_EventHandler)
{
  //general events
  arg_EventHandler->RegisterEvent(static_cast<ui32>(SDL_QUIT), new cQuitAppCommand());



  arg_EventHandler->RegisterEvent(static_cast<ui32>(SDL_MOUSEMOTION), new cMouseMoveHandling());



  //key events
  arg_EventHandler->RegisterKeyDown(SDL_SCANCODE_ESCAPE, new cQuitAppCommand());

  arg_EventHandler->RegisterKeyDown(SDL_SCANCODE_M, new cLockMouseToWindow());

  //movement of camera
  //arg_EventHandler->RegisterKeyDown('w', new cCameraForward());
  //arg_EventHandler->RegisterKeyDown('s', new cCameraBackward());
  //arg_EventHandler->RegisterKeyDown(SDLK_ESCAPE, new cQuitAppCommand());

}



void RegisterControlCommandToHandler(cKeyBasedControlHandler* arg_ControlHandler)
{

  arg_ControlHandler->RegisterControlFunction(SDL_SCANCODE_W, new cCameraForward());
  arg_ControlHandler->RegisterControlFunction(SDL_SCANCODE_S, new cCameraBackward());
  arg_ControlHandler->RegisterControlFunction(SDL_SCANCODE_A, new cCameraLeft());
  arg_ControlHandler->RegisterControlFunction(SDL_SCANCODE_D, new cCameraRight());
  arg_ControlHandler->RegisterControlFunction(SDLK_LCTRL, new cCameraUp());
  arg_ControlHandler->RegisterControlFunction(SDLK_LSHIFT, new cCameraDown());

}

