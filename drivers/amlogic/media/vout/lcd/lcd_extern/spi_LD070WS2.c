/*
 * drivers/amlogic/media/vout/lcd/lcd_extern/spi_LD070WS2.c
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

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/jiffies.h>
#include <linux/miscdevice.h>
#include <linux/mutex.h>
#include <linux/mm.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/sysctl.h>
#include <linux/uaccess.h>
#include <linux/amlogic/media/vout/lcd/lcd_extern.h>
#include "lcd_extern.h"

static struct lcd_extern_config_s *ext_config;

#define LCD_EXTERN_NAME		"lcd_spi_LD070WS2"

#define SPI_DELAY		30 /* unit: us */

#define LCD_EXTERN_CMD_SIZE        4
static unsigned char init_on_table[] = {
	0x00, 0x00, 0x21, 0x00, /* reset */
	0x00, 0x00, 0xa5, 0x00, /* standby */
	0x00, 0x01, 0x30, 0x00, /* enable FRC/Dither */
	0x00, 0x02, 0x40, 0x00, /* enable normally black */
	0x00, 0x0e, 0x5f, 0x00, /* enable test mode1 */
	0x00, 0x0f, 0xa4, 0x00, /* enable test mode2 */
	0x00, 0x0d, 0x00, 0x00, /* enable SDRRS, enlarge OE width */
	0x00, 0x02, 0x43, 0x00, /* adjust charge sharing time */
	0x00, 0x0a, 0x28, 0x00, /* trigger bias reduction */
	0x00, 0x10, 0x41, 50,   /* adopt 2 line/1 dot */ /* delay 50ms */
	0x00, 0x00, 0xad, 0x00, /* display on */
	0xff, 0x00, 0x00, 0x00, /* ending flag */
};

static unsigned char init_off_table[] = {
	0x00, 0x00, 0xa5, 0x00, /* standby */
	0xff, 0x00, 0x00, 0x00, /* ending flag */
};

static void set_lcd_csb(unsigned int v)
{
	lcd_extern_gpio_set(ext_config->spi_cs, v);
	udelay(SPI_DELAY);
}

static void set_lcd_scl(unsigned int v)
{
	lcd_extern_gpio_set(ext_config->spi_clk, v);
	udelay(SPI_DELAY);
}

static void set_lcd_sda(unsigned int v)
{
	lcd_extern_gpio_set(ext_config->spi_data, v);
	udelay(SPI_DELAY);
}

static void spi_gpio_init(void)
{
	set_lcd_csb(1);
	set_lcd_scl(1);
	set_lcd_sda(1);
}

static void spi_gpio_off(void)
{
	set_lcd_sda(0);
	set_lcd_scl(0);
	set_lcd_csb(0);
}

static void spi_write_8(unsigned char addr, unsigned char data)
{
	int i;
	unsigned int sdata;

	sdata = (unsigned int)(addr & 0x3f);
	sdata <<= 10;
	sdata |= (data & 0xff);
	sdata &= ~(1<<9); /* write flag */

	set_lcd_csb(1);
	set_lcd_scl(1);
	set_lcd_sda(1);

	set_lcd_csb(0);
	for (i = 0; i < 16; i++) {
		set_lcd_scl(0);
		if (sdata & 0x8000)
			set_lcd_sda(1);
		else
			set_lcd_sda(0);
		sdata <<= 1;
		set_lcd_scl(1);
	}

	set_lcd_csb(1);
	set_lcd_scl(1);
	set_lcd_sda(1);
	udelay(SPI_DELAY);
}

static int lcd_extern_spi_write(unsigned char *buf, int len)
{
	if (len != 2) {
		EXTERR("%s: len %d error\n", __func__, len);
		return -1;
	}
	spi_write_8(buf[0], buf[1]);
	return 0;
}

static int lcd_extern_power_cmd(unsigned char *init_table)
{
	int i = 0, len;
	int ret = 0;

	len = ext_config->cmd_size;
	if (len < 1) {
		EXTERR("%s: cmd_size %d is invalid\n", __func__, len);
		return -1;
	}

	while (i <= LCD_EXTERN_INIT_TABLE_MAX) {
		if (init_table[i] == LCD_EXTERN_INIT_END) {
			break;
		} else if (init_table[i] == LCD_EXTERN_INIT_NONE) {
			/* do nothing, only for delay */
		} else if (init_table[i] == LCD_EXTERN_INIT_GPIO) {
			if (init_table[i+1] < LCD_GPIO_MAX) {
				lcd_extern_gpio_set(init_table[i+1],
					init_table[i+2]);
			}
		} else if (init_table[i] == LCD_EXTERN_INIT_CMD) {
			ret = lcd_extern_spi_write(&init_table[i+1], (len-2));
		} else {
			EXTERR("%s(%d: %s): power_type %d is invalid\n",
				__func__, ext_config->index,
				ext_config->name, ext_config->type);
		}
		if (init_table[i+len-1] > 0)
			mdelay(init_table[i+len-1]);
		i += len;
	}

	return ret;
}

static int lcd_extern_power_ctrl(int flag)
{
	int ret = 0;

	spi_gpio_init();
	if (flag)
		ret = lcd_extern_power_cmd(ext_config->table_init_on);
	else
		ret = lcd_extern_power_cmd(ext_config->table_init_off);
	mdelay(10);
	spi_gpio_off();

	EXTPR("%s(%d: %s): %d\n",
		__func__, ext_config->index, ext_config->name, flag);
	return ret;
}

static int lcd_extern_power_on(void)
{
	int ret;

	ret = lcd_extern_power_ctrl(1);
	return ret;
}

static int lcd_extern_power_off(void)
{
	int ret;

	ret = lcd_extern_power_ctrl(0);
	return ret;
}

static int lcd_extern_driver_update(struct aml_lcd_extern_driver_s *ext_drv)
{
	if (ext_drv == NULL) {
		EXTERR("%s driver is null\n", LCD_EXTERN_NAME);
		return -1;
	}

	if (ext_drv->config.table_init_loaded == 0) {
		ext_drv->config.table_init_on  = init_on_table;
		ext_drv->config.table_init_off = init_off_table;
	}
	ext_drv->power_on  = lcd_extern_power_on;
	ext_drv->power_off = lcd_extern_power_off;

	return 0;
}

int aml_lcd_extern_spi_LD070WS2_probe(struct aml_lcd_extern_driver_s *ext_drv)
{
	int ret = 0;

	ext_config = &ext_drv->config;
	ret = lcd_extern_driver_update(ext_drv);

	if (lcd_debug_print_flag)
		EXTPR("%s: %d\n", __func__, ret);
	return ret;
}
