/*
 * this driver based on
 * modified by Jarry Ji for A10
 * w1-sun5i - W1 master driver for sun5i platform
 *
 * Copyright (C) 2013 Harry Hornbacher <h.hornbacher@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/platform_device.h>

#include <plat/sys_config.h>

#include "w1.h"
#include "w1_int.h"

#include "w1-sun4i.h"
#include "gpio_def.h"


struct w1_bus_master *w1_sun4i_master = NULL;
static struct platform_device *w1_sun4i_device = NULL;
static struct platform_driver w1_sun4i_driver = {
    .driver =
    {
        .name = DRIVER_NAME,
    },
    .remove = w1_sun4i_remove_driver
};

/* Init driver */
static int w1_sun4i_probe_driver(struct platform_device *pdev) {
    printk(KERN_INFO "%s()", __FUNCTION__);
    int err = 0;
    int w1_used = 0;
    struct w1_sun4i_platform_data *pdata = pdev->dev.platform_data;

    if (!pdata) {
        printk(KERN_INFO "%s: Invalid platform_data!\n", __FUNCTION__);
        return -ENXIO;
    }


    w1_sun4i_master = kzalloc(sizeof (struct w1_bus_master), GFP_KERNEL);
    if (!w1_sun4i_master) {
        printk(KERN_INFO "%s: Not enough memory!\n", __FUNCTION__);
        return -ENOMEM;
    }

    err = script_parser_fetch("w1_para", "w1_used", &w1_used, sizeof (w1_used) / sizeof (int));
    if (!w1_used || err) {
        printk(KERN_INFO "%s: w1-bus is not used in config\n", __FUNCTION__);
        kfree(w1_sun4i_master);
        return -EINVAL;
    }

    err = script_parser_fetch("w1_para", "w1_pin", (int *) &pdata->info, sizeof (script_gpio_set_t));
    if (err) {
        printk(KERN_INFO "%s: can not get \"w1_para\" \"w1_pin\" gpio handler, already used by others?", __FUNCTION__);
        kfree(w1_sun4i_master);
        return -EBUSY;
    }
    pdata->gpio_handler = gpio_request_ex("w1_para", "w1_pin");

    printk(KERN_INFO "%s: w1-bus GPIO pin: port:%d, portnum:%d\n", __FUNCTION__, pdata->info.port, pdata->info.port_num);

    w1_sun4i_master->data = pdata;
    w1_sun4i_master->read_bit = w1_sun4i_read_bit;
    w1_sun4i_master->write_bit = w1_sun4i_write_bit;

    err = w1_add_master_device(w1_sun4i_master);
    if (err) {
        printk(KERN_INFO "%s: can not add 1-wire master device!", __FUNCTION__);
        kfree(w1_sun4i_master);
        gpio_release(pdata->gpio_handler, 0);
        return -EBUSY;
    }


    return 0;
}

/*Cleanup*/
static int w1_sun4i_remove_driver(struct platform_device *pdev) {
    struct w1_sun4i_platform_data *pdata = pdev->dev.platform_data;
    w1_remove_master_device(w1_sun4i_master);
    kfree(w1_sun4i_master);
    gpio_release(pdata->gpio_handler, 0);
    kfree(w1_sun4i_device->dev.platform_data);
    platform_device_unregister(w1_sun4i_device);
    return 0;
}

static void w1_sun4i_write_bit(void *data, u8 bit) {
    struct w1_sun4i_platform_data *pdata = data;
    PIN_DIR(pdata->gpio_handler,1);
    PIN_SET(pdata->gpio_handler,bit);
}

static u8 w1_sun4i_read_bit(void *data) {
    struct w1_sun4i_platform_data *pdata = data;
    PIN_DIR(pdata->gpio_handler,0);
    return PIN_GET(pdata->gpio_handler);
}


static int __init w1_sun4i_init_driver(void) {
    w1_sun4i_device = platform_device_register_simple(DRIVER_NAME, 0, NULL, 0);
    w1_sun4i_device->dev.platform_data = kzalloc(sizeof (struct w1_sun4i_platform_data), GFP_KERNEL);
    return platform_driver_probe(&w1_sun4i_driver, w1_sun4i_probe_driver);
}

static void __exit w1_sun4i_exit_driver(void) {
    platform_driver_unregister(&w1_sun4i_driver);
}


MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_VERSION);

module_init(w1_sun4i_init_driver);
module_exit(w1_sun4i_exit_driver);
