#-*-Makefile-*- vim:syntax=make
#
# Copyright (c) 2013 OSW. All rights reserved.
# Copyright (c) 2008-2012 the MansOS team. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#  * Redistributions of source code must retain the above copyright notice,
#    this list of  conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above copyright
#   notice, this list of conditions and the following disclaimer in the
#   documentation and/or other materials provided with the distribution.
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

#############################################
# Energy Measuring board
#############################################

#############################################
# Define platform variables

ARCH = msp430
MCU_MODEL = msp430f1611

# Upload target specifically for EM board
UPLOAD_TARGET=upload-tilib

# Default clock speed: 1MHz
ifeq ($(USE_HARDWARE_TIMERS),y)
CPU_MHZ ?= 4
else
CPU_MHZ ?= 1  # actually the default DCO frequency is around 800 kHz
endif

CFLAGS += -DPLATFORM_EM=1 

#############################################
# Define platform-specific sources
# (excluding architecture-specific sources)

PSOURCES += $(SRC)/platforms/em/platform.c
PSOURCES += $(SRC)/chips/msp430/msp430x1xx_clock.c
PSOURCES-$(USE_ADS1115) += $(SRC)/chips/ads1115/ads1115.c
PSOURCES-$(USE_ADS7223) += $(SRC)/chips/ads7223/ads7223.c
