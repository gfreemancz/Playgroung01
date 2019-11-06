#pragma once

#include <iostream>
#include <Windows.h>


class cTimeMeasure
{
  LARGE_INTEGER StartingTime, EndingTime;
  LONGLONG          ResultMcroseconds;

public:

  void  Begin(void);
  void  End(void);
  LONGLONG  Get_uSec(void);
  float Get_mSec(void);

  cTimeMeasure();
  ~cTimeMeasure();
};

