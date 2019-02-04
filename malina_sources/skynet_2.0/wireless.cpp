#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <pthread.h>

#include <thread>
#include <mutex>
#include <condition_variable>


#include <wiringPi.h>
#include "nrf24l01.h"
#include "types.h"

 
#define  CMD_R_REGISTER    0x00
#define  CMD_W_REGISTER    0x20 
 
 
#define  WS_READ_NRF_PAYLOAD  2u 

#define  nRF_IRQ_PIN  24
 
using namespace std;

typedef struct stempData
{
  ui8 tmp1[2];
  ui8 tmp2[2];
  unsigned long int time;
}ttempData;

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

ttempData thermometer_data;
 



mutex m;
condition_variable cv;
// std::string data;
bool ready = false;
// bool processed = false;


void log2file(const char *record)
{
  FILE *log;
  log = fopen("/home/pi/skynet_2.0/log.txt","a");
  fprintf(log," %d %s \n",(unsigned int)time(0),record);
  fclose(log);
}






void sendData(void)
{
  ui8 t1l,t1r,t2l,t2r;
  char commandString[50];
  ui8 s1,s2;
  ui64 timestamp;
  unique_lock<std::mutex> *lk = new unique_lock<std::mutex>(m);
  
  while(loopLocker)
  {
   
    log2file(string("locking thread and waiting").c_str());
    cv.wait(*lk, []{return ready;});
    ready = false;
    printf("\n time> %lu\n",(unsigned long int)time(NULL));
    s1 = thermometer_data.tmp1[0]&0x80;
    s2 = thermometer_data.tmp2[0]&0x80; 
    timestamp = (unsigned long int)time(NULL);
    //printf("\n time> %lu\n",(unsigned long int)thermometer_data.time);
    
    if(s1==0)
    {
      t1r = thermometer_data.tmp1[1]&0x0f;
      t1l = (thermometer_data.tmp1[1]>>4)|((thermometer_data.tmp1[0]&0x0f)<<4);
      sprintf(commandString,"python /home/pi/skynet_2.0/sendtmp.py venku %d.%d %lu",t1l,t1r,(unsigned long int)timestamp);

    }
    else
    {
      t1r = ((0-thermometer_data.tmp1[1])&0x0f);
      t1l = 0-((thermometer_data.tmp1[1]>>4)|((thermometer_data.tmp1[0]&0x0f)<<4));
      sprintf(commandString,"python /home/pi/skynet_2.0/sendtmp.py venku -%d.%d %lu",t1l,t1r,(unsigned long int)timestamp);
    }
    log2file(string("sendind 1th thermometer_data").c_str());
    system(commandString);
    log2file(commandString);

    if(s2 == 0)
    {
      t2r = (thermometer_data.tmp2[1]&0x0f);
      t2l = (thermometer_data.tmp2[1]>>4)|((thermometer_data.tmp2[0]&0x0f)<<4);
      sprintf(commandString,"python /home/pi/skynet_2.0/sendtmp.py doma %d.%d %lu",t2l,t2r,(unsigned long int)timestamp);
    }
    else
    {
      t2r = ((0-thermometer_data.tmp2[1])&0x0f);
      t2l = ((0-thermometer_data.tmp2[1])>>4)|(((0-thermometer_data.tmp2[0])&0x0f)<<4);
      sprintf(commandString,"python /home/pi/skynet_2.0/sendtmp.py doma -%d.%d %lu",t2l,t2r,(unsigned long int)timestamp);
    }
    log2file(string("sendind 2th thermometer_data").c_str());
    system(commandString);
    log2file(commandString);
    //lk->unlock();
  }
 
}





void nRF_Handle(void)
{

  ui8 loc_dataSize=0;
  ui8 reset_flagu = 0x70;

  nRF24l01_CE_Down();
  nRF24l01_writeReg(7,&reset_flagu,1);  
  nRF24L01_status = nRF24l01_GetStatus();  
 // printf("\n%d\n",nRF24L01_status);
  nRF24L01_status = nRF24l01_readReg(0x11+((nRF24L01_status&0x0e)>>1),&loc_dataSize,1);
  nRF24l01_RecievePacket(nRF_Buffer_in,loc_dataSize);  

  nRF24l01_FlushRX();
  nRF24l01_CE_Up();
  
  thermometer_data.tmp1[0] = nRF_Buffer_in[6];
  thermometer_data.tmp1[1] = nRF_Buffer_in[7];
  thermometer_data.tmp2[0] = nRF_Buffer_in[9];
  thermometer_data.tmp2[1] = nRF_Buffer_in[10];
  thermometer_data.time = (unsigned long int)time(NULL);
  
  printf("%02x %02x %02x %02x %lu\n",thermometer_data.tmp1[0],thermometer_data.tmp1[1],thermometer_data.tmp2[0],thermometer_data.tmp2[1],thermometer_data.time);
  
  
  log2file(string("thermometer_data came").c_str());
  
 // std::lock_guard<std::mutex> lk(m);
  ready = true;
  cv.notify_one();
 /* */
}



int wirelessHandler(void)
{

 
  ssec= time(NULL);
  wiringPiSetup () ;
  pinMode (6, OUTPUT) ;
  digitalWrite (6,  LOW) ;
  
  wiringPiISR (5, INT_EDGE_FALLING,  &nRF_Handle);
  
  std::thread *worker = new std::thread(sendData);
  
  nRF24l01_initInterface(nRF_Buffer);  
  nRF24l01_Configure(&nRF_cfg);  
  nRF24l01_StartLisen();  
  
  
  
  while(loopLocker) //main loop
  {
    log2file(string("skynet cycle").c_str());
    sleep(50);
  //  printf("%d\n",loopLocker);
  }
  worker->join();
  printf("konec!\n");
  return 0;
}






