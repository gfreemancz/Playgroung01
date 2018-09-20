#pragma once
class cTimer
{
  ui32 time;
public:
  void set(ui32 delay){time = SDL_GetTicks()+delay;}
  bool check(void){if(SDL_GetTicks()<time)return false;else return true;}
  cTimer(void);
  ~cTimer(void);
};

