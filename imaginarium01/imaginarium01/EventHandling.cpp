



#ifndef CEVENTHANDLER_H_
  #include "cEventHandler.h"
#endif






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





void RegisterEventsToHandler(cEventHandler* arg_EventHandler)
{
  //general events
  arg_EventHandler->RegisterEvent(static_cast<ui32>(SDL_QUIT), new cQuitAppCommand());


  //key events
  arg_EventHandler->RegisterKeyDown(SDLK_ESCAPE, new cQuitAppCommand());

}



