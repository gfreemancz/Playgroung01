/*
 * cEventHandler.h
 *
 *  Created on: 14. 2. 2017
 *      Author: GFreeman
 */

#ifndef CEVENTHANDLER_H_
#define CEVENTHANDLER_H_

#ifndef STDAFX_H
	#include "stdafx.h"
#endif

#include <vector>
#include <SDL.h>
#include <map>


class cEventHandler {
public:
	cEventHandler(){;}
	virtual ~cEventHandler();
	void cyclic(void);
	void RegisterEvent(ui32 arg_EventType, cCommandBase * arg_command);
	void RegisterKeyDown(Sint32 arg_KeyCode, cCommandBase * arg_command);
	void RegisterKeyup(Sint32 arg_KeyCode, cCommandBase * arg_command);

private:
	ui8 KeyState[512];
	std::map<ui32 ,cCommandBase *> SystemCommands;
	std::map<Sint32 , cCommandBase *> KeyPressCommands;
	std::map<Sint32 , cCommandBase *> KeyFreeCommands;
	SDL_Event Event;

	void RunCommand(cCommandBase * arg_Command);

};

#endif /* CEVENTHANDLER_H_ */
