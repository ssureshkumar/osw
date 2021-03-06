/*
 * Copyright (c) 2013 OSW. All rights reserved.
 * Copyright (c) 2008-2013 the MansOS team. All rights reserved.
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

#ifndef OSW_NETWORKING_H
#define OSW_NETWORKING_H

/// \file
/// OSW networking public API
///

#include "net_internal.h"
#include "mac.h"

//----------------------------------------------------------
// constants
//----------------------------------------------------------

enum {
    //! Used for listening sockets to listen to all ports
    OSW_PORT_ANY = 0
};

//----------------------------------------------------------
// Functions
//----------------------------------------------------------

//
// Calls networkingInitArch() and other functions; two version are defined in comm.c and nonet.c
//
void networkingInit(void);

//
// Architecture-specific initalization. Defined in HAL
//
void networkingInitArch(void);

///
/// This function is the "center of the hourglass" in OSW networking stack:
/// almost all packets, incoming and outgoing, are passed through it.
/// @param macInfo   the MAC info describing the header of a packet
/// @param data      the data portion of the packet
/// @param len       the lenght of packet's data portion
///
void networkingForwardData(MacInfo_t *macInfo, uint8_t *data, uint16_t len);

#endif
