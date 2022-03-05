// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
#ifndef STDAFX_H
#define STDAFX_H


#include <tchar.h>
#include <iostream>


#define PI 3.14159265

//random number generator
#define MYRAND_MUL    1103515245UL
#define MYRAND_ADD    12345UL
#define MYRAND_MAX    0x7fffffffUL

#define BUFFER_OFFSET(i) ((void*)(i))

// standart type definition
typedef  unsigned char        ui8;
typedef  unsigned short       ui16;
typedef  unsigned long        ui32;
typedef  unsigned long long   ui64;

typedef  signed char       si8;
typedef  signed short      si16;
typedef  signed long       si32;
typedef  signed long long  si64;

#include "cMyRandom.h"
extern cMyRandomXORshift128plus RandomNumberXSp;

#define RANDI(min,max) RandomNumberXSp.getI(min,max)
#define RANDSEED(seed) RandomNumberXSp.setSeed(seed,seed)


//SDL color mask defs
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define rmask 0xFF000000
#define gmask 0x00FF0000
#define bmask 0x0000FF00
#define amask 0x000000FF
#define myRGB(R,G,B)    ( ((R<<24)&rmask) | ((G<<16)&gmask) | ((B<<8)&bmask)             )
#define myRGBA(R,G,B,A) ( ((R<<24)&rmask) | ((G<<16)&gmask) | ((B<<8)&bmask) | (A&amask) )
#else
#define rmask 0x000000FF
#define gmask 0x0000FF00
#define bmask 0x00FF0000
#define amask 0xFF000000
#define myRGB(R,G,B)    (                   ((B<<16)&bmask) | ((G<<8)&gmask) | (R&rmask) )
#define myRGBA(R,G,B,A) ( ((A<<24)&amask) | ((B<<16)&bmask) | ((G<<8)&gmask) | (R&rmask) )

#endif

#ifndef CALLBACK
#define CALLBACK __stdcall
#endif


// TODO: reference additional headers your program requires here
#endif //ifndef STDAFX_H
