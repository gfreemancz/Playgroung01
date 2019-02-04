//**************************************************************
//  cSPI class definition - class for SPI control on raspberry
//**************************************************************
#ifndef CSPI_H
    #define CSPI_H
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string>
#include <iostream>
 
class cSpi{
 
public:
    cSpi();
    cSpi(std::string devspi, unsigned char spiMode, unsigned int spiSpeed, unsigned char spibitsPerWord);
    ~cSpi();
    int spiWriteRead( unsigned char *data, int length);
 
private:
    unsigned char mode;
    unsigned char bitsPerWord;
    unsigned int speed;
    int spifd;
 
    int spiOpen(std::string devspi);
    int spiClose();
 
};
 
#endif