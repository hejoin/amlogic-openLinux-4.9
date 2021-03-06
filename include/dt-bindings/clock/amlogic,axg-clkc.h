/*
 * include/dt-bindings/clock/gxl-clkc.h
 *
 * Copyright (C) 2017 Amlogic, Inc. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 */

#ifndef __GX_CLKC_H
#define __GX_CLKC_H

/*
 * CLKID index values
 */

#define CLKID_SYS_PLL       0
#define CLKID_FIXED_PLL		  1
#define CLKID_FCLK_DIV2     2
#define CLKID_FCLK_DIV3     3
#define CLKID_FCLK_DIV4     4
#define CLKID_FCLK_DIV5		  5
#define CLKID_FCLK_DIV7		  6
#define CLKID_GP0_PLL       7
#define CLKID_HIFI_PLL      8
#define CLKID_MPEG_SEL		  9
#define CLKID_MPEG_DIV		  10
#define CLKID_CLK81         11
#define CLKID_MPLL0		  12
#define CLKID_MPLL1		  13
#define CLKID_MPLL2     14
#define CLKID_MPLL3		  15
#define CLKID_CPU_FCLK_P00	16
#define CLKID_CPU_FCLK_P01	17
#define CLKID_CPU_FCLK_P0	18
#define CLKID_CPU_FCLK_P10	19
#define CLKID_CPU_FCLK_P11	20
#define CLKID_CPU_FCLK_P1	21
#define CLKID_CPU_FCLK_P	22
#define CLKID_CPU_CLK		23
#define CLKID_PCIE_PLL 24
#define CLKID_PCIE_MUX 25
#define CLKID_PCIE_REF 26
#define CLKID_PCIE_INPUT_GATE 27

/*HHI_GCLK_MPEG0: 0x50*/
#define GATE_BASE0    25
#define CLKID_DDR    (GATE_BASE0 + 0)
#define CLKID_AUDIO_LOCKER	(GATE_BASE0 + 1)
#define CLKID_MIPI_DSI_HOST		  (GATE_BASE0 + 2)
#define CLKID_ISA		  (GATE_BASE0 + 3)
#define CLKID_PL301		  (GATE_BASE0 + 4)
#define CLKID_PERIPHS		 (GATE_BASE0 + 5)
#define CLKID_SPICC0		  (GATE_BASE0 + 6)
#define CLKID_I2C         (GATE_BASE0 + 7)
#define CLKID_RNG0		  (GATE_BASE0 + 8)
#define CLKID_UART0		  (GATE_BASE0 + 9)
#define CLKID_MIPI_DSI_PHY		  (GATE_BASE0 + 10)
#define CLKID_SPICC1		  (GATE_BASE0 + 11)
#define CLKID_PCIE_A	  (GATE_BASE0 + 12)
#define CLKID_PCIE_B		  (GATE_BASE0 + 13)
#define CLKID_HIU_REG		  (GATE_BASE0 + 14)
#define CLKID_ASSIST_MISC	  (GATE_BASE0 + 15)
#define CLKID_SD_EMMC_B	(GATE_BASE0 + 16)
#define CLKID_SD_EMMC_C	(GATE_BASE0 + 17)
#define CLKID_DMA	(GATE_BASE0 + 18)
#define CLKID_SPI (GATE_BASE0 + 19)
/*HHI_GCLK_MPEG1: 0x51*/
#define GATE_BASE1    (GATE_BASE0 + 20) /*28+20*/
#define CLKID_AUDIO	(GATE_BASE1 + 0)
#define CLKID_ETH_CORE		  (GATE_BASE1 + 1)
#define CLKID_UART1		  (GATE_BASE1 + 2)
#define CLKID_G2D		  (GATE_BASE1 + 3)
#define CLKID_USB0    (GATE_BASE1 + 4)
#define CLKID_USB1    (GATE_BASE1 + 5)
#define CLKID_RESET		  (GATE_BASE1 + 6)
#define CLKID_USB_GENERAL      (GATE_BASE1 + 7)
#define CLKID_AHB_ARB0		  (GATE_BASE1 + 8)
#define CLKID_EFUSE		  (GATE_BASE1 + 9)
#define CLKID_BOOT_ROM		  (GATE_BASE1 + 10)
/*HHI_GCLK_MPEG2: 0x52*/
#define GATE_BASE2    (GATE_BASE1 + 11)  /*28+20+11*/
#define CLKID_AHB_DATA_BUS	  (GATE_BASE2 + 0)
#define CLKID_AHB_CTRL_BUS	  (GATE_BASE2 + 1)
#define CLKID_USB1_TO_DDR (GATE_BASE2 + 2)
#define CLKID_USB0_TO_DDR (GATE_BASE2 + 3)
#define CLKID_MMC_PCLK		  (GATE_BASE2 + 4)
#define CLKID_VPU_INTR		  (GATE_BASE2 + 5)
#define CLKID_SEC_AHB_AHB3_BRIDGE (GATE_BASE2 + 6)
#define CLKID_GIC		  (GATE_BASE2 + 7)

#define AO_BASE (GATE_BASE2 + 8) /*28+20+11+8*/
#define CLKID_AO_MEDIA_CPU	  (AO_BASE + 0)
#define CLKID_AO_AHB_SRAM	  (AO_BASE + 1)
#define CLKID_AO_AHB_BUS	  (AO_BASE + 2)
#define CLKID_AO_IFACE		  (AO_BASE + 3)
#define CLKID_AO_I2C	(AO_BASE + 4)

#define OTHER_BASE (AO_BASE + 5) /*28+20+11+8+5=72*/
#define CLKID_SD_EMMC_B_P0_MUX (OTHER_BASE + 0)
#define CLKID_SD_EMMC_B_P0_DIV (OTHER_BASE + 1)
#define CLKID_SD_EMMC_B_P0_GATE (OTHER_BASE + 2)
#define CLKID_SD_EMMC_B_P0_COMP (OTHER_BASE + 3)
#define CLKID_SD_EMMC_C_P0_MUX (OTHER_BASE + 4)
#define CLKID_SD_EMMC_C_P0_DIV (OTHER_BASE + 5)
#define CLKID_SD_EMMC_C_P0_GATE (OTHER_BASE + 6)
#define CLKID_SD_EMMC_C_P0_COMP (OTHER_BASE + 7)
#define CLKID_SD_EMMC_B_MUX	 (OTHER_BASE + 8)
#define CLKID_SD_EMMC_B_DIV	 (OTHER_BASE + 9)
#define CLKID_SD_EMMC_B_GATE	 (OTHER_BASE + 10)
#define CLKID_SD_EMMC_B_COMP  (OTHER_BASE + 11)
#define CLKID_SD_EMMC_C_MUX	 (OTHER_BASE + 12)
#define CLKID_SD_EMMC_C_DIV	 (OTHER_BASE + 13)
#define CLKID_SD_EMMC_C_GATE	 (OTHER_BASE + 14)
#define CLKID_SD_EMMC_C_COMP  (OTHER_BASE + 15)

#define CLKID_MEDIA_BASE (OTHER_BASE + 16) /*28+20+11+8+5+16*/
#define CLKID_VPU_P0_MUX (CLKID_MEDIA_BASE + 0)
#define CLKID_VPU_P0_DIV (CLKID_MEDIA_BASE + 1)
#define CLKID_VPU_P0_GATE (CLKID_MEDIA_BASE + 2)
#define CLKID_VPU_P0_COMP (CLKID_MEDIA_BASE + 3)
#define CLKID_VPU_P1_MUX (CLKID_MEDIA_BASE + 4)
#define CLKID_VPU_P1_DIV (CLKID_MEDIA_BASE + 5)
#define CLKID_VPU_P1_GATE (CLKID_MEDIA_BASE + 6)
#define CLKID_VPU_P1_COMP (CLKID_MEDIA_BASE + 7)
#define CLKID_VPU_MUX (CLKID_MEDIA_BASE + 8)
#define CLKID_VAPB_P0_MUX (CLKID_MEDIA_BASE + 9)
#define CLKID_VAPB_P0_DIV (CLKID_MEDIA_BASE + 10)
#define CLKID_VAPB_P0_GATE (CLKID_MEDIA_BASE + 11)
#define CLKID_VAPB_P0_COMP (CLKID_MEDIA_BASE + 12)
#define CLKID_VAPB_P1_MUX (CLKID_MEDIA_BASE + 13)
#define CLKID_VAPB_P1_DIV (CLKID_MEDIA_BASE + 14)
#define CLKID_VAPB_P1_GATE (CLKID_MEDIA_BASE + 15)
#define CLKID_VAPB_P1_COMP (CLKID_MEDIA_BASE + 16)
#define CLKID_VAPB_MUX (CLKID_MEDIA_BASE + 17)
#define CLKID_GE2D_GATE (CLKID_MEDIA_BASE + 18)
#define CLKID_DSI_MEAS_MUX (CLKID_MEDIA_BASE + 19)
#define CLKID_DSI_MEAS_DIV (CLKID_MEDIA_BASE + 20)
#define CLKID_DSI_MEAS_GATE (CLKID_MEDIA_BASE + 21)
#define CLKID_DSI_MEAS_COMP (CLKID_MEDIA_BASE + 22)

#define CLKID_MISC_BASE (CLKID_MEDIA_BASE + 23) /*28+20+11+8+5+16+23 = 111*/
#define CLKID_SPICC_MUX (CLKID_MISC_BASE + 0)
#define CLKID_SPICC_DIV (CLKID_MISC_BASE + 1)
#define CLKID_SPICC_GATE (CLKID_MISC_BASE + 2)
#define CLKID_SPICC_COMP (CLKID_MISC_BASE + 3)

#define NR_CLKS				(OTHER_BASE + 43)

#endif /* __GX_CLKC_H */
