/****************************************************************************
 * arch/arm/src/gd32h7xx/hardware/gd32h7xx_exti.h
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

#ifndef __ARCH_ARM_SRC_GD32H7XX_HARDWARE_GD32H7XX_EXTI_H
#define __ARCH_ARM_SRC_GD32H7XX_HARDWARE_GD32H7XX_EXTI_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include "chip.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* EXTI register offsets ****************************************************/

#define GD32_EXTI_INTEN_OFFSET    0x0000  /* Interrupt enable register */
#define GD32_EXTI_EVEN_OFFSET     0x0004  /* Event enable register */
#define GD32_EXTI_RTEN_OFFSET     0x0008  /* Rising edge trigger enable register */
#define GD32_EXTI_FTEN_OFFSET     0x000c  /* Falling edge trigger enable register */
#define GD32_EXTI_SWIEV_OFFSET    0x0010  /* Software interrupt event register */
#define GD32_EXTI_PD_OFFSET       0x0014  /* Pending register */

/* EXTI register addresses **************************************************/

#define GD32_EXTI_INTEN           (GD32_EXTI_BASE + GD32_EXTI_INTEN_OFFSET)
#define GD32_EXTI_EVEN            (GD32_EXTI_BASE + GD32_EXTI_EVEN_OFFSET)
#define GD32_EXTI_RTEN            (GD32_EXTI_BASE + GD32_EXTI_RTEN_OFFSET)
#define GD32_EXTI_FTEN            (GD32_EXTI_BASE + GD32_EXTI_FTEN_OFFSET)
#define GD32_EXTI_SWIEV           (GD32_EXTI_BASE + GD32_EXTI_SWIEV_OFFSET)
#define GD32_EXTI_PD              (GD32_EXTI_BASE + GD32_EXTI_PD_OFFSET)

/* EXTI line definitions ****************************************************/

#define EXTI_0                    (1 << 0)   /* EXTI line 0 */
#define EXTI_1                    (1 << 1)   /* EXTI line 1 */
#define EXTI_2                    (1 << 2)   /* EXTI line 2 */
#define EXTI_3                    (1 << 3)   /* EXTI line 3 */
#define EXTI_4                    (1 << 4)   /* EXTI line 4 */
#define EXTI_5                    (1 << 5)   /* EXTI line 5 */
#define EXTI_6                    (1 << 6)   /* EXTI line 6 */
#define EXTI_7                    (1 << 7)   /* EXTI line 7 */
#define EXTI_8                    (1 << 8)   /* EXTI line 8 */
#define EXTI_9                    (1 << 9)   /* EXTI line 9 */
#define EXTI_10                   (1 << 10)  /* EXTI line 10 */
#define EXTI_11                   (1 << 11)  /* EXTI line 11 */
#define EXTI_12                   (1 << 12)  /* EXTI line 12 */
#define EXTI_13                   (1 << 13)  /* EXTI line 13 */
#define EXTI_14                   (1 << 14)  /* EXTI line 14 */
#define EXTI_15                   (1 << 15)  /* EXTI line 15 */

/* EXTI mode definitions ****************************************************/

#define EXTI_INTERRUPT            0  /* Interrupt mode */
#define EXTI_EVENT                1  /* Event mode */

/* EXTI trigger type definitions ********************************************/

#define EXTI_TRIG_RISING          0  /* Rising edge trigger */
#define EXTI_TRIG_FALLING         1  /* Falling edge trigger */
#define EXTI_TRIG_BOTH            2  /* Both rising and falling edge */
#define EXTI_TRIG_NONE            3  /* No trigger */

#endif /* __ARCH_ARM_SRC_GD32H7XX_HARDWARE_GD32H7XX_EXTI_H */
