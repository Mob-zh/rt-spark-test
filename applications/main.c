/*
 * Copyright (c) 2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-07-06     Supperthomas first version
 * 2023-12-03     Meco Man     support nano version
 */

#include <board.h>
#include <rtthread.h>
#include <drv_gpio.h>
#ifndef RT_USING_NANO
#include <rtdevice.h>
#include <hello.h>
#endif /* RT_USING_NANO */

#define GPIO_LED_R    GET_PIN(F, 12)

int main(void)
{
		hello_world();
    while (1)
    {
        rt_thread_mdelay(500);
        rt_thread_mdelay(500);
    }
}
