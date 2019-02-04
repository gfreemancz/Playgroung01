

nRF_Packet::nRF_Packet()
    time(0),
    count(0)
{
  
  count++;
  next=0;
  previous=0;
}

nRF_Packet::nRF_Packet(ui32 time,ui8 data[])
{
}

nRF_Packet::~nRF_Packet()
{
}