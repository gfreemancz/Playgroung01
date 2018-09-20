#pragma once
#include "stdafx.h"

class cMyRandomXORshift128plus
{
  ui64 seed[2];
  ui64 get(void);
public:
  cMyRandomXORshift128plus(void){};
  void  setSeed(ui64 arg_seed1,ui64 arg_seed2){seed[0]=arg_seed1;seed[1]=arg_seed2;}
  ui32  getI(ui32 min, ui32 max);
  float getF(float min, float max);
  ~cMyRandomXORshift128plus(void){};
};

