//------------------------------------------------------------------------------
//
//	Copyright (C) 2014 Nexell Co. All Rights Reserved
//	Nexell Co. Proprietary & Confidential
//
//	NEXELL INFORMS THAT THIS CODE AND INFORMATION IS PROVIDED "AS IS" BASE
//	AND	WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING
//	BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS
//	FOR A PARTICULAR PURPOSE.
//
//	Module		: base
//	File		: sysHeader.h
//	Description	:
//	Author		: Russell
//	Export		:
//	History		:
//		2014.11.03	Russell - First draft
//------------------------------------------------------------------------------
#ifndef __SYS_HEADER_H__
#define __SYS_HEADER_H__

#include "cfgBootDefine.h"
#include "cfgFreqDefine.h"

#include <nx_pyrope.h>
#include <nx_type.h>
#include <nx_debug2.h>
#include <nx_chip.h>
#include <nx_rstcon.h>

#include <nx_clkpwr.h>
#include <nx_gpio.h>
#include <nx_alive.h>
#include <nx_tieoff.h>
#include <nx_intc.h>
#include <nx_clkgen.h>
#include <nx_ssp.h>

#include "secondboot.h"
#include "printf.h"
#include "debug.h"


//------------------------------------------------------------------------------
//  Set DEBUG Macro
//------------------------------------------------------------------------------

#if 0   //def NX_DEBUG
#define SYSMSG(x, ...)  printf(x, ...)
#else
#define SYSMSG(x, ...)
#endif

// Memory debug message
#if 0
#define MEMMSG(x, ...)  printf(x, ...)
#else
#define MEMMSG(x, ...)
#endif


//------------------------------------------------------------------------------
//  Set global variables
//------------------------------------------------------------------------------

#if defined(__SET_GLOBAL_VARIABLES)
struct NX_SecondBootInfo                * const pSBI = (struct NX_SecondBootInfo * const)BASEADDR_SRAM;
struct NX_SecondBootInfo                * const pTBI = (struct NX_SecondBootInfo * const)BASEADDR_SRAM;
struct NX_GPIO_RegisterSet             (* pReg_GPIO)[1] = (struct NX_GPIO_RegisterSet (*)[])PHY_BASEADDR_GPIOA_MODULE;
struct NX_ALIVE_RegisterSet             * pReg_Alive = (struct NX_ALIVE_RegisterSet *)PHY_BASEADDR_ALIVE_MODULE;
struct NX_TIEOFF_RegisterSet            * pReg_Tieoff = (struct NX_TIEOFF_RegisterSet *)PHY_BASEADDR_TIEOFF_MODULE;
struct NX_CLKPWR_RegisterSet            * pReg_ClkPwr = (struct NX_CLKPWR_RegisterSet *)PHY_BASEADDR_CLKPWR_MODULE;
struct NX_CLKGEN_RegisterSet            * pReg_UartClkGen = (struct NX_CLKGEN_RegisterSet *)PHY_BASEADDR_CLKGEN22_MODULE;
struct NX_UART_RegisterSet              * pReg_Uart = (struct NX_UART_RegisterSet *)PHY_BASEADDR_UART0_MODULE;
struct NX_RSTCON_RegisterSet            * pReg_RstCon = (struct NX_RSTCON_RegisterSet *)PHY_BASEADDR_RSTCON_MODULE;
struct NX_DREXSDRAM_RegisterSet         * pReg_Drex = (struct NX_DREXSDRAM_RegisterSet *)PHY_BASEADDR_DREX_MODULE_CH0_APB;
struct NX_DDRPHY_RegisterSet            * pReg_DDRPHY = (struct NX_DDRPHY_RegisterSet *)PHY_BASEADDR_DREX_MODULE_CH1_APB;

U32 g_USBD_VID;
U32 g_USBD_PID;

#else

extern struct NX_SecondBootInfo         * const pSBI;   // second boot info
extern struct NX_SecondBootInfo         * const pTBI;   // third boot info
extern struct NX_GPIO_RegisterSet      (* pReg_GPIO)[1];
extern struct NX_ALIVE_RegisterSet      * pReg_Alive;
extern struct NX_TIEOFF_RegisterSet     * pReg_Tieoff;
extern struct NX_CLKPWR_RegisterSet     * pReg_ClkPwr;
extern struct NX_CLKGEN_RegisterSet     * pReg_UartClkGen;
extern struct NX_UART_RegisterSet       * pReg_Uart;
extern struct NX_RSTCON_RegisterSet     * pReg_RstCon;
extern struct NX_DREXSDRAM_RegisterSet  * pReg_Drex;
extern struct NX_DDRPHY_RegisterSet     * pReg_DDRPHY;

extern U32 g_USBD_VID;
extern U32 g_USBD_PID;

#endif


#endif  //	__SYS_HEADER_H__
