#include "stdafx.h"
#include "cTimeMeasure.h"


void cTimeMeasure::Begin(void)
{
  QueryPerformanceCounter(&StartingTime);
}

void cTimeMeasure::End(void)
{
  QueryPerformanceCounter(&EndingTime);
  ResultMcroseconds = (EndingTime.QuadPart - StartingTime.QuadPart);
}

LONGLONG cTimeMeasure::Get_uSec(void)
{  
  return ResultMcroseconds;
}

float cTimeMeasure::Get_mSec(void)
{
  return static_cast<float>(ResultMcroseconds)/1000.0f;
}

cTimeMeasure::cTimeMeasure():
  StartingTime(),
  EndingTime(),
  ResultMcroseconds()
{
}


cTimeMeasure::~cTimeMeasure()
{
}
