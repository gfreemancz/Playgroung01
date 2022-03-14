#pragma once

#ifndef CCOMMANDBASE_H_
#include "cCommandBase.h"
#endif

#include <vector>
#include <SDL.h>
#include "cEventHandler.h"


typedef struct sCommandKeyPair
{
  cCommandBase * Command;
  Sint32 KeyCode;

}tCommandKeyPair;

class cKeyBasedControlHandler
{
public:
  cKeyBasedControlHandler(void);
  ~cKeyBasedControlHandler(void);

  void RegisterControlFunction(Sint32 arg_KeyCode, cCommandBase* arg_command);
  void Cyclic(cEventHandler * arg_EventHandler);

private:
  std::vector<sCommandKeyPair>  CommandList;
};

