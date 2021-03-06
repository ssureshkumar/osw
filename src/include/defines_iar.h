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

#ifndef OSW_DEFINES_IAR_H
#define OSW_DEFINES_IAR_H

/// \file
/// IAR compiler-specific defines and headers
///

#include <msp430.h>
#include <intrinsics.h>

#ifndef BV
#define BV(x) (1 << (x))
#endif
#define PRAGMA(x) _Pragma(#x)
#define MESSAGE(x) PRAGMA(message(x))
#define ISR(vec, name) PRAGMA(vector=vec ## _VECTOR) __interrupt void name(void)
// use XISR instead of ISR if symbolic names are wanted
#define XXISR(port, func) ISR(PORT ## port, func)
#define XISR(port, func)  XXISR(port, func)
#define ASM_VOLATILE(x) asm(x)
// attribute for a function place in RAM (i.e. .data section) instead of flash
//# define RAMFUNC __ramfunc   // already defined in IAR headers!

#define UNUSED

#define PRINTF_LIKE

#define ENABLE_INTS() __enable_interrupt()
#define DISABLE_INTS() __disable_interrupt()
#define nop() __no_operation()

#define GET_INTERRUPT_STATUS(status)       \
    status = __get_interrupt_state()

#define SET_INTERRUPT_STATUS(status)       \
    __set_interrupt_state(status)

#define MEMORY_BARRIER() // nothing
#define INLINE // nothing
#define NORETURN // nothing
#define PACKED // nothing
#define NAKED // nothing
#define NO_EPILOGUE PRAGMA(no_epilogue)
#define WEAK_SYMBOL // nothing

#endif
