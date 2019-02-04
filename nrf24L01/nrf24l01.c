/******************************************************************************
*
*          filename: nrf24l01.c
*          NRF24L01 driver module 
*          autor: Miroslav Pesta
*          date:  21.2.2014
*
*
*******************************************************************************/



#include "nrf24l01.h"

ui8  nRF24L01_status;
ui8 *dataBuffer;
ui8 nRF24l01_dataReady = 0;



ui8 nRF24l01_writeReg(ui8 arg_regAdr, ui8 *arg_regValue, ui8 arg_regValueLenght)
{
  ui8 loc_status;
  loc_status = nRF24l01_sendCMD( (W_REGISTER|(arg_regAdr)), arg_regValue, arg_regValueLenght);
  return loc_status;
}


ui8 nRF24l01_readReg(ui8 arg_regAdr, ui8 *arg_regValue, ui8 arg_regValueLenght)
{
  ui8 loc_status;
  loc_status = nRF24l01_sendCMD( ((arg_regAdr)), arg_regValue, arg_regValueLenght);
  return loc_status;
}

ui8 nRF24l01_WritePayload(ui8 *arg_data,ui8 dataSize)
{
  ui8 loc_status;
  ui8 loc_index;
  ui8 loc_buffer[32];
  for(loc_index=0;loc_index<dataSize;loc_index++)
  {
	  loc_buffer[loc_index]=arg_data[loc_index];
  }
  loc_status = nRF24l01_sendCMD( W_TX_PAYLOAD , loc_buffer, dataSize);
  return loc_status;
}

void nRF24l01_setMode(ui8 mode)
{
  ui8 loc_configReg = 0u;
  nRF24l01_readReg(REG_CONFIG,&loc_configReg,1u);

  if(mode == MODULE_MODE_TRANSMITER)
  {
    loc_configReg = loc_configReg&(~0x01u);
  }
  else if(mode == MODULE_MODE_RECIEVER)
  {
    loc_configReg = loc_configReg|1u;
  }
  (void)nRF24l01_writeReg(REG_CONFIG,&loc_configReg,1u);
  
}

void nRF24l01_powerUp(void)
{
  ui8 loc_configReg = 0u;
  nRF24l01_readReg(REG_CONFIG,&loc_configReg,1u); 
  loc_configReg = loc_configReg|2u;
  nRF24l01_writeReg(REG_CONFIG,&loc_configReg,1u);
}


void nRF24l01_powerDown(void)
{
  ui8 loc_configReg = 0u;
  nRF24l01_readReg(REG_CONFIG,&loc_configReg,1u); 
  loc_configReg = loc_configReg&(~0x02u);
  nRF24l01_writeReg(REG_CONFIG,&loc_configReg,1u);
}


void nRF24l01_Configure(nRF24l01_Config *arg_cfgS)
{
  ui8 loc_Reg;
  ui8 loc_longAdr[5];
  ui8 i;
  nRF24l01_CE_Down();
  
  delay_ms(5);  
  
  
  loc_Reg = arg_cfgS->config;
  nRF24l01_writeReg(REG_CONFIG,&loc_Reg,1u);
  
  loc_Reg = arg_cfgS->EN_AA&0x3fu;
  nRF24l01_writeReg(REG_EN_AA,&loc_Reg,1u);
  
  loc_Reg = arg_cfgS->EN_RXADR&0x3fu;
  nRF24l01_writeReg(REG_EN_RXADDR,&loc_Reg,1u);
  
  loc_Reg = arg_cfgS->adr_Width&0x03u;
  nRF24l01_writeReg(REG_SETUP_AW,&loc_Reg,1u);
  
  loc_Reg = arg_cfgS->retransmit_delay | arg_cfgS->retransmit_count;
  nRF24l01_writeReg(REG_SETUP_RETR,&loc_Reg,1u);
  
  loc_Reg = arg_cfgS->channel&0x7fu;
  nRF24l01_writeReg(REG_RF_CH,&loc_Reg,1u);
  
  loc_Reg = (arg_cfgS->data_Rate | arg_cfgS->out_Power|1)&0x0f;
  nRF24l01_writeReg(REG_RF_SETUP,&loc_Reg,1u);
  
  for(i=0;i<5;i++)
  {
    loc_longAdr[i] = arg_cfgS->RX_ADDR_P0[i];
  }  
  nRF24l01_writeReg(REG_RX_ADDR_P0,loc_longAdr,5u);
  
  for(i=0;i<5;i++)
  {
    loc_longAdr[i] = arg_cfgS->RX_ADDR_P1[i];
  }  
  nRF24l01_writeReg(REG_RX_ADDR_P1,loc_longAdr,5u);
  
  loc_Reg = arg_cfgS->RX_ADDR_P2;
  nRF24l01_writeReg(REG_RX_ADDR_P2,&loc_Reg,1u);
  loc_Reg = arg_cfgS->RX_ADDR_P3;
  nRF24l01_writeReg(REG_RX_ADDR_P3,&loc_Reg,1u);
  loc_Reg = arg_cfgS->RX_ADDR_P4;
  nRF24l01_writeReg(REG_RX_ADDR_P4,&loc_Reg,1u);
  loc_Reg = arg_cfgS->RX_ADDR_P5;
  nRF24l01_writeReg(REG_RX_ADDR_P5,&loc_Reg,1u);
  
  for(i=0;i<5;i++) 
  {
    loc_longAdr[i] = arg_cfgS->TX_ADDR[i];
  }
  nRF24l01_writeReg(REG_TX_ADDR,loc_longAdr,5u);  
  
  loc_Reg = arg_cfgS->RX_payload_size_P0&0x3fu;
  nRF24l01_writeReg(REG_RX_PW_P0,&loc_Reg,1u);
  loc_Reg = arg_cfgS->RX_payload_size_P1&0x3fu;
  nRF24l01_writeReg(REG_RX_PW_P1,&loc_Reg,1u);
  loc_Reg = arg_cfgS->RX_payload_size_P2&0x3fu;
  nRF24l01_writeReg(REG_RX_PW_P2,&loc_Reg,1u);
  loc_Reg = arg_cfgS->RX_payload_size_P3&0x3fu;
  nRF24l01_writeReg(REG_RX_PW_P3,&loc_Reg,1u);
  loc_Reg = arg_cfgS->RX_payload_size_P4&0x3fu;
  nRF24l01_writeReg(REG_RX_PW_P4,&loc_Reg,1u);
  loc_Reg = arg_cfgS->RX_payload_size_P5&0x3fu;
  nRF24l01_writeReg(REG_RX_PW_P5,&loc_Reg,1u); 
  
  
  loc_Reg = 0x70;
  nRF24l01_writeReg(REG_STATUS,&loc_Reg,1u); 
  
  loc_Reg = 0;
  nRF24l01_sendCMD(FLUSH_TX,&loc_Reg,0);
  nRF24l01_sendCMD(FLUSH_RX,&loc_Reg,0);  
  
}

void nRF24l01_FlushTX(void)
{
	nRF24l01_sendCMD(FLUSH_TX,0,0);
}
void nRF24l01_FlushRX(void)
{
	nRF24l01_sendCMD(FLUSH_RX,0,0);
}


ui8 nRF24l01_SendPacket(ui8 *arg_data,ui8 dataSize)
{
  register ui8 loc_status;
  loc_status = nRF24l01_sendCMD( W_TX_PAYLOAD , arg_data, dataSize);
  nRF24l01_CE_Up();
  delay_us(15);
  nRF24l01_CE_Down();
  return loc_status;
}

ui8 nRF24l01_RecievePacket(ui8 *arg_data,ui8 dataSize)
{
  register  ui8  loc_status=0;
  nRF24l01_CE_Down();
  loc_status = nRF24l01_sendCMD(R_RX_PAYLOAD,arg_data,dataSize);
  nRF24l01_CE_Up();
  return  loc_status;  
}

ui8 nRF24l01_GetStatus(void)
{
	register  ui8  loc_status=0;
	loc_status = nRF24l01_sendCMD( NOP, 0, 0);
	return loc_status;
}

void nRF24l01_ReuseTxPL(void)
{
	register  ui8  loc_status=0;
	loc_status = nRF24l01_sendCMD(REUSE_TX_PL, 0, 0);
}

ui8 nRF24l01_SetP0Address(ui8 arg_address[])
{
	register  ui8  loc_status=0;
	register  ui8  i=0;

  ui8 loc_longAdr[5];
  for(i=0;i<5;i++) 
  {
    loc_longAdr[i] = arg_address[i];
  }
  loc_status = nRF24l01_writeReg(REG_RX_ADDR_P0,loc_longAdr,5u);
	return loc_status;
}

ui8 nRF24l01_SetP1Address(ui8 arg_address[])
{
	register  ui8  loc_status=0;
	register  ui8  i=0;
  ui8 loc_longAdr[5];
  for(i=0;i<5;i++) 
  {
    loc_longAdr[i] = arg_address[i];
  }
  loc_status = nRF24l01_writeReg(REG_RX_ADDR_P1,loc_longAdr,5u);
	return loc_status;
}
ui8 nRF24l01_SetP2Address(ui8 arg_address)
{
	register  ui8  loc_status=0;
  loc_status = nRF24l01_writeReg(REG_RX_ADDR_P2,&arg_address,1u);
	return loc_status;
}
ui8 nRF24l01_SetP3Address(ui8 arg_address)
{
	register  ui8  loc_status=0;
  loc_status = nRF24l01_writeReg(REG_RX_ADDR_P3,&arg_address,1u);
	return loc_status;
}

ui8 nRF24l01_SetP4Address(ui8 arg_address)
{
	register  ui8  loc_status=0;
  loc_status = nRF24l01_writeReg(REG_RX_ADDR_P4,&arg_address,1u);
	return loc_status;
}

ui8 nRF24l01_SetP5Address(ui8 arg_address)
{
	register  ui8  loc_status=0;
  loc_status = nRF24l01_writeReg(REG_RX_ADDR_P5,&arg_address,1u);
	return loc_status;
}

ui8 nRF24l01_SetTXAddress(ui8 arg_address[])
{
	register  ui8  loc_status=0;
	register  ui8  i=0;
  ui8 loc_longAdr[5];
  for(i=0;i<5;i++) 
  {
    loc_longAdr[i] = arg_address[i];
  }
  loc_status = nRF24l01_writeReg(REG_TX_ADDR,loc_longAdr,5u);
	return loc_status;
}

ui8 nRF24l01_SetP0DataSize(ui8 arg_dataSize)
{
	register  ui8  loc_status=0;
  loc_status = nRF24l01_writeReg(REG_RX_PW_P0,&arg_dataSize,1u);
	return loc_status;
}

ui8 nRF24l01_SetP1DataSize(ui8 arg_dataSize)
{
	register  ui8  loc_status=0;
  loc_status = nRF24l01_writeReg(REG_RX_PW_P1,&arg_dataSize,1u);
	return loc_status;
}

ui8 nRF24l01_SetP2DataSize(ui8 arg_dataSize)
{
	register  ui8  loc_status=0;
  loc_status = nRF24l01_writeReg(REG_RX_PW_P2,&arg_dataSize,1u);
	return loc_status;
}

ui8 nRF24l01_SetP3DataSize(ui8 arg_dataSize)
{
	register  ui8  loc_status=0;
  loc_status = nRF24l01_writeReg(REG_RX_PW_P3,&arg_dataSize,1u);
	return loc_status;
}

ui8 nRF24l01_SetP4DataSize(ui8 arg_dataSize)
{
	register  ui8  loc_status=0;
  loc_status = nRF24l01_writeReg(REG_RX_PW_P4,&arg_dataSize,1u);
	return loc_status;
}

ui8 nRF24l01_SetP5DataSize(ui8 arg_dataSize)
{
	register  ui8  loc_status=0;
  loc_status = nRF24l01_writeReg(REG_RX_PW_P5,&arg_dataSize,1u);
	return loc_status;
}

void nRF24l01_StartLisen(void)
{
  nRF24l01_powerUp();
  delay_ms(2);
  nRF24l01_setMode(MODULE_MODE_RECIEVER);
  nRF24l01_CE_Up();
  delay_us(150);  
}

void nRF24l01_PrepareToTransmit(void)
{
  nRF24l01_powerUp();
  delay_ms(2);
  nRF24l01_setMode(MODULE_MODE_TRANSMITER);
  delay_us(150);
  nRF24l01_CE_Down();
}
















