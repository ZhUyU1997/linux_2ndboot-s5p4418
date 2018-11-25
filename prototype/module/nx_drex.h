//	Copyright (C) 2009 Nexell Co., All Rights Reserved
//	Nexell Co. Proprietary & Confidential
//
//	NEXELL INFORMS THAT THIS CODE AND INFORMATION IS PROVIDED "AS IS" BASE
//	AND WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING
//	BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS
//	FOR A PARTICULAR PURPOSE.
//
//	Module		: DDR Memory Controller
//	File		: nx_drex.h
//	Description	:
//	Author		: Firmware Team
//	History		:
//				2014.08.20 Hans create
//------------------------------------------------------------------------------
#ifndef __NX_DREX_H__
#define __NX_DREX_H__

#include "../base/nx_prototype.h"

//------------------------
// implentation of DREX
//------------------------
#define PORTNUM		4


#ifdef	__cplusplus
extern "C"
{
#endif

//------------------------------------------------------------------------------
/// @defgroup	DREX
//------------------------------------------------------------------------------
//@{
	struct NX_DREX_QOS
	{
		volatile U32 QOSCONTROL;
		volatile U32 _Reserved;
	};

	struct NX_DREX_ACTIMING
	{
		volatile U32 TIMINGROW;					///< 0x034 : AC Timing for SDRAM Row
		volatile U32 TIMINGDATA;				///< 0x038 : AC Timing for SDRAM Data
		volatile U32 TIMINGPOWER;				///< 0x03C : AC Timing for Power Mode of SDRAM
	};

	struct	NX_DREXSDRAM_RegisterSet
	{
		volatile U32 CONCONTROL;				///< 0x0000 : Controller Control
		volatile U32 MEMCONTROL;				///< 0x0004 : Memory Control
		volatile U32 MEMCONFIG[2];				///< 0x0008~0x000C :
		volatile U32 DIRECTCMD;					///< 0x0010 : Memory Direct Command
		volatile U32 PRECHCONFIG;				///< 0x0014 : Precharge Policy Configuration
		volatile U32 PHYCONTROL[4];				///< 0x0018 : PHY Control0
		volatile U32 PWRDNCONFIG;				///< 0x0028 : Dynamic Power Down Configuration
		volatile U32 TIMINGPZQ;					///< 0x002C : AC Timing for DDR3 SDRAM periodic ZQ (ZQCS)
		volatile U32 TIMINGAREF;				///< 0x0030 : AC Timing for SDRAM Auto refresh
		volatile U32 TIMINGROW;					///< 0x034 : AC Timing for SDRAM Row
		volatile U32 TIMINGDATA;				///< 0x038 : AC Timing for SDRAM Data
		volatile U32 TIMINGPOWER;				///< 0x03C : AC Timing for Power Mode of SDRAM
		volatile U32 PHYSTATUS;					///< 0x0040 : PHY Status
		volatile U32 _Reserved2;				///< 0x0044 : 
		volatile U32 CHIPSTATUS;				///< 0x0048 : Memory Status
		volatile U32 _Reserved3[2];				///< 0x004C~0x0050
		volatile U32 MRSTATUS;					///< 0x0054 : Memory Mode Registers Status
		volatile U32 _Reserved4[2];				///< 0x0058~0x005C
		struct NX_DREX_QOS QOSCONTROL[15];		///< 0x0060~0x00D8 : Quality of Service Control
		volatile U32 _Reserved5[7];				///< 0x00DC~0x00F0
		volatile U32 WRTRA_CONFIG;				///< 0x00F4 : Write Training Configuration
		volatile U32 RDLVL_CONFIG;				///< 0x00F8 : Read Leveling Configuration (For PHY V5 Only) NXP5430 DDR PHY is V6
		volatile U32 _Reserved6;				///< 0x00FC : 
		volatile U32 BRBRSVCONTROL;				///< 0x0100 : BRB Reservation Control
		volatile U32 BRBRSVCONFIG;				///< 0x0104 : BRB Reservation Configuration
		volatile U32 BRBQOSCONFIG;				///< 0x0108 : BRB QoS Configuration
		volatile U32 MEMBASECONFIG[2];			///< 0x010C~0x0110
		volatile U32 _Reserved7[3];				///< 0x0114~0x011C
		volatile U32 WRLVL_CONFIG[2];			///< 0x0120~0x0124 : Write Leveling Configuration
		volatile U32 WRLVL_STATUS;				///< 0x0128 : Write Leveling Status
		volatile U32 _Reserved8[9];				///< 0x012C~0x014C
		volatile U32 CTRL_IO_RDATA;				///< 0x0150 : CTRL_IO_RDATA from PHY
		volatile U32 _Reserved9[3];				///< 0x0154~0x015C
		volatile U32 CACAL_CONFIG[2];			///< 0x0160~0x0164 : CA Calibration Configuration
		volatile U32 CACAL_STATUS;				///< 0x0168 : CA Calibration Status
	};

#if 0
	struct NX_DREXPPC_RegisterSet
	{
		volatile U32 PMNC;			///< 0x000 : Performance Monitor Control
		volatile U32 CNTENS;		///< 0x020 : Count Enable Set
		volatile U32 CNTENC;		///< 0x020 : Count Enable Clear
		volatile U32 INTENS;		///< 0x030 : Interrupt Enable Set
		volatile U32 INTENC;		///< 0x040 : Interrupt Enable Clear
		volatile U32 FLAG;			///< 0x050 : Overflow Flag Status Register
		volatile U32 CCNT;			///< 0x100 : Cycle Count
		volatile U32 PMCNT0;		///< 0x110 : Performance Monitor Count
	};
#endif
	enum
	{
		DREX_PORT_DISP		= 0,
		DREX_PORT_CCI		= 1,
		DREX_PORT_BOT		= 2
	};

	typedef enum
	{
		SDRAM_CMD_MRS		= 0x0,	// MRS/EMRS	mode register
		SDRAM_CMD_EMRS		= 0x0,
		SDRAM_CMD_PALL		= 0x1,	// all banks precharge
		SDRAM_CMD_PRE		= 0x2,	// per bank precharge
		SDRAM_CMD_REFS		= 0x4,	// self refresh
		SDRAM_CMD_REFA		= 0x5,	// auto refresh
		// don't use this command if pb_ref_en is enabled in MemControl register
		SDRAM_CMD_CKEL		= 0x6,	// active/precharge power down
		SDRAM_CMD_NOP		= 0x7,	// exit from active/precharge power down
		SDRAM_CMD_REFSX		= 0x8,	// exit from self refresh
		SDRAM_CMD_MRR		= 0x9,	// mode register reading
		SDRAM_CMD_ZQINIT	= 0xa,	// ZQ calibration init
		SDRAM_CMD_ZQOPER	= 0xb,	// ZQ calibration long
		SDRAM_CMD_ZQCS		= 0xc,	// ZQ calibration short
		SDRAM_CMD_SRR		= 0xd	// for Wide IO Memory
	}SDRAM_CMD;


	typedef enum
	{
		WRITE_LEVEL_STATUS_FSM_IDLE		= 1<<0,
		WRITE_LEVEL_STATUS_FSM_SETUP	= 1<<1,
		WRITE_LEVEL_STATUS_FSM_ACCESS	= 1<<2,
		WRITE_LEVEL_STATUS_FSM_DONE		= 1<<3,
		WRITE_LEVEL_STATUS_FSM_TWLO		= 1<<4
	}WRITE_LEVEL_STATUS;


//	struct NX_DREXTZFAIL
//	{
//		volatile U32 TZFAILADDRLOWR;		// 0x00x0 : Read Fail Address Low
//		volatile U32 TZFAILADDRHIGHR;		// 0x00x4 : Read Fail Address High
//		volatile U32 TZFAILCTRLR;			// 0x00x8 : Read Fail Control
//		volatile U32 TZFAILIDR;				// 0x00xC : Read Fail ID
//		volatile U32 TZFAILADDRLOWW;		// 0x00y0 : Write Fail Address Low
//		volatile U32 TZFAILADDRHIGH;		// 0x00y4 : Write Fail Address High
//		volatile U32 TZFAILCTRLW;			// 0x00y8 : Write Fail Control
//		volatile U32 TZFAILIDW;				// 0x00yC : Write Fail ID
//	};
//	struct NX_DREXTZSETUP
//	{
//		volatile U32 TZRSLOW;				// 0x01x0 : TZ Region Setup Low
//		volatile U32 TZRSHIGH;				// 0x01x4 : TZ Region Setup High
//		volatile U32 TZRSATTR;				// 0x01x8 : TZ Region Setup Attribute
//		volatile U32 _Reserved;				// 0x01xC
//	};
//	struct NX_DREXTZ_RegisterSet
//	{
//		volatile U32 TZCONFIG;				// 0x0000 : Configuration
//		volatile U32 TZACTION;				// 0x0004 : Action
//		volatile U32 TZLDRANGE;				// 0x0008 : Lockdown Range
//		volatile U32 TZLDSELECT;			// 0x000C : Lockdown Select
//		volatile U32 TZINTSTATUS;			// 0x0010 : Interrupt Status
//		volatile U32 TZINTCLEAR;			// 0x0014 : Interrupt Clear
//		volatile U32 _Reserved0[10];		// 0x0018~0x003C
//		struct NX_DREXTZFAIL TZFAIL[4];		// 0x0040~0x00BC
//		volatile U32 _Reserved1[16];		// 0x00C0~0x00FC
//		struct NX_DREXTZSETUP TZSETUP[9];	// 0x0100~0x018C
//		volatile U32 _Reserved2[0x31C];		// 0x0190~0x0DFC
//		volatile U32 TZITCRG;				// 0x0E00 : TZ Integration Test Control
//		volatile U32 TZITIP;				// 0x0E04 : TZ Integration Test Input
//		volatile U32 TZITOP;				// 0x0E08 : TZ Integration Test Output
//		volatile U32 _Reserved3[0x3D];		// 0x0E0C~0x0EFC
//		volatile U32 MEMBASECONFIG[2];		// 0x0F00~0x0F04 : Memory Chip Base Configuration
//		volatile U32 _Reserved4[2];			// 0x0F08~0x0F0C
//		volatile U32 MEMCONFIG[2];			// 0x0F10~0x0F14 : Memory Chip Configuration
//	};

	enum
	{
		CHIP_COL_7	= 0,
		CHIP_COL_8	= 1,
		CHIP_COL_9	= 2,
		CHIP_COL_10 = 3,
		CHIP_COL_11 = 4
	};

	enum
	{
		CHIP_ROW_12 = 0,
		CHIP_ROW_13 = 1,
		CHIP_ROW_14 = 2,
		CHIP_ROW_15 = 3,
		CHIP_ROW_16 = 4
	};

	enum
	{
		CHIP_BANK_4 = 2,
		CHIP_BANK_8 = 3
	};
	enum
	{
		CHIP_SIZE_MASK_256MB	= 0x7F0,
		CHIP_SIZE_MASK_512MB	= 0x7E0,
		CHIP_SIZE_MASK_1GB		= 0x7C0,
		CHIP_SIZE_MASK_2GB		= 0x780,
		CHIP_SIZE_MASK_4GB		= 0x700
	};

	enum
	{
		BANK_OF_LSB_BIT_POSITION_8	= 0,	// column low size 256B
		BANK_OF_LSB_BIT_POSITION_9	= 1,	// column low size 512B
		BANK_OF_LSB_BIT_POSITION_10 = 2,	// column low size 1KB
		BANK_OF_LSB_BIT_POSITION_11 = 3,	// column low size 2KB
		BANK_OF_LSB_BIT_POSITION_12 = 4,	// column low size 4KB
		BANK_OF_LSB_BIT_POSITION_13 = 5 	// column low size 8KB
	};

	///@brief	DREXSDRAM Interrupts for interrupt interfaces

	/// @brief	Reset status

	/// @brief	Power mode

	/// @brief	Bus type

	/// @brief	pll number

	/// @brief	power switch number




//------------------------------------------------------------------------------
/// @name	Module Interface
//@{
CBOOL	NX_DREXSDRAM_Initialize( void );
U32		NX_DREXSDRAM_GetNumberOfModule( void );
//@}

//------------------------------------------------------------------------------
///	@name	Basic Interface
//@{
U32		NX_DREXSDRAM_GetPhysicalAddress( void );
U32		NX_DREXSDRAM_GetSizeOfRegisterSet( void );
void	NX_DREXSDRAM_SetBaseAddress( U32 BaseAddress );
U32		NX_DREXSDRAM_GetBaseAddress( void );
CBOOL	NX_DREXSDRAM_OpenModule( void );
CBOOL	NX_DREXSDRAM_CloseModule( void );
CBOOL	NX_DREXSDRAM_CheckBusy( void );
CBOOL	NX_DREXSDRAM_CanPowerDown( void );
//@}

//------------------------------------------------------------------------------
///	@name	Interrupt Interface
//@{
// there is no interrupt interface
//@}

//------------------------------------------------------------------------------
/// @name	Module Interface
//@{
CBOOL	NX_DREXTZ_Initialize( void );
U32		NX_DREXTZ_GetNumberOfModule( void );
//@}

//------------------------------------------------------------------------------
///	@name	Basic Interface
//@{
U32		NX_DREXTZ_GetPhysicalAddress( void );
U32		NX_DREXTZ_GetSizeOfRegisterSet( void );
void	NX_DREXTZ_SetBaseAddress( U32 BaseAddress );
U32		NX_DREXTZ_GetBaseAddress( void );
CBOOL	NX_DREXTZ_OpenModule( void );
CBOOL	NX_DREXTZ_CloseModule( void );
CBOOL	NX_DREXTZ_CheckBusy( void );
CBOOL	NX_DREXTZ_CanPowerDown( void );
//@}

//------------------------------------------------------------------------------
///	@name	Interrupt Interface
//@{
// there is no interrupt interface
//@}

//@}

#ifdef	__cplusplus
}
#endif


#endif // __NX_DREX_H__
