/*
 * Copyright (c) 2013 OSW. All rights reserved.
 * Copyright (c) 2011, Institute of Electronics and Computer Science
 * All rights reserved.
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
 *
 * radio_hal_cc1101.h -- CC1101 radio driver glue
 */

#ifndef PLATFORM_RADIO_H
#define PLATFORM_RADIO_H

#include <cc1101/cc1101.h>

#define RADIO_MAX_PACKET    CC1101_MAX_PACKET_LEN
#define RADIO_TX_POWER_MIN  CC1101_TX_POWER_MIN
#define RADIO_TX_POWER_MAX  CC1101_TX_POWER_MAX

static inline void radioInit(void)
{
    cc1101Init();
}

static inline void radioReinit(void)
{
    cc1101InitSpi();
}

static inline int8_t radioSendHeader(const void *header, uint16_t headerLength,
                                     const void *data,   uint16_t dataLength)
{
    return cc1101Send(header, headerLength, data, dataLength);
}

static inline int16_t radioRecv(void *buffer, uint16_t bufferLength)
{
    return cc1101Read(buffer, bufferLength);
}

static inline void radioDiscard(void)
{
    cc1101Discard();
}

static inline RadioRecvFunction radioSetReceiveHandle(
    RadioRecvFunction functionHandle)
{
    cc1101SetRecvCallback(functionHandle);
    return NULL;
}

static inline void radioOn(void)
{
    cc1101On();
}

static inline void radioOff(void)
{
    cc1101Off();
}

static inline int radioGetRSSI(void)
{
    return cc1101GetRSSI();
}

static inline int8_t radioGetLastRSSI(void)
{
    return cc1101GetLastRSSI();
}

static inline uint8_t radioGetLastLQI(void)
{
    return cc1101GetLastLQI();
}

static inline void radioSetChannel(int channel)
{
    cc1101SetChannel(channel);
}

static inline void radioSetTxPower(uint8_t power)
{
    cc1101SetTxPower(power);
}

static inline bool radioIsChannelClear(void)
{
    return cc1101IsChannelClear();
}

#endif
