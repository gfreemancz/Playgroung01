#include "cKeyBasedControlHandler.h"
#include <algorithm>




cKeyBasedControlHandler::cKeyBasedControlHandler(void)
{
}

cKeyBasedControlHandler::~cKeyBasedControlHandler(void)
{
  CommandList.clear();
}

void cKeyBasedControlHandler::RegisterControlFunction(Sint32 arg_KeyCode, cCommandBase* arg_command)
{
  sCommandKeyPair loc_PairInstance;
  loc_PairInstance.Command = arg_command;
  loc_PairInstance.KeyCode = arg_KeyCode;

  //if (std::find(CommandList.begin(), CommandList.end(), loc_PairInstance) == CommandList.end())
  //{
    CommandList.push_back(loc_PairInstance);
  //}
  //else
  //{
  //  std::cout << "Element with key '" << arg_KeyCode << "' not inserted because already existed" << std::endl;
  //}
}

void cKeyBasedControlHandler::Cyclic(cEventHandler* arg_EventHandler)
{

  for (ui16 i = 0; i < (ui16)CommandList.size(); i++)
  {
    if (arg_EventHandler->GetKeyState(CommandList[i].KeyCode) == (ui8)true)
    {
      CommandList[i].Command->execute((void*)0);
    }
    
  }

}
