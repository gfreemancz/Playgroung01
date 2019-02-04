/******************************************************************************
*
*          filename: nrf24l01.h
*          NRF24L01 driver module header
*          autor: Miroslav Pesta
*          date:  21.2.2014
*
*
*******************************************************************************/
#ifndef NRF24L01_HPP
#define NRF24L01_HPP

#include "types.h"

#include "nrf24l01_interface_STM32f10x.h"


//memory map - register addresses
#define REG_CONFIG                     0x00
#define REG_EN_AA                      0x01
#define REG_EN_RXADDR                  0x02
#define REG_SETUP_AW                   0x03
#define REG_SETUP_RETR                 0x04
#define REG_RF_CH                      0x05
#define REG_RF_SETUP                   0x06
#define REG_STATUS                     0x07
#define REG_OBSERVE_TX                 0x08
#define REG_CD                         0x09
#define REG_RX_ADDR_P0                 0x0A
#define REG_RX_ADDR_P1                 0x0B
#define REG_RX_ADDR_P2                 0x0C
#define REG_RX_ADDR_P3                 0x0D
#define REG_RX_ADDR_P4                 0x0E
#define REG_RX_ADDR_P5                 0x0F
#define REG_TX_ADDR                    0x10
#define REG_RX_PW_P0                   0x11
#define REG_RX_PW_P1                   0x12
#define REG_RX_PW_P2                   0x13
#define REG_RX_PW_P3                   0x14
#define REG_RX_PW_P4                   0x15
#define REG_RX_PW_P5                   0x16
#define REG_FIFO_STATUS                0x17
#define REG_DYNPD	                     0x1C
#define REG_FEATURE	                   0x1D

// configuration macros:
#define  CONFIG_MASK_RX_DR         0x40u
#define  CONFIG_MASK_TX_DS         0x20u
#define  CONFIG_MASK_MAX_RT        0x10u
#define  CONFIG_EN_CRC             0x08u
#define  CONFIG_CRCO_1B            0x00u
#define  CONFIG_CRCO_2B            0x04u

#define  ENABLE_AUTO_ACK_PIPE_0    0x01u
#define  ENABLE_AUTO_ACK_PIPE_1    0x02u
#define  ENABLE_AUTO_ACK_PIPE_2    0x04u
#define  ENABLE_AUTO_ACK_PIPE_3    0x08u
#define  ENABLE_AUTO_ACK_PIPE_4    0x10u
#define  ENABLE_AUTO_ACK_PIPE_5    0x20u

#define  ENABLE_DATA_PIPE_0        0x01u
#define  ENABLE_DATA_PIPE_1        0x02u
#define  ENABLE_DATA_PIPE_2        0x04u
#define  ENABLE_DATA_PIPE_3        0x08u
#define  ENABLE_DATA_PIPE_4        0x10u
#define  ENABLE_DATA_PIPE_5        0x20u

#define  ADRES_WIDTH_3BYTES        0x01u
#define  ADRES_WIDTH_4BYTES        0x02u
#define  ADRES_WIDTH_5BYTES        0x03u

#define  RETRANSMIT_DELAY_250US    0x00u
#define  RETRANSMIT_DELAY_500US    0x01u
#define  RETRANSMIT_DELAY_750US    0x02u
#define  RETRANSMIT_DELAY_1000US   0x03u
#define  RETRANSMIT_DELAY_1250US   0x04u
#define  RETRANSMIT_DELAY_1500US   0x05u
#define  RETRANSMIT_DELAY_1750US   0x06u
#define  RETRANSMIT_DELAY_2000US   0x07u
#define  RETRANSMIT_DELAY_2250US   0x08u
#define  RETRANSMIT_DELAY_2500US   0x09u
#define  RETRANSMIT_DELAY_2750US   0x0Au
#define  RETRANSMIT_DELAY_3000US   0x0Bu
#define  RETRANSMIT_DELAY_3250US   0x0Cu
#define  RETRANSMIT_DELAY_3500US   0x0Du
#define  RETRANSMIT_DELAY_3750US   0x0Eu
#define  RETRANSMIT_DELAY_4000US   0x0Fu

#define  RF_PWR_18DB               0x00u
#define  RF_PWR_12DB               0x02u
#define  RF_PWR_6DB                0x04u
#define  RF_PWR_00DB               0x06u
                                      
#define  RF_D_RATE_1MB             0x00u
#define  RF_D_RATE_2MB             0x08u

#define  MODULE_MODE_TRANSMITER    0x00
#define  MODULE_MODE_RECIEVER      0x01



//commands for nRF24L01
#define  R_REGISTER                0x00
#define  W_REGISTER                0x20
#define  R_RX_PAYLOAD              0x61
#define  W_TX_PAYLOAD              0xA0
#define  FLUSH_TX                  0xE1
#define  FLUSH_RX                  0xE2
#define  REUSE_TX_PL               0xE3
#define  ACTIVATE                  0x50
#define  R_RX_PL_WID               0x60
#define  W_ACK_PAYLOAD             0x68
#define  W_TX_PAYLOAD_NOACK        0xB0
#define  NOP                       0xFF







// nRF24L01 configuration structure
typedef struct
{
  ui8 config;
  ui8 EN_AA;
  ui8 EN_RXADR;
  ui8 adr_Width;
  ui8 retransmit_delay;
  ui8 retransmit_count;
  ui8 channel;
  ui8 data_Rate;
  ui8 out_Power;
  ui8 RX_ADDR_P0[5];
  ui8 RX_ADDR_P1[5];
  ui8 RX_ADDR_P2;
  ui8 RX_ADDR_P3;
  ui8 RX_ADDR_P4;
  ui8 RX_ADDR_P5;
  ui8 TX_ADDR[5];
  ui8 RX_payload_size_P0;
  ui8 RX_payload_size_P1;
  ui8 RX_payload_size_P2;
  ui8 RX_payload_size_P3;
  ui8 RX_payload_size_P4;
  ui8 RX_payload_size_P5;  
} nRF24l01_Config;


//*****************************************************************
// prototypes of nRF24l01 driver functions - dont touch them...
//*****************************************************************

ui8 nRF24l01_writeReg(ui8 arg_regAdr, ui8 *arg_regValue, ui8 arg_regValueLenght);
ui8 nRF24l01_readReg(ui8 arg_regAdr, ui8 *arg_regValue, ui8 arg_regValueLenght);
ui8 nRF24l01_GetStatus(void);

void nRF24l01_setMode(ui8 mode);
void nRF24l01_powerUp(void);
void nRF24l01_powerDown(void);
void nRF24l01_StartLisen(void);
void nRF24l01_FlushTX(void);
void nRF24l01_FlushRX(void);
void nRF24l01_ReuseTxPL(void);

ui8 nRF24l01_WritePayload(ui8 *arg_data,ui8 dataSize);

ui8 nRF24l01_RecievePacket(ui8 *arg_data,ui8 dataSize);
ui8 nRF24l01_SendPacket(ui8 *arg_data,ui8 dataSize);
void nRF24l01_Configure(nRF24l01_Config *arg_cfgS);

ui8 nRF24l01_SetP0Address(ui8 arg_address[]);
ui8 nRF24l01_SetP1Address(ui8 arg_address[]);
ui8 nRF24l01_SetP2Address(ui8 arg_address);
ui8 nRF24l01_SetP3Address(ui8 arg_address);
ui8 nRF24l01_SetP4Address(ui8 arg_address);
ui8 nRF24l01_SetP5Address(ui8 arg_address);
ui8 nRF24l01_SetTXAddress(ui8 arg_address[]);

ui8 nRF24l01_SetP0DataSize(ui8 arg_dataSize);
ui8 nRF24l01_SetP1DataSize(ui8 arg_dataSize);
ui8 nRF24l01_SetP2DataSize(ui8 arg_dataSize);
ui8 nRF24l01_SetP3DataSize(ui8 arg_dataSize);
ui8 nRF24l01_SetP4DataSize(ui8 arg_dataSize);
ui8 nRF24l01_SetP5DataSize(ui8 arg_dataSize);

#endif
