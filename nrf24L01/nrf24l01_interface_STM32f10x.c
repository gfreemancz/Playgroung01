#include "types.h"

// #include "nrf24l01_interface_STM32f10x.h"
#include "nrf24l01.h"

#include "GPIO.h"
#ifndef _EXTI_H
  #include "exti.h"
#endif








void EXTI2_ISR_Handler(void)
{
  ui8 loc_dataSize=0;
  nRF24l01_CE_Down();
  nRF24L01_status = nRF24l01_GetStatus();
  nRF24L01_status = nRF24l01_readReg(0x11+((nRF24L01_status&0x0e)>>1),&loc_dataSize,1);
  nRF24l01_RecievePacket(dataBuffer,loc_dataSize);
  nRF24l01_dataReady = 1;
  loc_dataSize = 0x70;
  nRF24L01_status = nRF24l01_writeReg(7,&loc_dataSize,1);
  nRF24l01_CE_Up();
  myEXTI->u_PR.PR_BF.PR2 = 1;
}


void nRF24l01_initInterface(ui8 *arg_dataBuffer)
{
	dataBuffer = arg_dataBuffer;
}

void delay_us(ui8 time)
{
  ui32 loc_timer = 0;
  while(loc_timer > time*12)loc_timer++;
}

void delay_ms(ui8 time)
{
  ui32 loc_timer = 0;
  while(loc_timer > time*12000)loc_timer++;
}



ui8 nRF24l01_sendCMD(ui8 arg_cmd, ui8 *arg_data, ui8 arg_data_len)
{
  ui8 loc_spiBuffer[33];
  ui8 i;
  loc_spiBuffer[0] = arg_cmd;
  if(arg_data_len == 0u)
  {
    CSN_LOW;
    loc_spiBuffer[0] = SPI1_trrx8bit(arg_cmd);
    CSN_HI;
  }
  else
  {    
    for(i=0;i<arg_data_len;i++)
    {
      loc_spiBuffer[i+1] = arg_data[i];
    }  
    CSN_LOW;
    for(i=0;i<arg_data_len+1;i++)
    {
      loc_spiBuffer[i] = SPI1_trrx8bit(loc_spiBuffer[i]);
    }
    CSN_HI;
    for(i=0;i<arg_data_len;i++)
    {
      arg_data[i]=loc_spiBuffer[i+1];
    }  
  }
  
  return loc_spiBuffer[0];
}
