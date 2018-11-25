#	Copyright (C) 2009 Nexell Co., All Rights Reserved
#	Nexell Co. Proprietary & Confidential
#
#	NEXELL INFORMS THAT THIS CODE AND INFORMATION IS PROVIDED "AS IS" BASE
#	AND WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING
#	BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS
#	FOR A PARTICULAR PURPOSE.
#
#	Module		:
#	File		:
#	Description	:
#	Author		:
#	History		:
#------------------------------------------------------------------------------

include config.mak

LDFLAGS		=	-Bstatic							\
			-Wl,-Map=$(DIR_TARGETOUTPUT)/$(TARGET_NAME).map,--cref		\
			-T$(LDS_NAME).lds						\
			-Wl,--start-group						\
			-Lsrc/$(DIR_OBJOUTPUT)						\
			-Wl,--end-group							\
			-nostdlib -Wl,-gc-sections -Wl,--build-id=none -L$(GCC_LIB) -lgcc

SYS_OBJS	=	startup.o secondboot.o				\
			resetcon.o CRYPTO.o GPIO.o CRC32.o		\
			clockinit.o debug.o printf.o util.o
SYS_OBJS	+=	MemoryInit.o
#SYS_OBJS	+=	nx_tieoff.o

ifeq ($(CHIPNAME),S5P4418)
ifeq ($(BOOTFROM),usb)
SYS_OBJS += iUSBBOOT.o
endif
ifeq ($(BOOTFROM),spi)
SYS_OBJS += iSPIBOOT.o
endif
ifeq ($(BOOTFROM),sdmmc)
SYS_OBJS += iSDHCBOOT.o
endif
ifeq ($(BOOTFROM),sdfs)
SYS_OBJS += iSDHCBOOT.o diskio.o fatfs.o iSDHCFSBOOT.o
endif
ifeq ($(BOOTFROM),nand)
SYS_OBJS += iNANDBOOTEC.o
endif
ifeq ($(BOOTFROM),uart)
SYS_OBJS += iUARTBOOT.o
endif

else ifeq ($(CHIPNAME),NXP4330)
SYS_OBJS += iUSBBOOT.o iSPIBOOT.o iSDHCBOOT.o diskio.o fatfs.o iSDHCFSBOOT.o iNANDBOOTEC.o
#SYS_OBJS += iUARTBOOT.o
endif

#SYS_OBJS += memtest_main.o test_list.o


SYS_OBJS_LIST	=	$(addprefix $(DIR_OBJOUTPUT)/,$(SYS_OBJS))

SYS_INCLUDES	=	-I src				\
			-I prototype/base 		\
			-I prototype/module

###################################################################################################
$(DIR_OBJOUTPUT)/%.o: src/%.c
	@echo [compile....$<]
	$(Q)$(CC) -MMD $< -c -o $@ $(CFLAGS) $(SYS_INCLUDES)
###################################################################################################
$(DIR_OBJOUTPUT)/%.o: src/%.S
	@echo [compile....$<]
	$(Q)$(CC) -MMD $< -c -o $@ $(ASFLAG) $(CFLAGS) $(SYS_INCLUDES)
###################################################################################################

ifeq ($(wildcard $(DIR_OBJOUTPUT)),)
__dummy := $(shell $(MKDIR) $(DIR_OBJOUTPUT))
endif
ifeq ($(wildcard $(DIR_TARGETOUTPUT)),)
__dummy := $(shell $(MKDIR) $(DIR_TARGETOUTPUT))
endif

all: link

link: $(SYS_OBJS_LIST)
	@echo [link.... $(DIR_TARGETOUTPUT)/$(TARGET_NAME).elf]
	$(Q)$(CC) $(SYS_OBJS_LIST) $(LDFLAGS) -o $(DIR_TARGETOUTPUT)/$(TARGET_NAME).elf
	@echo [binary.... $(DIR_TARGETOUTPUT)/$(TARGET_NAME).bin]
	$(Q)$(MAKEBIN) -O binary $(DIR_TARGETOUTPUT)/$(TARGET_NAME).elf $(DIR_TARGETOUTPUT)/$(TARGET_NAME).bin

###################################################################################################
clean:
	$(RMDIR) $(DIR_OBJOUTPUT)
	$(RMDIR) $(DIR_TARGETOUTPUT)

-include $(SYS_OBJS_LIST:.o=.d)

