/****************************************************************************
 * arch/arm/src/gd32h7xx/hardware/gd32h7xx_tli.h
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

#ifndef __ARCH_ARM_SRC_GD32H7_HARDWARE_GD32H7XX_TLI_H
#define __ARCH_ARM_SRC_GD32H7_HARDWARE_GD32H7XX_TLI_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdint.h>

#include "chip.h"
#include "gd32h759im_memorymap.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* BIT / BITS helpers (fallback if not provided by NuttX) */

#ifndef BIT
#  define BIT(n) (1U << (n))
#endif

#ifndef BITS
#  define BITS(a, b) (((1U << ((b) - (a) + 1)) - 1U) << (a))
#endif

/* TLI register offsets */

#define GD32_TLI_SPSZ_OFFSET          0x0008   /* TLI synchronous pulse size register */
#define GD32_TLI_BPSZ_OFFSET          0x000c   /* TLI back-porch size register */
#define GD32_TLI_ASZ_OFFSET           0x0010   /* TLI active size register */
#define GD32_TLI_TSZ_OFFSET           0x0014   /* TLI total size register */
#define GD32_TLI_CTL_OFFSET           0x0018   /* TLI control register */
#define GD32_TLI_RL_OFFSET            0x0024   /* TLI reload Layer register */
#define GD32_TLI_BGC_OFFSET           0x002c   /* TLI background color register */
#define GD32_TLI_INTEN_OFFSET         0x0034   /* TLI interrupt enable register */
#define GD32_TLI_INTF_OFFSET          0x0038   /* TLI interrupt flag register */
#define GD32_TLI_INTC_OFFSET          0x003c   /* TLI interrupt flag clear register */
#define GD32_TLI_LM_OFFSET            0x0040   /* TLI line mark register */
#define GD32_TLI_CPPOS_OFFSET         0x0044   /* TLI current pixel position register */
#define GD32_TLI_STAT_OFFSET          0x0048   /* TLI status register */
#define GD32_TLI_LAYER0_OFFSET        0x0084   /* TLI layer0 base address */
#define GD32_TLI_LAYER1_OFFSET        0x0104   /* TLI layer1 base address */

/* TLI registers */

#define GD32_TLI_SPSZ                 (GD32_TLI_BASE + GD32_TLI_SPSZ_OFFSET)
#define GD32_TLI_BPSZ                 (GD32_TLI_BASE + GD32_TLI_BPSZ_OFFSET)
#define GD32_TLI_ASZ                  (GD32_TLI_BASE + GD32_TLI_ASZ_OFFSET)
#define GD32_TLI_TSZ                  (GD32_TLI_BASE + GD32_TLI_TSZ_OFFSET)
#define GD32_TLI_CTL                  (GD32_TLI_BASE + GD32_TLI_CTL_OFFSET)
#define GD32_TLI_RL                   (GD32_TLI_BASE + GD32_TLI_RL_OFFSET)
#define GD32_TLI_BGC                  (GD32_TLI_BASE + GD32_TLI_BGC_OFFSET)
#define GD32_TLI_INTEN                (GD32_TLI_BASE + GD32_TLI_INTEN_OFFSET)
#define GD32_TLI_INTF                 (GD32_TLI_BASE + GD32_TLI_INTF_OFFSET)
#define GD32_TLI_INTC                 (GD32_TLI_BASE + GD32_TLI_INTC_OFFSET)
#define GD32_TLI_LM                   (GD32_TLI_BASE + GD32_TLI_LM_OFFSET)
#define GD32_TLI_CPPOS                (GD32_TLI_BASE + GD32_TLI_CPPOS_OFFSET)
#define GD32_TLI_STAT                 (GD32_TLI_BASE + GD32_TLI_STAT_OFFSET)
#define GD32_TLI_LAYER0               (GD32_TLI_BASE + GD32_TLI_LAYER0_OFFSET)
#define GD32_TLI_LAYER1               (GD32_TLI_BASE + GD32_TLI_LAYER1_OFFSET)

/* TLI layer register offsets (relative to LAYERx base) */

#define GD32_TLI_LXCTL_OFFSET         0x0000   /* TLI layer x control register */
#define GD32_TLI_LXHPOS_OFFSET        0x0004   /* TLI layer x horizontal position parameters register */
#define GD32_TLI_LXVPOS_OFFSET        0x0008   /* TLI layer x vertical position parameters register */
#define GD32_TLI_LXCKEY_OFFSET        0x000c   /* TLI layer x color key register */
#define GD32_TLI_LXPPF_OFFSET         0x0010   /* TLI layer x packeted pixel format register */
#define GD32_TLI_LXSA_OFFSET          0x0014   /* TLI layer x specified alpha register */
#define GD32_TLI_LXDC_OFFSET          0x0018   /* TLI layer x default color register */
#define GD32_TLI_LXBLEND_OFFSET       0x001c   /* TLI layer x blending register */
#define GD32_TLI_LXFBADDR_OFFSET      0x0028   /* TLI layer x frame base address register */
#define GD32_TLI_LXFLLEN_OFFSET       0x002c   /* TLI layer x frame line length register */
#define GD32_TLI_LXFTLN_OFFSET        0x0030   /* TLI layer x frame total line number register */
#define GD32_TLI_LXLUT_OFFSET         0x0040   /* TLI layer x look up table register */

#define GD32_TLI_LXCTL(layerx)        ((layerx) + GD32_TLI_LXCTL_OFFSET)
#define GD32_TLI_LXHPOS(layerx)       ((layerx) + GD32_TLI_LXHPOS_OFFSET)
#define GD32_TLI_LXVPOS(layerx)       ((layerx) + GD32_TLI_LXVPOS_OFFSET)
#define GD32_TLI_LXCKEY(layerx)       ((layerx) + GD32_TLI_LXCKEY_OFFSET)
#define GD32_TLI_LXPPF(layerx)        ((layerx) + GD32_TLI_LXPPF_OFFSET)
#define GD32_TLI_LXSA(layerx)         ((layerx) + GD32_TLI_LXSA_OFFSET)
#define GD32_TLI_LXDC(layerx)         ((layerx) + GD32_TLI_LXDC_OFFSET)
#define GD32_TLI_LXBLEND(layerx)      ((layerx) + GD32_TLI_LXBLEND_OFFSET)
#define GD32_TLI_LXFBADDR(layerx)     ((layerx) + GD32_TLI_LXFBADDR_OFFSET)
#define GD32_TLI_LXFLLEN(layerx)      ((layerx) + GD32_TLI_LXFLLEN_OFFSET)
#define GD32_TLI_LXFTLN(layerx)       ((layerx) + GD32_TLI_LXFTLN_OFFSET)
#define GD32_TLI_LXLUT(layerx)        ((layerx) + GD32_TLI_LXLUT_OFFSET)

/* TLI_SPSZ */

#define TLI_SPSZ_VPSZ                 BITS(0,11)   /* size of the vertical synchronous pulse */
#define TLI_SPSZ_HPSZ                 BITS(16,27)  /* size of the horizontal synchronous pulse */

/* TLI_BPSZ */

#define TLI_BPSZ_VBPSZ                BITS(0,11)   /* size of the vertical back porch plus synchronous pulse */
#define TLI_BPSZ_HBPSZ                BITS(16,27)  /* size of the horizontal back porch plus synchronous pulse */

/* TLI_ASZ */

#define TLI_ASZ_VASZ                  BITS(0,11)   /* size of the vertical active area */
#define TLI_ASZ_HASZ                  BITS(16,27)  /* size of the horizontal active area */

/* TLI_TSZ */

#define TLI_TSZ_VTSZ                  BITS(0,11)   /* size of the vertical total area */
#define TLI_TSZ_HTSZ                  BITS(16,27)  /* size of the horizontal total area */

/* TLI_CTL */

#define TLI_CTL_TLIEN                 BIT(0)       /* TLI enable bit */
#define TLI_CTL_BDB                   BITS(4,6)    /* blue channel dither bits number */
#define TLI_CTL_GDB                   BITS(8,10)   /* green channel dither bits number */
#define TLI_CTL_RDB                   BITS(12,14)  /* red channel dither bits number */
#define TLI_CTL_LFCS                  BITS(16,17)  /* low frequency clock source */
#define TLI_CTL_DFEN                  BIT(21)      /* dither function enable */
#define TLI_CTL_CLKPS                 BIT(28)      /* pixel clock polarity selection */
#define TLI_CTL_DEPS                  BIT(29)      /* data enable polarity selection */
#define TLI_CTL_VPPS                  BIT(30)      /* vertical pulse polarity selection */
#define TLI_CTL_HPPS                  BIT(31)      /* horizontal pulse polarity selection */

/* TLI_RL */

#define TLI_RL_L0RE                  BIT(0)       /* layer0 reload enable */
#define TLI_RL_L1RE                  BIT(1)       /* layer1 reload enable */

/* TLI_BGC */

#define TLI_BGC_BVB                  BITS(0,7)    /* background color blue */
#define TLI_BGC_BVG                  BITS(8,15)   /* background color green */
#define TLI_BGC_BVR                  BITS(16,23)  /* background color red */

/* TLI_INTEN */

#define TLI_INTEN_LXIE               BIT(0)       /* line mark interrupt enable */
#define TLI_INTEN_TEIE               BIT(1)       /* transfer error interrupt enable */
#define TLI_INTEN_FEIE               BIT(2)       /* FIFO error interrupt enable */
#define TLI_INTEN_FBEIE              BIT(3)       /* frame blank interrupt enable */
#define TLI_INTEN_RRIE               BIT(4)       /* register reload interrupt enable */

/* TLI layer x control register (TLI_LXCTL) */

#define TLI_LXCTL_LXEN               BIT(0)       /* layer x enable bit */
#define TLI_LXCTL_DFEN               BIT(8)       /* layer x dither function enable */
#define TLI_LXCTL_CKEN               BIT(9)       /* layer x color keying enable */
#define TLI_LXCTL_LUTEN              BIT(10)      /* layer x LUT enable */

/* TLI layer x horizontal position parameters register (TLI_LXHPOS) */

#define TLI_LXHPOS_WLP               BITS(0,11)   /* layer x window left position */
#define TLI_LXHPOS_WRP               BITS(16,27)  /* layer x window right position */

/* TLI layer x vertical position parameters register (TLI_LXVPOS) */

#define TLI_LXVPOS_WTP               BITS(0,11)   /* layer x window top position */
#define TLI_LXVPOS_WBP               BITS(16,27)  /* layer x window bottom position */

/* TLI layer x packeted pixel format register (TLI_LXPPF) */

#define TLI_LXPPF_PPF                BITS(0,2)    /* layer x packeted pixel format */

#define LAYER_PPF_ARGB8888           0            /* layer x pixel format ARGB8888 */
#define LAYER_PPF_RGB888             1            /* layer x pixel format RGB888 */
#define LAYER_PPF_RGB565             2            /* layer x pixel format RGB565 */
#define LAYER_PPF_ARGB1555           3            /* layer x pixel format ARGB1555 */
#define LAYER_PPF_ARGB4444           4            /* layer x pixel format ARGB4444 */
#define LAYER_PPF_L8                 5            /* layer x pixel format L8 */
#define LAYER_PPF_AL44               6            /* layer x pixel format AL44 */
#define LAYER_PPF_AL88               7            /* layer x pixel format AL88 */

/* TLI layer x specified alpha register (TLI_LXSA) */

#define TLI_LXSA_SA                  BITS(0,7)    /* layer x specified alpha */

/* TLI layer x default color register (TLI_LXDC) */

#define TLI_LXDC_DCB                 BITS(0,7)    /* layer x default color blue */
#define TLI_LXDC_DCG                 BITS(8,15)   /* layer x default color green */
#define TLI_LXDC_DCR                 BITS(16,23)  /* layer x default color red */
#define TLI_LXDC_DCA                 BITS(24,31)  /* layer x default color alpha */

/* TLI layer x blending register (TLI_LXBLEND) */

#define TLI_LXBLEND_ACF2             BITS(0,2)    /* layer x alpha calculation factor 2 */
#define TLI_LXBLEND_ACF1             BITS(8,10)   /* layer x alpha calculation factor 1 */

#define LXBLEND_ACF1(regval)         (BITS(8,10) & ((uint32_t)(regval) << 8))
#define LXBLEND_ACF2(regval)         (BITS(0,2) & ((uint32_t)(regval)))
#define LAYER_ACF1_PASA              LXBLEND_ACF1(6)  /* pixel alpha * specified alpha */
#define LAYER_ACF2_PASA              LXBLEND_ACF2(7)  /* pixel alpha * specified alpha */

/* TLI layer x frame base address register (TLI_LXFBADDR) */

#define TLI_LXFBADDR_FBADD           BITS(0,31)   /* layer x frame buffer base address */

/* TLI layer x frame line length register (TLI_LXFLLEN) */

#define TLI_LXFLLEN_FLL              BITS(0,13)   /* layer x frame line length */
#define TLI_LXFLLEN_STDOFF           BITS(16,29)  /* layer x frame buffer stride offset */

/* TLI layer x frame total line number register (TLI_LXFTLN) */

#define TLI_LXFTLN_FTLN              BITS(0,10)   /* layer x frame total line number */

#endif /* __ARCH_ARM_SRC_GD32H7_HARDWARE_GD32H7XX_TLI_H */
