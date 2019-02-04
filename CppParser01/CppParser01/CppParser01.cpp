// CppParser01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "cSrcModule.h"

cSrcModule *iTestModule;


ui8 x; 

namespace nsAAA
{
	namespace nsBBB
	{
		extern ui8 x;
	}
}


int main()
{
	iTestModule = new cSrcModule("CppParser01.cpp");

	std::cout << iTestModule->getLineCount() << std::endl;
	std::cout << nsAAA::nsBBB::x << std::endl;
	
	
	
	getchar();
    return 0;
}
