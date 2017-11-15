/*
 * Copyright (c) 2006-2014, Ari Suutari <ari@stonepile.fi>.
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

#include "driverlib.h"

uint32_t SystemCoreClock;
void SystemInit()
{
  /*
   * Turn FPU on to allow floating point code.
   */
  MAP_FPU_enableModule();
  MAP_FPU_enableLazyStacking();

  /*
   * Configure crystal pins.
   */
  MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_PJ,
          GPIO_PIN3 | GPIO_PIN4, GPIO_PRIMARY_MODULE_FUNCTION);

  MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_PJ,
          GPIO_PIN0 | GPIO_PIN1, GPIO_PRIMARY_MODULE_FUNCTION);

  CS_setExternalClockSourceFrequency(32768,48000000);

#if 0
  MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);
  MAP_FlashCtl_setWaitState(FLASH_BANK0, 2);
  MAP_FlashCtl_setWaitState(FLASH_BANK1, 2);
#endif

#ifdef USE_HFXT
  /*
   * Confgure MCLK, HSMCLK & SMCLK to HFXT/2 (24 Mhz)
   */
  CS_startHFXT(false);
  MAP_CS_initClockSignal(CS_MCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_2);
  MAP_CS_initClockSignal(CS_HSMCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_2);
  MAP_CS_initClockSignal(CS_SMCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_2);

#else

  /*
   * Confgure MCLK, HSMCLK & SMCLK to DCO (24 Mhz)
   */
  CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_24);
  MAP_CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
  MAP_CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
  MAP_CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);

#endif

  /*
   * Configure ACLK & BCLK as LFXT (32768 Hz)
   */
  CS_startLFXT(false);
  MAP_CS_initClockSignal(CS_ACLK, CS_LFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);
  MAP_CS_initClockSignal(CS_BCLK, CS_LFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);

  SystemCoreClock = CS_getMCLK();

  MAP_SysCtl_enableSRAMBankRetention(SYSCTL_SRAM_BANK7);

 // console input SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

}

void Default_Handler(void);
void PreReset_Handler(void);

void Default_Handler()
{
  __disable_irq();
  while (1)
    ;
}

extern unsigned int __stack[];

PORT_WEAK_HANDLER(SysTick_Handler);
PORT_WEAK_HANDLER(PSS_Handler);
PORT_WEAK_HANDLER(CS_Handler);
PORT_WEAK_HANDLER(PCM_Handler);
PORT_WEAK_HANDLER(WDT_Handler);
PORT_WEAK_HANDLER(FPU_Handler);
PORT_WEAK_HANDLER(FLCTL_Handler);
PORT_WEAK_HANDLER(COMP_E0_Handler);
PORT_WEAK_HANDLER(COMP_E1_Handler);
PORT_WEAK_HANDLER(TA0_0_Handler);
PORT_WEAK_HANDLER(TA0_N_Handler);
PORT_WEAK_HANDLER(TA1_0_Handler);
PORT_WEAK_HANDLER(TA1_N_Handler);
PORT_WEAK_HANDLER(TA2_0_Handler);
PORT_WEAK_HANDLER(TA2_N_Handler);
PORT_WEAK_HANDLER(TA3_0_Handler);
PORT_WEAK_HANDLER(TA3_N_Handler);
PORT_WEAK_HANDLER(EUSCIA0_Handler);
PORT_WEAK_HANDLER(EUSCIA1_Handler);
PORT_WEAK_HANDLER(EUSCIA2_Handler);
PORT_WEAK_HANDLER(EUSCIA3_Handler);
PORT_WEAK_HANDLER(EUSCIB0_Handler);
PORT_WEAK_HANDLER(EUSCIB1_Handler);
PORT_WEAK_HANDLER(EUSCIB2_Handler);
PORT_WEAK_HANDLER(EUSCIB3_Handler);
PORT_WEAK_HANDLER(ADC12_Handler);
PORT_WEAK_HANDLER(T32_INT1_Handler);
PORT_WEAK_HANDLER(T32_INT2_Handler);
PORT_WEAK_HANDLER(T32_INTC_Handler);
PORT_WEAK_HANDLER(AES_Handler);
PORT_WEAK_HANDLER(RTC_Handler);
PORT_WEAK_HANDLER(DMA_ERR_Handler);
PORT_WEAK_HANDLER(DMA_INT3_Handler);
PORT_WEAK_HANDLER(DMA_INT2_Handler);
PORT_WEAK_HANDLER(DMA_INT1_Handler);
PORT_WEAK_HANDLER(DMA_INT0_Handler);
PORT_WEAK_HANDLER(PORT1_Handler);
PORT_WEAK_HANDLER(PORT2_Handler);
PORT_WEAK_HANDLER(PORT3_Handler);
PORT_WEAK_HANDLER(PORT4_Handler);
PORT_WEAK_HANDLER(PORT5_Handler);
PORT_WEAK_HANDLER(PORT6_Handler);

void PreReset_Handler()
{
  /*
   * Stop WDT before Reset processing, otherwise 
   * it will reset the chip before we reach main.
   */
  MAP_WDT_A_holdTimer();
  Reset_Handler();
}

PortExcHandlerFunc vectorTable[] __attribute__ ((section(".vectors"))) =
{ 
    (PortExcHandlerFunc) __stack,  // stack pointer
    PreReset_Handler,              // The reset handler
    Reset_Handler,                 // The NMI handler
    HardFault_Handler,             // The hard fault handler
    Reset_Handler,                 // The MPU fault handler
    Reset_Handler,                 // The bus fault handler
    UsageFault_Handler,            // The usage fault handler
    0,                             // Reserved
    0,                             // Reserved
    0,                             // Reserved
    0,                             // Reserved
    SVC_Handler,                   // SVCall handler
    Reset_Handler,                 // Debug monitor handler
    0,                             // Reserved
    PendSV_Handler,                // The PendSV handler
    SysTick_Handler,               // The SysTick handler
    PSS_Handler,                   // PSS ISR
    CS_Handler,                    // CS ISR 
    PCM_Handler,                   // PCM ISR
    WDT_Handler,                   // WDT ISR
    FPU_Handler,                   // FPU ISR
    FLCTL_Handler,                 // FLCTL ISR
    COMP_E0_Handler,               // COMP_E0_MODULE ISR
    COMP_E1_Handler,               // COMP_E1_MODULE ISR
    TA0_0_Handler,                 // TA0_0 ISR
    TA0_N_Handler,                 // TA0_N ISR
    TA1_0_Handler,                 // TA1_0 ISR
    TA1_N_Handler,                 // TA1_N ISR
    TA2_0_Handler,                 // TA2_0 ISR
    TA2_N_Handler,                 // TA2_N ISR
    TA3_0_Handler,                 // TA3_0 ISR
    TA3_N_Handler,                 // TA3_N ISR
    EUSCIA0_Handler,               // EUSCIA0 ISR
    EUSCIA1_Handler,               // EUSCIA1 ISR
    EUSCIA2_Handler,               // EUSCIA2 ISR
    EUSCIA3_Handler,               // EUSCIA3 ISR
    EUSCIB0_Handler,               // EUSCIB0 ISR
    EUSCIB1_Handler,               // EUSCIB1 ISR
    EUSCIB2_Handler,               // EUSCIB2 ISR
    EUSCIB3_Handler,               // EUSCIB3 ISR
    ADC12_Handler,                 // ADC12 ISR
    T32_INT1_Handler,              // T32_INT1 ISR
    T32_INT2_Handler,              // T32_INT2 ISR
    T32_INTC_Handler,              // T32_INTC ISR
    AES_Handler,                   // AES ISR
    RTC_Handler,                   // RTC ISR
    DMA_ERR_Handler,               // DMA_ERR ISR
    DMA_INT3_Handler,              // DMA_INT3 ISR
    DMA_INT2_Handler,              // DMA_INT2 ISR
    DMA_INT1_Handler,              // DMA_INT1 ISR
    DMA_INT0_Handler,              // DMA_INT0 ISR
    PORT1_Handler,                 // PORT1 ISR
    PORT2_Handler,                 // PORT2 ISR
    PORT3_Handler,                 // PORT3 ISR
    PORT4_Handler,                 // PORT4 ISR
    PORT5_Handler,                 // PORT5 ISR
    PORT6_Handler,                 // PORT6 ISR
    Default_Handler,               // Reserved 41
    Default_Handler,               // Reserved 42
    Default_Handler,               // Reserved 43
    Default_Handler,               // Reserved 44
    Default_Handler,               // Reserved 45
    Default_Handler,               // Reserved 46
    Default_Handler,               // Reserved 47
    Default_Handler,               // Reserved 48
    Default_Handler,               // Reserved 49
    Default_Handler,               // Reserved 50
    Default_Handler,               // Reserved 51
    Default_Handler,               // Reserved 52
    Default_Handler,               // Reserved 53
    Default_Handler,               // Reserved 54
    Default_Handler,               // Reserved 55
    Default_Handler,               // Reserved 56
    Default_Handler,               // Reserved 57
    Default_Handler,               // Reserved 58
    Default_Handler,               // Reserved 59
    Default_Handler,               // Reserved 60
    Default_Handler,               // Reserved 61
    Default_Handler,               // Reserved 62
    Default_Handler,               // Reserved 63
    Default_Handler                // Reserved 64
};
