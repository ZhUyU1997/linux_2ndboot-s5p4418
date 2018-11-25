###########################################################################
# Build Version info
###########################################################################
VERINFO				= V05

###########################################################################
# Build Environment
###########################################################################
DEBUG				= n

CHIPNAME			= S5P4418

ifeq ($(CHIPNAME),S5P4418)
#BOOTFROM			= usb
#BOOTFROM			= spi
BOOTFROM			= sdmmc
#BOOTFROM			= sdfs
#BOOTFROM			= nand
endif


# cross-tool pre-header
CROSS_TOOL_TOP		= 
CROSS_TOOL			= $(CROSS_TOOL_TOP)arm-linux-gnueabihf-

###########################################################################
# Top Names
###########################################################################
PROJECT_NAME		= $(CHIPNAME)_2ndboot
TARGET_NAME			= $(PROJECT_NAME)_$(VERINFO)$(BOARD)_$(BOOTFROM)

LDS_NAME			= pyrope_2ndboot


###########################################################################
# Directories
###########################################################################
DIR_PROJECT_TOP		=
DIR_OBJOUTPUT		= obj
DIR_TARGETOUTPUT	= build$(BOARD)_$(BOOTFROM)


CODE_MAIN_INCLUDE	=

###########################################################################
# Build Environment
###########################################################################
CPU					= cortex-a9
CC					= $(CROSS_TOOL)gcc
LD 					= $(CROSS_TOOL)ld
AS 					= $(CROSS_TOOL)as
AR 					= $(CROSS_TOOL)ar
MAKEBIN				= $(CROSS_TOOL)objcopy
RANLIB 				= $(CROSS_TOOL)ranlib

GCC_LIB				= $(shell $(CC) -print-libgcc-file-name)

ifeq ($(DEBUG), y)
CFLAGS				= -DNX_DEBUG -O0
Q					=
else
CFLAGS				= -DNX_RELEASE -Os
Q					= @
endif

MKDIR				= mkdir
RM					= rm -f
MV					= mv
CD					= cd
CP					= cp
ECHO				= echo
RMDIR				= rm -rf

###########################################################################
# FLAGS
###########################################################################
ARFLAGS				= rcs
ARFLAGS_REMOVE			= -d
ARLIBFLAGS			= -v -s

ASFLAG				= -D__ASSEMBLY__  -fdata-sections -mcpu=$(CPU) -marm

CFLAGS				+=	-g -Wall				\
					-Wextra -ffreestanding -fno-builtin	-fdata-sections -marm\
					-msoft-float				\
					-mlittle-endian				\
					-mcpu=$(CPU)				\
					-mstructure-size-boundary=32		\
					$(CODE_MAIN_INCLUDE)			\
					-D__arm -D$(BOOTFROM)load -DCHIPID_$(CHIPNAME)
