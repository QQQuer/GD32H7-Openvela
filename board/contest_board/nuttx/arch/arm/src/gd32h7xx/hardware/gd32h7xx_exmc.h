/****************************************************************************
 * arch/arm/src/gd32h7xx/hardware/gd32h7xx_exmc.h
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * GD32H759 EXMC SDRAM controller register definitions (subset needed by
 * the SDRAM driver for the W9825G6KH on the GD32H759IMT6 core board).
 *
 ****************************************************************************/

#ifndef __ARCH_ARM_SRC_GD32H7XX_HARDWARE_GD32H7XX_EXMC_H
#define __ARCH_ARM_SRC_GD32H7XX_HARDWARE_GD32H7XX_EXMC_H

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* EXMC peripheral base address.
 * GD32H759 AHB3 map: AXI interconnect matrix = 0x51000000, MDMA = 0x52000000,
 * IPA = 0x52001000, FMC = 0x52002000, EXMC = 0x52004000.
 * NOTE: the GD32H750 example library uses 0x51004000, which is WRONG for the
 * GD32H759 (that range belongs to the AXI interconnect matrix).  The value
 * below comes from the GD32H737/757/759 user manual, section 1.3.
 */

#define GD32_EXMC_CTRL_BASE                 0x52004000

/* SDRAM controller register offsets */

#define GD32_EXMC_SDCTL_OFFSET         0x00000140  /* SDRAM control register */
#define GD32_EXMC_SDTCFG_OFFSET        0x00000148  /* SDRAM timing configuration register */
#define GD32_EXMC_SDCMD_OFFSET         0x00000150  /* SDRAM command register */
#define GD32_EXMC_SDARI_OFFSET         0x00000154  /* SDRAM auto-refresh interval register */
#define GD32_EXMC_SDSTAT_OFFSET        0x00000158  /* SDRAM status register */
#define GD32_EXMC_SDRSCTL_OFFSET       0x00000180  /* SDRAM read sample control register */

#define GD32_EXMC_SDCTL                (GD32_EXMC_CTRL_BASE + GD32_EXMC_SDCTL_OFFSET)
#define GD32_EXMC_SDTCFG               (GD32_EXMC_CTRL_BASE + GD32_EXMC_SDTCFG_OFFSET)
#define GD32_EXMC_SDCMD                (GD32_EXMC_CTRL_BASE + GD32_EXMC_SDCMD_OFFSET)
#define GD32_EXMC_SDARI                (GD32_EXMC_CTRL_BASE + GD32_EXMC_SDARI_OFFSET)
#define GD32_EXMC_SDSTAT               (GD32_EXMC_CTRL_BASE + GD32_EXMC_SDSTAT_OFFSET)
#define GD32_EXMC_SDRSCTL              (GD32_EXMC_CTRL_BASE + GD32_EXMC_SDRSCTL_OFFSET)

/* SDCTL bit fields */

#define GD32_SDCTL_CAW_SHIFT           (0)         /* Bits 0-1: column address width */
#define GD32_SDCTL_CAW_MASK            (3 << GD32_SDCTL_CAW_SHIFT)
#define GD32_SDCTL_CAW_8BIT            (0)         /* 8 bit column address */
#define GD32_SDCTL_CAW_9BIT            (1)         /* 9 bit column address */
#define GD32_SDCTL_CAW_10BIT           (2)         /* 10 bit column address */
#define GD32_SDCTL_CAW_11BIT           (3)         /* 11 bit column address */

#define GD32_SDCTL_RAW_SHIFT           (2)         /* Bits 2-3: row address width */
#define GD32_SDCTL_RAW_MASK            (3 << GD32_SDCTL_RAW_SHIFT)
#define GD32_SDCTL_RAW_11BIT           (0)         /* 11 bit row address */
#define GD32_SDCTL_RAW_12BIT           (1)         /* 12 bit row address */
#define GD32_SDCTL_RAW_13BIT           (2)         /* 13 bit row address */

#define GD32_SDCTL_SDW_SHIFT           (4)         /* Bits 4-5: SDRAM data bus width */
#define GD32_SDCTL_SDW_MASK            (3 << GD32_SDCTL_SDW_SHIFT)
#define GD32_SDCTL_SDW_8BIT            (0)         /* 8 bit data bus */
#define GD32_SDCTL_SDW_16BIT           (1)         /* 16 bit data bus */
#define GD32_SDCTL_SDW_32BIT           (2)         /* 32 bit data bus */

#define GD32_SDCTL_NBK                 (1 << 6)    /* Bit 6: number of banks (1 = 4 banks) */
#define GD32_SDCTL_CL_SHIFT            (7)         /* Bits 7-8: CAS latency */
#define GD32_SDCTL_CL_MASK             (3 << GD32_SDCTL_CL_SHIFT)
#define GD32_SDCTL_CL_1                (1)         /* CAS = 1 */
#define GD32_SDCTL_CL_2                (2)         /* CAS = 2 */
#define GD32_SDCTL_CL_3                (3)         /* CAS = 3 */

#define GD32_SDCTL_WPEN                (1 << 9)    /* Bit 9: write protection enable */
#define GD32_SDCTL_SDCLK_SHIFT         (10)        /* Bits 10-11: SDRAM clock configuration */
#define GD32_SDCTL_SDCLK_MASK          (3 << GD32_SDCTL_SDCLK_SHIFT)
#define GD32_SDCTL_SDCLK_DISABLE       (0)         /* SDCLK disabled */
#define GD32_SDCTL_SDCLK_2             (2)         /* SDCLK = CK_EXMC / 2 */
#define GD32_SDCTL_SDCLK_3             (3)         /* SDCLK = CK_EXMC / 3 */

#define GD32_SDCTL_BRSTRD              (1 << 12)   /* Bit 12: burst read enable */
#define GD32_SDCTL_PIPED_SHIFT         (13)        /* Bits 13-14: pipeline read delay */
#define GD32_SDCTL_PIPED_MASK          (3 << GD32_SDCTL_PIPED_SHIFT)
#define GD32_SDCTL_PIPED_0             (0)         /* 0 CK_EXMC delay */
#define GD32_SDCTL_PIPED_1             (1)         /* 1 CK_EXMC delay */
#define GD32_SDCTL_PIPED_2             (2)         /* 2 CK_EXMC delay */

#define GD32_SDCTL_SDCLK_2_BIT         (1 << 15)   /* Bit 15: SDCLK bit 2 (for 4/5 periods) */

/* SDTCFG bit fields (all values in CK_EXMC periods) */

#define GD32_SDTCFG_LMRD_SHIFT         (0)         /* Bits 0-3: load mode register delay */
#define GD32_SDTCFG_LMRD_MASK          (15 << GD32_SDTCFG_LMRD_SHIFT)
#define GD32_SDTCFG_XSRD_SHIFT         (4)         /* Bits 4-7: exit self-refresh delay */
#define GD32_SDTCFG_XSRD_MASK          (15 << GD32_SDTCFG_XSRD_SHIFT)
#define GD32_SDTCFG_RASD_SHIFT         (8)         /* Bits 8-11: row address select delay */
#define GD32_SDTCFG_RASD_MASK          (15 << GD32_SDTCFG_RASD_SHIFT)
#define GD32_SDTCFG_ARFD_SHIFT         (12)        /* Bits 12-15: auto refresh delay */
#define GD32_SDTCFG_ARFD_MASK          (15 << GD32_SDTCFG_ARFD_SHIFT)
#define GD32_SDTCFG_WRD_SHIFT          (16)        /* Bits 16-19: write recovery delay */
#define GD32_SDTCFG_WRD_MASK          (15 << GD32_SDTCFG_WRD_SHIFT)
#define GD32_SDTCFG_RPD_SHIFT          (20)        /* Bits 20-23: row precharge delay */
#define GD32_SDTCFG_RPD_MASK           (15 << GD32_SDTCFG_RPD_SHIFT)
#define GD32_SDTCFG_RCD_SHIFT          (24)        /* Bits 24-27: row to column delay */
#define GD32_SDTCFG_RCD_MASK           (15 << GD32_SDTCFG_RCD_SHIFT)

/* SDCMD bit fields */

#define GD32_SDCMD_CMD_SHIFT           (0)         /* Bits 0-2: command */
#define GD32_SDCMD_CMD_MASK            (7 << GD32_SDCMD_CMD_SHIFT)
#define GD32_SDCMD_CMD_NORMAL          (0)         /* normal operation */
#define GD32_SDCMD_CMD_CKE             (1)         /* clock enable */
#define GD32_SDCMD_CMD_PRECHARGE       (2)         /* precharge all */
#define GD32_SDCMD_CMD_AUTOREFRESH     (3)         /* auto refresh */
#define GD32_SDCMD_CMD_LOADMODE        (4)         /* load mode register */
#define GD32_SDCMD_CMD_SELFREFRESH     (5)         /* self refresh */
#define GD32_SDCMD_CMD_POWERDOWN       (6)         /* power-down entry */

#define GD32_SDCMD_DS1                 (1 << 3)    /* Bit 3: select device1 */
#define GD32_SDCMD_DS0                 (1 << 4)    /* Bit 4: select device0 */
#define GD32_SDCMD_NARF_SHIFT          (5)         /* Bits 5-8: number of auto-refresh */
#define GD32_SDCMD_NARF_MASK           (15 << GD32_SDCMD_NARF_SHIFT)
#define GD32_SDCMD_MRC_SHIFT           (9)         /* Bits 9-21: mode register content */
#define GD32_SDCMD_MRC_MASK            (0x1fff << GD32_SDCMD_MRC_SHIFT)

/* SDSTAT bit fields */

#define GD32_SDSTAT_REIF               (1 << 0)    /* Bit 0: refresh error interrupt flag */
#define GD32_SDSTAT_STA0_SHIFT         (1)         /* Bits 1-2: device0 status */
#define GD32_SDSTAT_STA1_SHIFT         (3)         /* Bits 3-4: device1 status */
#define GD32_SDSTAT_NRDY               (1 << 5)    /* Bit 5: not ready status */

/* SDRSCTL bit fields */

#define GD32_SDRSCTL_RSEN              (1 << 0)    /* Bit 0: read sample enable */
#define GD32_SDRSCTL_SSCR              (1 << 1)    /* Bit 1: select sample cycle */
#define GD32_SDRSCTL_SDSC_SHIFT        (4)         /* Bits 4-7: delayed sample clock select */
#define GD32_SDRSCTL_SDSC_MASK         (15 << GD32_SDRSCTL_SDSC_SHIFT)

#endif /* __ARCH_ARM_SRC_GD32H7XX_HARDWARE_GD32H7XX_EXMC_H */
