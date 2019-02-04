//****************************************************************************************
//
//    File:         types.h
//    Author:       Miroslav Pesta
//    Target:       all
//    Description:  type redefinitions
//
//****************************************************************************************


//****************************************************************************************
//    Definition for mono-inclusion 
//****************************************************************************************
#ifndef _TYPES_H
#define _TYPES_H


typedef  unsigned char   ui8;
typedef  unsigned short  ui16;
typedef  unsigned long   ui32;

typedef  signed char   si8;
typedef  signed short  si16;
typedef  signed long   si32;

typedef  unsigned long long  ui64;

typedef volatile ui8   vui8;
typedef volatile ui16  vui16;
typedef volatile ui32  vui32;

typedef volatile si8   vsi8;
typedef volatile si16  vsi16;
typedef volatile si32  vsi32;

typedef  unsigned int    uintbf;

typedef  float        fl32;
typedef  double       fl64;


typedef  unsigned short   tBool;

#ifndef TRUE
 #define TRUE  1
#endif

#ifndef FALSE
 #define FALSE 0
#endif


#define NULL_PTR (void *)0      
 


#define ENABLE   1
#define DISABLE  0

#ifndef NULL
	#define NULL 0
#endif

#ifdef __cplusplus
  #define   __I     volatile             /*!< defines 'read only' permissions                 */
#else
  #define   __I     volatile const       /*!< defines 'read only' permissions                 */
#endif
#define     __O     volatile             /*!< defines 'write only' permissions                */
#define     __IO    volatile             /*!< defines 'read / write' permissions              */


#if   defined ( __CC_ARM )
  #define __ASM            __asm                                      /*!< asm keyword for ARM Compiler          */
  #define __INLINE         __inline                                   /*!< inline keyword for ARM Compiler       */

#elif defined ( __ICCARM__ )
  #define __ASM           __asm                                       /*!< asm keyword for IAR Compiler          */
  #define __INLINE        inline                                      /*!< inline keyword for IAR Compiler. Only available in High optimization mode! */

#elif defined ( __GNUC__ )
  #define __ASM            __asm                                      /*!< asm keyword for GNU Compiler          */
  #define __INLINE         inline                                     /*!< inline keyword for GNU Compiler       */

#elif defined ( __TASKING__ )
  #define __ASM            __asm                                      /*!< asm keyword for TASKING Compiler      */
  #define __INLINE         inline                                     /*!< inline keyword for TASKING Compiler   */

#endif

#endif    // #ifndef _TYPES_H
