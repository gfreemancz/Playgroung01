#include "types.h"


extern ui8  nRF24L01_status;
extern ui8 *dataBuffer;
extern ui8 nRF24l01_dataReady;


void nRF24l01_CE_Down(void);
void nRF24l01_CE_Up(void);

void EXTI2_ISR_Handler(void);
ui8 nRF24l01_initInterface(ui8 *arg_dataBuffer);
void delay_us(ui8 time);
void delay_ms(ui8 time);
ui8 nRF24l01_sendCMD(ui8 arg_cmd, ui8 *arg_data, ui8 arg_data_len);





