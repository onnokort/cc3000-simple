/* 
 * Copyright (C) 2013 Onno Kortmann <onno@gmx.net>
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "spi.h"
#include "evnt_handler.h"
#include "hardware.h"

void cc3k_global_irq_enable(char dummy) {dummy=dummy; }

void cc3k_hardware_init(void) {
    cc3k_set_enable(0);
    cc3k_set_cs(1);
    cc3k_set_clk(0);
    cc3k_set_dout(0);
}

static char cc3k_pseudo_irq_en=0;

long WlanReadInterruptPin(void) { return cc3k_get_irq(); }
void WlanInterruptEnable(void) { cc3k_pseudo_irq_en=1; }
void WlanInterruptDisable(void) { cc3k_pseudo_irq_en=0; }
void WriteWlanPin(unsigned char val) { cc3k_set_enable(val); }

volatile unsigned cc3k_regular_cnt;

void cc3k_regular() {
    cc3k_regular_cnt++;
    if (cc3k_pseudo_irq_en && !cc3k_get_irq())
        CC3000InterruptHandler();
    if ((cc3k_regular_cnt & 0x3f)==0)
        hci_unsolicited_event_handler();
}
