#pragma once
#include "stdafx.h"

class cBaseEngineObject
{
	static ui32 BaseIdCounter;
public:
	static ui32 nextID() { return BaseIdCounter++; };
	cBaseEngineObject() {};
	~cBaseEngineObject() {};
};


template <typename T> 
class tBsEngObjCnt : public cBaseEngineObject
{
	static const ui32 IdCounter;
public:
	ui32 GetID(void) { return IdCounter; }
	tBsEngObjCnt() {}
	~tBsEngObjCnt() {}
};


template <typename T>
const ui32 tBsEngObjCnt<T>::IdCounter(cBaseEngineObject::nextID());



//test code to evaulate solution

class cTestClass1 : public tBsEngObjCnt<cTestClass1>
{
public:
	ui32 x;
	ui32 y;
};

class cTestClass2 : public tBsEngObjCnt<cTestClass2>
{
public:
	ui32 x;
	ui32 y;
};




