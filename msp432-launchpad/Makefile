#
# Copyright (c) 2015, Ari Suutari <ari@stonepile.fi>.
# All rights reserved. 
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 
#  1. Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#  2. Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
#  3. The name of the author may not be used to endorse or promote
#     products derived from this software without specific prior written
#     permission. 
# 
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
# OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
# INDIRECT,  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
# OF THE POSSIBILITY OF SUCH DAMAGE.

RELROOT = ../../picoos/

PORT ?= cortex-m
CPU ?= msp432
CORTEX = m4
export CORTEX

BUILD ?= DEBUG

EXTRA_CFLAGS=-std=gnu99
LD_SCRIPTS=launchpad.ld

include $(RELROOT)make/common.mak

NANO = 1
TARGET = mp-test
SRC_TXT =	startup.c test.c ../romfsdata.c mptask.c modlaunchpad.c ../../micropython/ports/unix/file.c spibus.c mmcspi.c
SRC_HDR=
SRC_OBJ = 
SRC_LIB = -lm

# CMSIS setup
CMSIS_MODULES=$(CURRENTDIR)/../../cmsis-ports/msp432-driverlib
MSP432_CHIP = __MSP432P401R__
export MSP432_CHIP

DIR_CONFIG = $(CURRENTDIR)
DIR_OUTPUT = $(CURRENTDIR)/bin
MODULES +=  ../../picoos-micro ../../picoos-python

POSTLINK1 = arm-none-eabi-size $(TARGETOUT)


# ---------------------------------------------------------------------------
# BUILD THE EXECUTABLE
# ---------------------------------------------------------------------------

include $(MAKE_OUT)
