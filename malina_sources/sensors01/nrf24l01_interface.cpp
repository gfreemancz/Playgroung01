#include "types.h"
#include "nrf24l01.h"
#include <wiringPi.h>
#include <wiringPiSPI.h>





int SPI_busss;


ui8 nRF24l01_initInterface(ui8 *arg_dataBuffer)
{
  dataBuffer = arg_dataBuffer;
  SPI_busss = wiringPiSPISetup (0, 4000000);
  if (SPI_busss==-1)
  {
     return -1;
  }
  return 0;
}

void delay_us(ui8 time)
{
  delayMicroseconds(time);
}

void delay_ms(ui8 time)
{
  delay(time);
}

void nRF24l01_CE_Up(void)
{
  digitalWrite (6,  HIGH) ;
}
void nRF24l01_CE_Down(void)
{
  digitalWrite (6,  LOW) ;
}



ui8 nRF24l01_sendCMD(ui8 arg_cmd, ui8 *arg_data, ui8 arg_data_len)
{
  ui8 loc_spiBuffer[33];
  ui8 i;
  loc_spiBuffer[0] = arg_cmd;
  if(arg_data_len == 0u)
  {
    wiringPiSPIDataRW (0,loc_spiBuffer, 1 );
  }
  else
  {    
    for(i=0;i<arg_data_len;i++)
    {
      loc_spiBuffer[i+1] = arg_data[i];
    }   
    wiringPiSPIDataRW (0,loc_spiBuffer, arg_data_len+1 );
    for(i=0;i<arg_data_len;i++)
    {
      arg_data[i]=loc_spiBuffer[i+1];
    }  
  }
  
  return loc_spiBuffer[0];
}