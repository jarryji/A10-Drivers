/*
 * this driver based on ---->>>
 * w1-sun5i - W1 master driver for sun5i platform
 *
 * Copyright (C) 2013 Harry Hornbacher <h.hornbacher@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 */

#define DRIVER_AUTHOR   "Harry Hornbacher <h.hornbacher@gmail.com>"
#define DRIVER_DESC     "W1 driver for sun4i platform"
#define DRIVER_NAME     "w1-sun4i"
#define DRV_VERSION     "0.0.1"

struct w1_sun4i_platform_data {
    unsigned gpio_handler;
    script_gpio_set_t info;
};

static int w1_sun4i_remove_driver(struct platform_device *pdev);
static int w1_sun4i_probe_driver(struct platform_device *pdev);


static void w1_sun4i_write_bit(void *data, u8 bit);
static u8 w1_sun4i_read_bit(void *data);
