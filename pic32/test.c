/*
 * Copyright (c) 2015, Ari Suutari <ari@stonepile.fi>.
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. The name of the author may not be used to endorse or promote
 *     products derived from this software without specific prior written
 *     permission. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
 * INDIRECT,  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <picoos.h>
#include <picoos-u.h>

#include <plib.h>

// Configuration Bit settings
// SYSCLK = 40 MHz (8MHz FRC / FPLLIDIV * FPLLMUL / FPLLODIV)
// PBCLK = 20 MHz
// FRC w/PLL
// WDT OFF
// Other options are don't care
//

#pragma config FNOSC = FRCPLL
#pragma config FPLLIDIV = DIV_2
#pragma config FPLLMUL = MUL_20
#pragma config FPLLODIV = DIV_2
#pragma config FPBDIV = DIV_2
#pragma config FSOSCEN = ON
#pragma config FWDTEN = OFF

void pyTask(void*);

void pyTask(void* arg)
{
  char* argv[] = { "python" };
  uosInit();
  uosBootDiag();

  mp_main(1, argv);
}

int main(int argc, char **argv)
{
  SYSTEMConfig(PORTCFG_CRYSTAL_CLOCK, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);
  mJTAGPortEnable(DEBUG_JTAGPORT_OFF);

  SYSKEY = 0xAA996655;            // Write Key1 to SYSKEY
  SYSKEY = 0x556699AA;            // Write Key2 to SYSKEY

  OSCCONbits.SLPEN = 1;           // Sleep when idle
  RPB14Rbits.RPB14R=2;            //Sets RPB14 as U2TX. (pin 25)
 // U1RXRbits.U1RXR=2;            //Sets RPA4 as U1RX. (pin 12)

  OSCCONSET = 2;                  // Keep secondary osc running
  SYSKEY = 0;                     // Locks the pin Configurations

  /*
   * Start scheduler.
   */
  nosInit(pyTask, NULL, 2, 4096, 1024);
  return 0;
}
