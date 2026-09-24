/****************************************************************************
 * arch/arm/src/gd32h7xx/gd32h7xx_timerisr.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdint.h>
#include <time.h>
#include <debug.h>
#include <nuttx/arch.h>
#include <nuttx/timers/arch_timer.h>
#include <arch/board/board.h>

#include "nvic.h"
#include "clock/clock.h"
#include "arm_internal.h"

#include "chip.h"
#include "gd32h7xx.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* The desired timer interrupt frequency is provided by the definition
 * CLK_TCK (see include/time.h).  CLK_TCK defines the desired number of
 * system clock ticks per second.  That value is a user configurable setting
 * that defaults to 100 (100 ticks per second = 10 MS interval).
 *
 * The RCU feeds the Cortex System Timer (SysTick) with the system clock
 * CK_SYS (or CK_SYS/8), NOT with HCLK.
 *
 * GD32H737/757/759 User Manual Rev1.6, page 310 (System timer):
 *   "SysTick 时钟源可选择为 CK_SYS 或 CK_SYS/8。当 SysTick 时钟源为
 *    CK_SYS (CK_SYS=a MHz) 时，SYST_RVR 寄存器值设置为 (a*1000-1)".
 * GD32H737/757/759 User Manual Rev1.6, page 208 (clock tree):
 *   "RCU 通过系统时钟（CK_SYS）8 分频后作为 Cortex 系统定时器（SysTick）
 *    的外部时钟……可选择上述时钟或系统时钟（CK_SYS）时钟作为 SysTick 时钟".
 *
 * => SysTick runs on CK_SYS = 600MHz (CLKSOURCE=1), NOT on the AHB-divided
 *    HCLK (300MHz).  This is a GD32H7 difference vs. stock ARMv7-M where
 *    SysTick uses the processor clock (HCLK).
 *
 * The AHB prescaler is DIV2 (HCLK=300MHz) only because the AHB domain max
 * is 300MHz (manual page 208); it does NOT change the SysTick source.
 *
 * The reload MUST be derived from GD32_SYSCLK_FREQUENCY (600MHz), NOT
 * GD32_HCLK_FREQUENCY.  Using HCLK here yields 200Hz (2x too fast) and
 * causes SysTick ISR overload -> usleep stalls / sleep() HardFault.
 */

#define SYSTICK_RELOAD ((GD32_SYSCLK_FREQUENCY / CLK_TCK) - 1)

/* The size of the reload field is 24 bits.  Verify that the reload value
 * will fit in the reload register.
 */

#if SYSTICK_RELOAD > 0x00ffffff
#  error SYSTICK_RELOAD exceeds the range of the RELOAD register
#endif

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Function:  gd32_timerisr
 *
 * Description:
 *   The timer ISR will perform a variety of services for various portions
 *   of the systems.
 *
 ****************************************************************************/

#if !defined(CONFIG_ARMV7M_SYSTICK) && !defined(CONFIG_TIMER_ARCH)

static int gd32_timerisr(int irq, uint32_t *regs, void *arg)
{
  /* Process timer interrupt */

  nxsched_process_timer();

  return 0;
}
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Function:  up_timer_initialize
 *
 * Description:
 *   This function is called during start-up to initialize
 *   the timer interrupt.
 *
 ****************************************************************************/

void up_timer_initialize(void)
{
  uint32_t regval;

  /* Clock diagnostic: dump actual RCU + SysTick state so we can verify
   * HCLK vs the reload value (a mismatch here = wrong tick rate).
   */

  syslog(LOG_INFO, "TICK: CFG0=%08x CTL=%08x PLL0=%08x\n",
         (unsigned int)getreg32(GD32_RCU_CFG0),
         (unsigned int)getreg32(GD32_RCU_CTL),
         (unsigned int)getreg32(GD32_RCU_PLL0));
  syslog(LOG_INFO, "TICK: SYSCLK=%lu HCLK=%lu RELOAD=%lu\n",
         (unsigned long)GD32_SYSCLK_FREQUENCY,
         (unsigned long)GD32_HCLK_FREQUENCY,
         (unsigned long)SYSTICK_RELOAD);

  /* Set the SysTick interrupt to the default priority */

  regval = getreg32(NVIC_SYSH12_15_PRIORITY);
  regval &= ~NVIC_SYSH_PRIORITY_PR15_MASK;
  regval |= (NVIC_SYSH_PRIORITY_DEFAULT << NVIC_SYSH_PRIORITY_PR15_SHIFT);
  putreg32(regval, NVIC_SYSH12_15_PRIORITY);

  /* Make sure that the SYSTICK clock source is set correctly */

#if defined(CONFIG_ARMV7M_SYSTICK) && defined(CONFIG_TIMER_ARCH)
  up_timer_set_lowerhalf(systick_initialize(true, GD32_SYSCLK_FREQUENCY,
                                             -1));
#else
  /* Configure SysTick to interrupt at the requested rate */

  putreg32(SYSTICK_RELOAD, NVIC_SYSTICK_RELOAD);

  /* Attach the timer interrupt vector */

  irq_attach(GD32_IRQ_SYSTICK, (xcpt_t)gd32_timerisr, NULL);

  /* Enable SysTick interrupts */

  putreg32((NVIC_SYSTICK_CTRL_CLKSOURCE | NVIC_SYSTICK_CTRL_TICKINT |
            NVIC_SYSTICK_CTRL_ENABLE), NVIC_SYSTICK_CTRL);

  /* And enable the timer interrupt */

  up_enable_irq(GD32_IRQ_SYSTICK);
#endif
}
