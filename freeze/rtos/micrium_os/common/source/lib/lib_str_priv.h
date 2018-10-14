/*
*********************************************************************************************************
*                                               Micrium OS
*                                                   Common
*
*                               (c) Copyright 2004; Silicon Laboratories Inc.
*                                           https://www.micrium.com
*********************************************************************************************************
* Licensing:
*           YOUR USE OF THIS SOFTWARE IS SUBJECT TO THE TERMS OF A MICRIUM SOFTWARE LICENSE.
*   If you are not willing to accept the terms of an appropriate Micrium Software License, you must not
*   download or use this software for any reason.
*   Information about Micrium software licensing is available at https://www.micrium.com/licensing/
*   It is your obligation to select an appropriate license based on your intended use of the Micrium OS.
*   Unless you have executed a Micrium Commercial License, your use of the Micrium OS is limited to
*   evaluation, educational or personal non-commercial uses. The Micrium OS may not be redistributed or
*   disclosed to any third party without the written consent of Silicon Laboratories Inc.
*********************************************************************************************************
* Documentation:
*   You can find user manuals, API references, release notes and more at: https://doc.micrium.com
*********************************************************************************************************
* Technical Support:
*   Support is available for commercially licensed users of Micrium's software. For additional
*   information on support, you can contact info@micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                           ASCII STRING MANAGEMENT
*
* File : lib_str_priv.h
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*********************************************************************************************************
*/

#ifndef  _LIB_STR_PRIV_H_
#define  _LIB_STR_PRIV_H_


/*
*********************************************************************************************************
*********************************************************************************************************
*                                               INCLUDE FILES
*********************************************************************************************************
*********************************************************************************************************
*/

#include  <cpu/include/cpu.h>


/*
*********************************************************************************************************
*********************************************************************************************************
*                                               DATA TYPES
*********************************************************************************************************
*********************************************************************************************************
*/

typedef int (*STR_PRINTF_OUT_CB)(int, void *);


/*
*********************************************************************************************************
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*********************************************************************************************************
*/

CPU_INT16U  Str_Printf          (      STR_PRINTF_OUT_CB   out_cb,
                                       void               *p_out_cb_arg,
                                 const CPU_CHAR           *format,
                                                           ...);

CPU_INT16U  Str_Sprintf         (      CPU_CHAR           *p_str,
                                 const CPU_CHAR           *format,
                                                           ...);

CPU_INT16U  Str_Snprintf        (      CPU_CHAR           *p_str,
                                       CPU_INT16U          size,
                                 const CPU_CHAR           *format,
                                                           ...);


/*
*********************************************************************************************************
*********************************************************************************************************
*                                               MODULE
*********************************************************************************************************
*********************************************************************************************************
*/

#endif                                                          /* End of lib str module include.                       */
