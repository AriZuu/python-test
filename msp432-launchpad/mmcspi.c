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
#include <stdbool.h>

#include "driverlib.h"

// Connections: 
// P1.5 SPICLK
// P1.6 MOSI
// P1.7 MISO
// P5.2 CS

static void    spiOpen(void);
static void    spiClose(void);
static void    spiControl(bool fullSpeed);
static void    spiCs(bool select);
static uint8_t spiXchg(uint8_t data);

const UosMMC_SPI mmcSpi = {

  .open    = spiOpen,
  .close   = spiClose,
  .control = spiControl,
  .cs      = spiCs,
  .xchg    = spiXchg,
  .xmit    = uosMMC_SPIxmit,
  .rcvr    = uosMMC_SPIrcvr
};

static const eUSCI_SPI_MasterConfig spiMasterConfig =
{
  EUSCI_B_SPI_CLOCKSOURCE_SMCLK,             // SMCLK Clock Source
  24000000,                                  // SMCLK = 24 Mhz
  400000,                                    // SPICLK = 400khz
  EUSCI_B_SPI_MSB_FIRST,                     // MSB First
  EUSCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT,    // Phase
  EUSCI_B_SPI_CLOCKPOLARITY_INACTIVITY_HIGH, // High polarity
  EUSCI_B_SPI_3PIN                           // 3Wire SPI Mode
};

void spiOpen ()
{
  GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN2);
  GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN2);

  GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
                                             GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7, 
                                             GPIO_PRIMARY_MODULE_FUNCTION);

  SPI_initMaster(EUSCI_B0_MODULE, &spiMasterConfig);
  SPI_enableModule(EUSCI_B0_MODULE);
}

void spiClose()
{
  SPI_disableModule(EUSCI_B0_MODULE);
}

void spiCs (bool select)
{
  if (select)
    GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN2);
  else
    GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN2);
}

void spiControl(bool max)
{
  SPI_disableModule(EUSCI_B0_MODULE);
  if (max)
    SPI_changeMasterClock(EUSCI_B0_MODULE, 24000000, 10000000);
  else
    SPI_changeMasterClock(EUSCI_B0_MODULE, 24000000, 400000);

  nosPrintf("fullSpeed not implemented\n");
  SPI_enableModule(EUSCI_B0_MODULE);
}

uint8_t spiXchg(uint8_t dat)
{
  SPI_transmitData(EUSCI_B0_MODULE, dat);
  return SPI_receiveData(EUSCI_B0_MODULE);
}

