#include "types.h"

#ifndef _GPIO_H
  #include "GPIO.h"
#endif
#ifndef _SPI_H
#include "SPI.h"
#endif

extern ui8  nRF24L01_status;
extern ui8 *dataBuffer;
extern ui8 nRF24l01_dataReady;


#define CSN_LOW setPin4(myGPIO_A,0)
#define CSN_HI  setPin4(myGPIO_A,1)
#define nRF24l01_CE_Up()  setPin3(myGPIO_A,1)
#define nRF24l01_CE_Down()  setPin3(myGPIO_A,0)

void EXTI2_ISR_Handler(void);
void nRF24l01_initInterface(ui8 *arg_dataBuffer);
void delay_us(ui8 time);
void delay_ms(ui8 time);
ui8 nRF24l01_sendCMD(ui8 arg_cmd, ui8 *arg_data, ui8 arg_data_len);

extern ui8 nrfIRQstatus;
/*
void nRF24l01_CE_Up(void)
{
  setPin3(myGPIO_A,1);
}
void nRF24l01_CE_Down(void)
{
  setPin3(myGPIO_A,0);
}

*/



