/*
 * cEventHandler.cpp
 *
 *  Created on: 14. 2. 2017
 *      Author: GFreeman
 */

#include "cEventHandler.h"
#include <iostream>





cEventHandler::~cEventHandler() {
	// TODO Auto-generated destructor stub
	SystemCommands.erase(SystemCommands.begin(), SystemCommands.end());
}



void cEventHandler::RegisterEvent(ui32 arg_EventType,cCommandBase * arg_command)
{
	if(SystemCommands.insert(std::make_pair(arg_EventType, arg_command)).second == false)
	{
		std::cout<<"Element with key '"<<arg_EventType<<"' not inserted because already existed"<<std::endl;
	}
}

void cEventHandler::RegisterKeyDown(Sint32 arg_KeyCode, cCommandBase * arg_command)
{
	if(KeyPressCommands.insert(std::make_pair(arg_KeyCode, arg_command)).second == false)
	{
		std::cout<<"Element with key '"<<arg_KeyCode<<"' not inserted because already existed"<<std::endl;
	}
}

void cEventHandler::RegisterKeyup(Sint32 arg_KeyCode, cCommandBase * arg_command)
{
	if(KeyFreeCommands.insert(std::make_pair(arg_KeyCode, arg_command)).second == false)
	{
		std::cout<<"Element with key '"<<arg_KeyCode<<"' not inserted because already existed"<<std::endl;
	}
}

ui8 cEventHandler::GetKeyState(ui16 arg_Key)
{
  ui8 loc_RetValue = 0U;
  if (arg_Key < 512)
  {
    loc_RetValue = KeyState[arg_Key];
  }
  return loc_RetValue;
}

void cEventHandler::RunCommand(cCommandBase * arg_Command)
{
	if(arg_Command!=0)
	{
		arg_Command->execute(reinterpret_cast<void *>(&Event));
	}
}

void cEventHandler::cyclic()
{
	while( SDL_PollEvent( &Event ) != 0 )
	{
		switch(Event.type)
		{
		case SDL_QUIT:
			RunCommand(SystemCommands[SDL_QUIT]);
			break;
		case SDL_KEYDOWN:
			KeyState[Event.key.keysym.scancode] = true;
			RunCommand(KeyPressCommands[Event.key.keysym.scancode]);
			break ;
		case SDL_KEYUP:
			KeyState[Event.key.keysym.scancode] = false;
			RunCommand(KeyFreeCommands[Event.key.keysym.scancode]);
			break ;
		case SDL_MOUSEBUTTONDOWN:
			RunCommand(SystemCommands[SDL_MOUSEBUTTONDOWN]);
			break;
		case SDL_MOUSEBUTTONUP:
			RunCommand(SystemCommands[SDL_MOUSEBUTTONUP]);
			break;
		case SDL_MOUSEMOTION:
			RunCommand(SystemCommands[SDL_MOUSEMOTION]);
			break ;
		}
	}
}
