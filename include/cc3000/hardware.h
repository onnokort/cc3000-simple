/*
 * hardware.h - Set of hardware macros/functions for the CC3000 driver.
 * To be filled by the application using the code.
 * 
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

#ifndef CC3000_HARDWARE_H
#define CC3000_HARDWARE_H

/* Boolean arguments ('char') to the functions to be filled in always
   correspond to logic levels: 0=LOW, 1=HIGH.
   Functions to be written are documented starting with 'Fill in'.
   */

/*! Fill in for doing a short MCU wait. Should wait for the given number
 * of microseconds (<<1000). WILL be called inside an IRQ. Yes, this is
 * slightly messy.
 * This can be implemented using the SysTick timer.
 * */
void cc3k_delay_us(unsigned);

/*! Fill in for doing an MCU wait. Should wait for the given number
 * of milliseconds (<=1000). WILL NOT be called inside an IRQ.
 *
 * Waiting for the SysTick timer is a good implementation for this. 
 * */
void cc3k_delay_ms(unsigned);

/*! Fill in for reading the SPI_IRQ pin. Should return 1=HIGH, 0=LOW
 * for SPI_IRQ line (pin 14). */
char cc3k_get_irq(void);

/*! Fill in for handling the SPI_CS line (pin 12) of the CC3K */
void cc3k_set_cs(char);

/*! Fill in for setting the SPI_CLK line (pin 17). Any fixed delay (busy loop)
 * for slowing down the generated SPI signal should also be put in here. */
void cc3k_set_clk(char);

/*! Fill in for setting the SPI_DIN line (=host SPI_DOUT) (pin 15) */
void cc3k_set_dout(char);

/*! Fill in to return logic state of the SPI_DOUT line (=host SPI_DIN) (pin 13) */
char cc3k_get_din(void);

/*! Fill in to set the status of the CC3000 enable (pin 26) */
void cc3k_set_enable(char);

/*! Fill in to prepare SPI ports for data in/out. This should set up the port
 * directions, peripheral clock enables etc. for the software SPI pins. */
void cc3k_hardware_prepare(void);

/*! CC3000 hardware init. This will call cc3k_prepare. This will set the lines
 * going to the CC3000 to their initial state. */
void cc3k_hardware_init(void);

/*! (Fill in) Disable (0) or enable(1) all interrupts, to make
 * sending/receiving of each SPI byte deterministic. It seems like my variant
 * of the CC3K can create internal timeouts if the byte transfers do not
 * happen fast enough. This function can be left empty (as-is), if no further
 * problems with SPI communications occur. */
void cc3k_global_irq_enable(char) __attribute__((weak)); 

/*! Regular house keeping for CC3000.
  Call this function about every 1ms. This will do the asynchronous processing
  of packets from the CC3K, as well as doing IRQ polling. */
void cc3k_regular();

//! This counter will be increased by one with every call to cc3k_regular
extern volatile unsigned cc3k_regular_cnt;
//-----------------------------------------------------------------------------
/*! Functions to give to wlan_init. */
long WlanReadInterruptPin(void);
void WlanInterruptEnable(void);
void WlanInterruptDisable(void);
void WriteWlanPin(unsigned char);

#endif
