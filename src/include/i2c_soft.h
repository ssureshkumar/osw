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

#ifndef OSW_I2C_SOFT_H
#define OSW_I2C_SOFT_H

/// \file
/// Software controlled I2C
///
/// Prior to use you must define SDA and SCL pins using your specific values 
/// - #define SDA_PORT 1
/// - #define SDA_PIN  1
/// - #define SCL_PORT 1
/// - #define SCL_PIN  2
///
/// Note: enable the pullup resistors, or ensure the hardware has them.
///
/// Note: timing may have to be adjusted for a different microcontroller
///

#include <i2c_types.h>
#include <digital.h>
#include <delay.h>

// The communication on SDA (not SCL) is done by switching pad direction.
// For a low level the direction is set to output. 
// For a high level the direction is set to input (must have a pullup resistor).

#define I2C_SCL_OUT()  pinAsOutput(SCL_PORT, SCL_PIN)
#define I2C_SCL_HI()   pinSet(SCL_PORT, SCL_PIN)
#define I2C_SCL_LO()   pinClear(SCL_PORT, SCL_PIN)

#define I2C_SDA_IN()   pinAsInput(SDA_PORT, SDA_PIN)
#define I2C_SDA_OUT()  pinAsOutput(SDA_PORT, SDA_PIN)
#define I2C_SDA_HI()   do { pinAsOutput(SDA_PORT, SDA_PIN); pinSet(SDA_PORT, SDA_PIN); } while (0)
#define I2C_SDA_LO()   do { pinAsOutput(SDA_PORT, SDA_PIN); pinClear(SDA_PORT, SDA_PIN); } while (0)
// #define I2C_SDA_HI()   pinSet(SDA_PORT, SDA_PIN)
// #define I2C_SDA_LO()   pinClear(SDA_PORT, SDA_PIN)

#define I2C_SDA_GET()  pinRead(SDA_PORT, SDA_PIN)
#define I2C_SDA_SET(b) pinWrite(SDA_PORT, SDA_PIN, b)


///
/// Writes a start condition on I2C-bus
/// <pre>
///        ___
/// SDA:      |_____
///        _____
/// SCL :       |___
/// </pre>
///
#define i2cSoftStart() \
    I2C_SDA_HI();      \
    I2C_SCL_HI();      \
    udelay(10);        \
    I2C_SDA_LO();      \
    udelay(10);        \
    I2C_SCL_LO();      \
    udelay(10);


///
/// Writes a stop condition on I2C-bus
/// <pre>
///             ____
/// SDA:   ____|
///           ______
/// SCL :  __|
/// </pre>
///
#define i2cSoftStop()  \
    I2C_SDA_LO();      \
    I2C_SCL_LO();      \
    I2C_SCL_HI();      \
    udelay(10);        \
    I2C_SDA_HI();      \
    udelay(10);        \

///
/// Writes a byte to I2C and checks acknowledge
/// @return 0 on success
///
i2cError_t i2cSoftWriteByte(uint8_t txByte);

///
/// Reads a byte from I2C
/// @return the byte received
///
uint8_t i2cSoftReadByte(i2cAck_t ack);


/**
 * Writes a string to I2C and checks acknowledge
 * @param   addr        address of the slave receiver (7 bits!)
 * @param   buf         the buffer containing the string
 * @param   len         buffer length in bytes
 * @return  0           on success, error code otherwise
 */
i2cError_t i2cSoftWrite(uint8_t addr, const void *buf, uint8_t len);

/**
 * Reads a message into buffer from I2C - requests it from a slave
 * @param   addr        address of the slave transmitter (7 bits!)
 * @param   buf         the buffer to store the message
 * @param   len         buffer length in bytes
 * @return  received byte count
 */
uint8_t i2cSoftRead(uint8_t addr,  void *buf, uint8_t len);


// initialization (setup the pins)
void i2cSoftInit(void);


#endif
