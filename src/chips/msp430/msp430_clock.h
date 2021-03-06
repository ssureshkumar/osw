/*
 * Copyright (c) 2013 OSW. All rights reserved.
 * Copyright (c) 2008-2012 the MansOS team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of  conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _MSP430_CLOCK_H_
#define _MSP430_CLOCK_H_

#include <stdtypes.h>
#include "msp430_int.h"

// The value returned depends on the system's runtime configuration
// LPM3 is used on MSP430 by default, unles SMCLK is needed by a some component
#define SLEEP_MODE_BITS() \
    ((PWM_USES_SMCLK() || SERIAL_USES_SMCLK() || ADC_USES_SMCLK())  \
    ? LPM1_bits \
    : LPM3_bits)

#define PWM_USES_SMCLK()    false  // PWM is not implemented yet
#define SERIAL_USES_SMCLK() serialUsesSMCLK()
#define ADC_USES_SMCLK()    hplAdcUsesSMCLK()

// set low power mode bits in the SR to sleep, and make sure interrupts are enabled as well
#define ENTER_SLEEP_MODE() _BIS_SR((SLEEP_MODE_BITS() | GIE))
// Warning: this commands works *only* in interrupt handlers!
#define EXIT_SLEEP_MODE() LPM3_EXIT

//===========================================================
// Procedures
//===========================================================

void msp430InitClocks(void);

#define hplInitClocks() msp430InitClocks()

static inline void msp430Init(void) {
    msp430InitPins();
    msp430InitClocks();
}

//===========================================================
//===========================================================

#endif
