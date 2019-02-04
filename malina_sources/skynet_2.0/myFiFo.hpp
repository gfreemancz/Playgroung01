// my fifo class for NRF packets

#include "types.h"

struct nRF_Packet
{
  nRF_Packet *next;
  nRF_Packet *previous;
  ui32 time;
  ui8  data[32];
};

class myFiFo
{
  public:
    myFiFo();
    myFiFo(ui16 arg_maxSize);
    ~myFiFo();
    ui8 addPacket(
  private:
  nRF_Packet *first;
  nRF_Packet *last;
  ui32 count;
  
}