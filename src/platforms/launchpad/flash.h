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
 */

#ifndef _PLATFORM_LAUNCHPAD_FLASH_H_
#define _PLATFORM_LAUNCHPAD_FLASH_H_

// The values correspond to the MSP430G2231 MCU

// Flash memory location and size
#define MSP430_FLASH_START 0xF800
#define MSP430_FLASH_END   0xFFDE
#define MSP430_FLASH_SIZE  (0xFFFF - MSP430_FLASH_START + 1)

// Flash segment (minimal erasable unit) size
#define MSP430_FLASH_SEGMENT_SIZE  512

// Flash block (maximal writable-at-once unit) size
#define MSP430_FLASH_BLOCK_SIZE    64

// Information memory: four segments of 64 bytes each
#define MSP430_FLASH_INFOMEM_START 0x1000
#define MSP430_FLASH_INFOMEM_END   0x10FF

// Information memory segment size
#define MSP430_FLASH_INFOMEM_SEGMENT_SIZE  64

#endif
