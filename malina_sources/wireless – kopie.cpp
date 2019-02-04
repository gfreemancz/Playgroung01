
#include <wiringPi.h>
#include "cSPI.hpp"
#include "nrf24l01.hpp"

 
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
             RETRANSMIT_DELAY_250US,                            //ui8 retransmit_delay;
             15,                                                //ui8 retransmit_count;
             40,                                                 //ui8 channel;
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



 
int main(void)
{
 // cSpi *myspi;
//  myspi = new cSpi("/dev/spidev0.0", SPI_MODE_0, 1000000, 8);
  unsigned char i = 3;
  unsigned char data[14]={'h','e','l','l','o',' ','w','i','r','e','l','e','s','s'};
  unsigned char dataz[14]={'h','e','l','l','o',' ','w','i','r','e','l','e','s','s'};
  unsigned char mbuffer[5];
  unsigned char loopLocker = 1;
  unsigned char nrf_status = 0; 
  unsigned char reset_flagu = 0x10;
  unsigned int pCounter = 0;
  string dataload = string("hello wireless");
  
  // system("gpio edge 24 falling");
  wiringPiSetup () ;
  //pinMode (5, INPUT) ;
  pinMode (6, OUTPUT) ;
  digitalWrite (6,  LOW) ;
  wiringPiISR(5, INT_EDGE_FALLING, &nRF_Handle);
  
  nRF24l01_initInterface();
 
  
  nRF24l01_Configure(nRF_cfg);
  nRF24l01_powerUp();
  delay_ms(2);  
  nRF24l01_setMode(MODULE_MODE_TRANSMITER);  
  delay_us(150);
  cout << "start of cyclic sending via nRF24l01" <<endl;
  
  
  while(loopLocker) //main loop
  {
    nRF24l01_sendCMD(FLUSH_TX,mbuffer,0);
    reset_flagu = 0x10;
    nRF24l01_writeReg(0x07,&reset_flagu,1u);
    
    for(i=0;i<14;i++)data[i] = dataz[i];
    
    nrf_status=nRF24l01_readReg(0,mbuffer,1);
    
    nRF24l01_SendPacket(data,8);
   // nrf_status=nRF24l01_readReg(0,mbuffer,0);    
    printf("odeslanej paket %d\n status:%x\n config reg: %x\n",pCounter,nrf_status,mbuffer[0]);
    
    // nRF24l01_writeReg(0x07,&reset_flagu,1u);   
    
    pCounter++;
    sleep(2);
    if(pCounter>100)loopLocker=0;    
  }
  printf("konec!\n");
  return 0;
}