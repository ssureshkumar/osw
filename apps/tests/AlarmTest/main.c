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

// include OSW standard API
#include "osw.h"

// Declare out timer structures
Alarm_t timer1, timer2;

// Timer #1 callback function
void onTimer1(void *x)
{
    static uint8_t counter;

    PRINTF("onTimer1\n");
    redLedToggle();

    // start (schedule) timer #1
    alarmSchedule(&timer1, 700);

    if (++counter == 3) {
        // In case the counter is 3, start (schedule) timer #2 too
        PRINTF("reschedule alarm\n");
        alarmSchedule(&timer2, 200);
    }
}

// Timer #2 callback function
void onTimer2(void *x)
{
    PRINTF("onTimer2\n");
    blueLedToggle();
}

// Application entry point
void appMain(void)
{
    // Initialize and start timer #1 (after 700 milliseconds)
    alarmInit(&timer1, onTimer1, NULL);
    alarmSchedule(&timer1, 700);

    // Initialize and start timer #2  (after 1000 milliseconds)
    alarmInit(&timer2, onTimer2, NULL);
    alarmSchedule(&timer2, 1000);

    // Enter infinite low-power loop
    for (;;) {
        msleep(2000);
    }
}
