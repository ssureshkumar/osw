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

#ifndef LIGHT_HAL_H
#define LIGHT_HAL_H

#include <platform.h>
#if USE_ADC
#include <adc.h>
#endif

#ifndef lightRead

// On TelosB analog light sensors (visible spectrum and PAR) are attached to ADC
// No on/off functionality available
#define lightInit()
#define lightOn()
#define lightOff()

#ifdef ADC_LIGHT_TOTAL
#define totalSolarRadiationRead() adcRead(ADC_LIGHT_TOTAL)
#else
#define totalSolarRadiationRead() 0
#endif

#ifdef ADC_LIGHT_PHOTOSYNTHETIC
#define photosyntheticRadiationRead() adcRead(ADC_LIGHT_PHOTOSYNTHETIC)
#else
#define photosyntheticRadiationRead() 0
#endif

#define lightRead() totalSolarRadiationRead()

#endif // lightRead not defined in platform-specific way

#endif
