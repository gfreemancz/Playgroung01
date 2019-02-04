#include "stdafx.h"
#include "cSrcModule.h"
#include <iostream>
#include <fstream>
#include <string>


cSrcModule::cSrcModule()
{
}

cSrcModule::cSrcModule(std::string arg_FileName)
{
	std::string loc_line;
	std::ifstream loc_fHandle(arg_FileName);
	if (loc_fHandle.is_open())
	{
		LineCount = 0;
		FileContent.clear();
		while (std::getline(loc_fHandle, loc_line))
		{
			FileContent+=loc_line;
			LineCount++;
		}
	}
}


cSrcModule::~cSrcModule()
{
}
