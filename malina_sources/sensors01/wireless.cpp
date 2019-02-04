#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#include <wiringPi.h>
#include "nrf24l01.h"

 
#define  CMD_R_REGISTER    0x00
#define  CMD_W_REGISTER    0x20 
 
 
#define  WS_READ_NRF_PAYLOAD  2u 

#define  nRF_IRQ_PIN  24
 
using namespace std;


static volatile unsigned int eventType=0;
volatile unsigned int pCounter = 0;
volatile unsigned char loopLocker = 1;

nRF24l01_Config nRF_cfg = {
             CONFIG_EN_CRC|CONFIG_CRCO_2B,                      //ui8 config;
             ENABLE_AUTO_ACK_PIPE_1,     //ui8 EN_AA;
             ENABLE_DATA_PIPE_1,             //ui8 EN_RXADR;
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
             24,                                                //ui8 RX_payload_size_P0;
             24,                                                //ui8 RX_payload_size_P1;
             0,                                                 //ui8 RX_payload_size_P2;
             0,                                                 //ui8 RX_payload_size_P3;
             0,                                                 //ui8 RX_payload_size_P4;
             0,                                                 //ui8 RX_payload_size_P5;
              };    

              
unsigned char nRF_Buffer[33];
unsigned char nRF_Buffer_in[33];
unsigned long int sec=0;
unsigned long int ssec=0;
 
 

void nRF_Handle(void)
{
  ui8 loc_dataSize=0;
  ui8 reset_flagu = 0x70;
  ui8 t1l,t1r,t2l,t2r;
  char commandString[50];
  nRF24l01_CE_Down();
  nRF24L01_status = nRF24l01_GetStatus();
  nRF24L01_status = nRF24l01_readReg(0x11+((nRF24L01_status&0x0e)>>1),&loc_dataSize,1);
  nRF24l01_RecievePacket(nRF_Buffer_in,loc_dataSize);  
  nRF24l01_writeReg(7,&reset_flagu,1);
  nRF24l01_CE_Up();
  
  ui8 s1 = nRF_Buffer_in[6]&0x80;
  ui8 s2 = nRF_Buffer_in[9]&0x80;
  
  if(s1==0)
  {
    t1r = nRF_Buffer_in[7]&0x0f;
    t1l = (nRF_Buffer_in[7]>>4)|((nRF_Buffer_in[6]&0x0f)<<4);
    sprintf(commandString,"python sendtmp.py venku %d.%d",t1l,t1r);

  }
  else
  {
    t1r = ((0-nRF_Buffer_in[7])&0x0f);
    t1l = 0-((nRF_Buffer_in[7]>>4)|((nRF_Buffer_in[6]&0x0f)<<4));
    sprintf(commandString,"python sendtmp.py venku -%d.%d",t1l,t1r);
  }
  system(commandString);

  if(s2 == 0)
  {
    t2r = (nRF_Buffer_in[10]&0x0f);
    t2l = (nRF_Buffer_in[10]>>4)|((nRF_Buffer_in[9]&0x0f)<<4);
    sprintf(commandString,"python sendtmp.py doma %d.%d",t2l,t2r);
  }
  else
  {
    t2r = ((0-nRF_Buffer_in[10])&0x0f);
    t2l = ((0-nRF_Buffer_in[10])>>4)|(((0-nRF_Buffer_in[9])&0x0f)<<4);
    sprintf(commandString,"python sendtmp.py doma -%d.%d",t2l,t2r);
  }
  system(commandString);
  

  printf("teplota1: %d,%d \n",t1l,t1r);
  printf("teplota2: %d,%d \n",t2l,t2r);
  sec= time(NULL);
  cout<<(sec-ssec)<<endl;

}



int main(void)
{

  //unsigned char i = 3;
 // unsigned char data[8]={'_','t','e','s','t','i','k','_'};
 // unsigned char dataz[]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
  unsigned char status, config;  
  unsigned char loopLocker = 1;
  unsigned char userCommand=0;
  int regnum=0;

 // string dataload = string("hello wireless");
  
  ssec= time(NULL);
  wiringPiSetup () ;
  pinMode (6, OUTPUT) ;
  digitalWrite (6,  LOW) ;
  //wiringPiISR(5, INT_EDGE_FALLING, &nRF_Handle);
  
 // system("gpio edge 5 falling");
  wiringPiISR (5, INT_EDGE_FALLING,  &nRF_Handle);
  
  nRF24l01_initInterface(nRF_Buffer);  
  nRF24l01_Configure(&nRF_cfg);  
  nRF24l01_StartLisen();  
  
  
  while(loopLocker) //main loop
  {
    switch(userCommand)
    {
      case 'k':
        loopLocker = 0;
      break;
      case 'r':
        cout<<"cislo registru: ";
        scanf("%d",&regnum);
        nRF24l01_CE_Down();
        status = nRF24l01_readReg((ui8)regnum,&config,1);
        printf("status: 0x%x   , register value: 0x%x \n",status, config);
        nRF24l01_CE_Up();
      break;
    }
    cout << "k - konec, r - read register"<<endl;
    userCommand = getchar();
    //sleep();
  }
  printf("konec!\n");
  return 0;
}






