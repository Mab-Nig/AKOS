CPU		  	= -mthumb -mcpu=cortex-m3
DEFINES  	= -DSTM32L151xB
LDSCRIPT  	= test/stm32l151xx/stm32l151xx.ld

OOCD_IF		= stlink
OOCD_TARGET	= stm32l1x

INCLUDE	 	+=
SRCS	 	+= test/stm32l151xx/main.c
ASM_SRCS 	+= test/stm32l151xx/startup_stm32l151xx.s
