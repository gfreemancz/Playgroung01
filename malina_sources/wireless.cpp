
#include <wiringPi.h>
#include "cSPI.hpp"
#include "nrf24l01.h"

 
#define  CMD_R_REGISTER    0x00
#define  CMD_W_REGISTER    0x20 
 
 
#define  WS_READ_NRF_PAYLOAD  2u 

#define  nRF_IRQ_PIN  24
 
using namespace std;


static volatile unsigned int eventType=0;

nRF24l01_Config nRF_cfg = {
             CONFIG_EN_CRC|CONFIG_CRCO_2B,                      //ui8 config;
             ENABLE_AUTO_ACK_PIPE_0|ENABLE_AUTO_ACK_PIPE_1,     //ui8 EN_AA;
             ENABLE_DATA_PIPE_0|ENABLE_DATA_PIPE_1,             //ui8 EN_RXADR;
             ADRES_WIDTH_5BYTES,                                //ui8 adr_Width;
             RETRANSMIT_DELAY_750US,                           //ui8 retransmit_delay;
             15,                                                 //ui8 retransmit_count;
             40,                                                //ui8 channel;
             RF_D_RATE_1MB,                                     //ui8 data_Rate;
             RF_PWR_00DB,                                       //ui8 out_Power;
             {'s','n','e','t','M'},                             //ui8 RX_ADDR_P0[5];
             {'s','n','e','t','S'},                             //ui8 RX_ADDR_P1[5];
             '0',                                               //ui8 RX_ADDR_P2;
             '1',                                               //ui8 RX_ADDR_P3;
             '2',                                               //ui8 RX_ADDR_P4;
             '3',                                               //ui8 RX_ADDR_P5;
             {'s','n','e','t','M'},                             //ui8 TX_ADDR[5];
             8,                                                //ui8 RX_payload_size_P0;
             8,                                                //ui8 RX_payload_size_P1;
             0,                                                 //ui8 RX_payload_size_P2;
             0,                                                 //ui8 RX_payload_size_P3;
             0,                                                 //ui8 RX_payload_size_P4;
             0,                                                 //ui8 RX_payload_size_P5;
              };    

void nRF_Handle(void)
{
  eventType = WS_READ_NRF_PAYLOAD;
}


unsigned char nRF_Buffer[33];
 
int main(void)
{

  unsigned char i = 3;
  unsigned char data[8]={'_','t','e','s','t','i','k','_'};
  unsigned char dataz[]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
  unsigned char config = 0;  
  unsigned char loopLocker = 1;
  unsigned char nrf_status = 0; 
  unsigned char reset_flagu = 0x70;
  unsigned int pCounter = 0;
  unsigned char userCommand=0;
  string dataload = string("hello wireless");
  

  wiringPiSetup () ;
  pinMode (6, OUTPUT) ;
  digitalWrite (6,  LOW) ;
  wiringPiISR(5, INT_EDGE_FALLING, &nRF_Handle);
  
  nRF24l01_initInterface(nRF_Buffer);
 
  
  nRF24l01_Configure(&nRF_cfg);
 // nRF24l01_powerUp();
  // nRF24l01_setMode(MODULE_MODE_TRANSMITER);
 // delay_ms(2);  
 // nRF24l01_setMode(MODULE_MODE_TRANSMITER);  
  //delay_us(150);
  ///cout << "start of cyclic sending via nRF24l01" <<endl;
  
  nRF24l01_PrepareToTransmit();
  
  
  while(loopLocker) //main loop
  {
    cout <<endl<< "nRF24l01 driver development aplication" <<endl;
    switch(userCommand)
    {
      case 'k':
        loopLocker = 0;
      break;
      case 'w':        
        nRF24l01_WritePayload(data,8);
        printf("zapsan payload %.8s",data);
      break;
      case 'c':
        reset_flagu = 0x70;
        nrf_status = nRF24l01_writeReg(7,&reset_flagu,1);
      break;
      case 's':
     //   nRF24l01_CE_Up();
        nRF24l01_CE_Up();
        delay_us(15);
        nRF24l01_CE_Down();
        // nrf_status = nRF24l01_readReg(0,&config,1);
        // while((nrf_status&0xf0)==0)
        // {
          // nrf_status = nRF24l01_readReg(0,&config,1);
        // }       
        // nRF24l01_CE_Down();
      break;
      case 'r':
       printf("continuus carrier wave enabled \n");
       reset_flagu = 0x00;
       nrf_status = nRF24l01_writeReg(1,&reset_flagu,1);
       reset_flagu = 0x00;
       nrf_status = nRF24l01_writeReg(4,&reset_flagu,1);
       reset_flagu = 0x1f;
       nrf_status = nRF24l01_writeReg(6,&reset_flagu,1);
       nrf_status = nRF24l01_WritePayload(dataz,8);
       nrf_status = nRF24l01_writeReg(REG_TX_ADDR,dataz,5u);  
       reset_flagu = 0x02;
       nrf_status = nRF24l01_writeReg(0,&reset_flagu,1);
       nRF24l01_CE_Up();
       delay_us(15);
       nRF24l01_CE_Down();
       delay_ms(1);
       nRF24l01_CE_Up();
       nRF24l01_ReuseTxPL();
       
       printf("enter to stop");
       cin >> i;
       nRF24l01_CE_Down();
       nRF24l01_Configure(&nRF_cfg);
       nRF24l01_powerUp();
       delay_ms(2); 
      break;
      case 'f':
        nRF24l01_sendCMD(FLUSH_TX,&reset_flagu,0);
        nRF24l01_sendCMD(FLUSH_RX,&reset_flagu,0);
      break;
      default:
      break;
    }
    cout <<endl;
    nrf_status = nRF24l01_readReg(0,&config,1);
    printf("status =  %2x \n",nrf_status);
    printf("config =  %2x \n",config);
    printf("payload = %.8s\n",data);
    printf("write payload....- w\n");
    printf("clear flags......- c\n");
    printf("send.............- s\n");
    printf("start cont. carr.- r\n");
    printf("flush fifos......- f\n");
    printf("konec............- k\n");
    printf("co delat? :");
    scanf("%c",&userCommand);
  }
  printf("konec!\n");
  return 0;
}






