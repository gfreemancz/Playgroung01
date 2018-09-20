#include "stdafx.h"
#include "cMyRandom.h"



ui64 cMyRandomXORshift128plus::get(void)
{
  ui64 loc_x = seed[0];
  ui64 const loc_y = seed[1];
  seed[0] = loc_y;
  loc_x ^= loc_x << 23;
  seed[1] = loc_x ^ loc_y ^ (loc_x >> 17) ^ (loc_y >>26);
  return seed[1]+loc_y;
}

ui32  cMyRandomXORshift128plus::getI(ui32 min, ui32 max)
{
  double loc_rnd = static_cast<double>(get());
  double loc_scale = static_cast<double>(max - min + 1)/static_cast<double>(0xffffffffffffffff);


  return static_cast<ui32>(loc_rnd * loc_scale ) + min;
}

float cMyRandomXORshift128plus::getF(float min, float max)
{
  return static_cast<float>(get() *  (max - min + 1) + min);
}





cMyRandomXORshift128plus RandomNumberXSp;


