/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-07-29     KyleChan          first version
 */

#include <drv_gpio.h>

#ifdef RT_USING_PIN

#define DBG_TAG              "drv.gpio"
#ifdef DRV_DEBUG
    #define DBG_LVL               DBG_LOG
#else
    #define DBG_LVL               DBG_INFO
#endif /* DRV_DEBUG */

#ifdef R_ICU_H
static rt_base_t ra_pin_get_irqx(rt_uint32_t pin)
{
    switch (pin)
    {
    case BSP_IO_PORT_04_PIN_00:
    case BSP_IO_PORT_02_PIN_06:
    case BSP_IO_PORT_01_PIN_05:
        return 0;

    case BSP_IO_PORT_02_PIN_05:
    case BSP_IO_PORT_01_PIN_01:
    case BSP_IO_PORT_01_PIN_04:
        return 1;

    case BSP_IO_PORT_02_PIN_03:
    case BSP_IO_PORT_01_PIN_00:
    case BSP_IO_PORT_02_PIN_13:
        return 2;

    case BSP_IO_PORT_02_PIN_02:
    case BSP_IO_PORT_01_PIN_10:
    case BSP_IO_PORT_02_PIN_12:
        return 3;

    case BSP_IO_PORT_04_PIN_02:
    case BSP_IO_PORT_01_PIN_11:
    case BSP_IO_PORT_04_PIN_11:
        return 4;

    case BSP_IO_PORT_04_PIN_01:
    case BSP_IO_PORT_03_PIN_02:
    case BSP_IO_PORT_04_PIN_10:
        return 5;

    case BSP_IO_PORT_03_PIN_01:
    case BSP_IO_PORT_00_PIN_00:
    case BSP_IO_PORT_04_PIN_09:
        return 6;

    case BSP_IO_PORT_00_PIN_01:
    case BSP_IO_PORT_04_PIN_08:
        return 7;

    case BSP_IO_PORT_00_PIN_02:
    case BSP_IO_PORT_03_PIN_05:
    case BSP_IO_PORT_04_PIN_15:
        return 8;

    case BSP_IO_PORT_00_PIN_04:
    case BSP_IO_PORT_03_PIN_04:
    case BSP_IO_PORT_04_PIN_14:
        return 9;

    case BSP_IO_PORT_00_PIN_05:
    case BSP_IO_PORT_07_PIN_09:
        return 10;

    case BSP_IO_PORT_05_PIN_01:
    case BSP_IO_PORT_00_PIN_06:
    case BSP_IO_PORT_07_PIN_08:
        return 11;

    case BSP_IO_PORT_05_PIN_02:
    case BSP_IO_PORT_00_PIN_08:
        return 12;

    case BSP_IO_PORT_00_PIN_15:
    case BSP_IO_PORT_00_PIN_09:
        return 13;

    case BSP_IO_PORT_04_PIN_03:
    case BSP_IO_PORT_05_PIN_12:
    case BSP_IO_PORT_05_PIN_05:
        return 14;

    case BSP_IO_PORT_04_PIN_04:
    case BSP_IO_PORT_05_PIN_11:
    case BSP_IO_PORT_05_PIN_06:
        return 15;

    default  :
        return -1;
    }
}

static struct rt_pin_irq_hdr pin_irq_hdr_tab[] =
{
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
    {-1, 0, RT_NULL, RT_NULL},
};

#define RA_IRQ_MAX  16
struct ra_pin_irq_map pin_irq_map[RA_IRQ_MAX] = {0};

static void ra_pin_map_init(void)
{
#ifdef VECTOR_NUMBER_ICU_IRQ0
    pin_irq_map[0].irq_ctrl = &g_external_irq0_ctrl;
    pin_irq_map[0].irq_cfg = &g_external_irq0_cfg;
#endif
#ifdef VECTOR_NUMBER_ICU_IRQ1
    pin_irq_map[1].irq_ctrl = &g_external_irq1_ctrl;
    pin_irq_map[1].irq_cfg = &g_external_irq1_cfg;
#endif
#ifdef VECTOR_NUMBER_ICU_IRQ2
    pin_irq_map[2].irq_ctrl = &g_external_irq2_ctrl;
    pin_irq_map[2].irq_cfg = &g_external_irq2_cfg;
#endif
#ifdef VECTOR_NUMBER_ICU_IRQ3
    pin_irq_map[3].irq_ctrl = &g_external_irq3_ctrl;
    pin_irq_map[3].irq_cfg = &g_external_irq3_cfg;
#endif
#ifdef VECTOR_NUMBER_ICU_IRQ4
    pin_irq_map[4].irq_ctrl = &g_external_irq4_ctrl;
    pin_irq_map[4].irq_cfg = &g_external_irq4_cfg;
#endif
#ifdef VECTOR_NUMBER_ICU_IRQ5
    pin_irq_map[5].irq_ctrl = &g_external_irq5_ctrl;
    pin_irq_map[5].irq_cfg = &g_external_irq5_cfg;
#endif
#ifdef VECTOR_NUMBER_ICU_IRQ6
    pin_irq_map[6].irq_ctrl = &g_external_irq6_ctrl;
    pin_irq_map[6].irq_cfg = &g_external_irq6_cfg;
#endif
#ifdef VECTOR_NUMBER_ICU_IRQ7
    pin_irq_map[7].irq_ctrl = &g_external_irq7_ctrl;
    pin_irq_map[7].irq_cfg = &g_external_irq7_cfg;
#endif
#ifdef VECTOR_NUMBER_ICU_IRQ8
    pin_irq_map[8].irq_ctrl = &g_external_irq8_ctrl;
    pin_irq_map[8].irq_cfg = &g_external_irq8_cfg;
#endif
#ifdef VECTOR_NUMBER_ICU_IRQ9
    pin_irq_map[9].irq_ctrl = &g_external_irq9_ctrl;
    pin_irq_map[9].irq_cfg = &g_external_irq9_cfg;
#endif
#ifdef VECTOR_NUMBER_ICU_IRQ10
    pin_irq_map[10].irq_ctrl = &g_external_irq10_ctrl;
    pin_irq_map[10].irq_cfg = &g_external_irq10_cfg;
#endif
#ifdef VECTOR_NUMBER_ICU_IRQ11
    pin_irq_map[11].irq_ctrl = &g_external_irq11_ctrl;
    pin_irq_map[11].irq_cfg = &g_external_irq11_cfg;
#endif
#ifdef VECTOR_NUMBER_ICU_IRQ12
    pin_irq_map[12].irq_ctrl = &g_external_irq12_ctrl;
    pin_irq_map[12].irq_cfg = &g_external_irq12_cfg;
#endif
#ifdef VECTOR_NUMBER_ICU_IRQ13
    pin_irq_map[13].irq_ctrl = &g_external_irq13_ctrl;
    pin_irq_map[13].irq_cfg = &g_external_irq13_cfg;
#endif
#ifdef VECTOR_NUMBER_ICU_IRQ14
    pin_irq_map[14].irq_ctrl = &g_external_irq14_ctrl;
    pin_irq_map[14].irq_cfg = &g_external_irq14_cfg;
#endif
#ifdef VECTOR_NUMBER_ICU_IRQ15
    pin_irq_map[15].irq_ctrl = &g_external_irq15_ctrl;
    pin_irq_map[15].irq_cfg = &g_external_irq15_cfg;
#endif
}
#endif  /* R_ICU_H */

static void ra_pin_mode(rt_device_t dev, rt_base_t pin, rt_base_t mode)
{
    fsp_err_t err;
    /* Initialize the IOPORT module and configure the pins */
    err = R_IOPORT_Open(&g_ioport_ctrl, &g_bsp_pin_cfg);

    if (err != FSP_SUCCESS)
    {
        LOG_E("GPIO open failed");
        return;
    }

    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        err = R_IOPORT_PinCfg(&g_ioport_ctrl, pin, BSP_IO_DIRECTION_OUTPUT);
        if (err != FSP_SUCCESS)
        {
            LOG_E("PIN_MODE_OUTPUT configuration failed");
            return;
        }
        break;

    case PIN_MODE_INPUT:
        err = R_IOPORT_PinCfg(&g_ioport_ctrl, pin, BSP_IO_DIRECTION_INPUT);
        if (err != FSP_SUCCESS)
        {
            LOG_E("PIN_MODE_INPUT configuration failed");
            return;
        }
        break;

    case PIN_MODE_OUTPUT_OD:
        err = R_IOPORT_PinCfg(&g_ioport_ctrl, pin, IOPORT_CFG_NMOS_ENABLE);
        if (err != FSP_SUCCESS)
        {
            LOG_E("PIN_MODE_OUTPUT_OD configuration failed");
            return;
        }
        break;
    }
}

static void ra_pin_write(rt_device_t dev, rt_base_t pin, rt_base_t value)
{
    bsp_io_level_t level = BSP_IO_LEVEL_HIGH;

    if (value != level)
    {
        level = BSP_IO_LEVEL_LOW;
    }

    R_BSP_PinAccessEnable();
    R_BSP_PinWrite(pin, level);
    R_BSP_PinAccessDisable();
}

static int ra_pin_read(rt_device_t dev, rt_base_t pin)
{
    if ((pin > RA_MAX_PIN_VALUE) || (pin < RA_MIN_PIN_VALUE))
    {
        LOG_E("GPIO pin value is illegal");
        return -RT_ERROR;
    }
    return R_BSP_PinRead(pin);
}

static rt_err_t ra_pin_irq_enable(struct rt_device *device, rt_base_t pin, rt_uint32_t enabled)
{
#ifdef R_ICU_H
    rt_err_t err;
    rt_int32_t irqx = ra_pin_get_irqx(pin);
    if (PIN_IRQ_ENABLE == enabled)
    {
        if (0 <= irqx && irqx < sizeof(pin_irq_map) / sizeof(pin_irq_map[0]))
        {
            err = R_ICU_ExternalIrqOpen((external_irq_ctrl_t *const)pin_irq_map[irqx].irq_ctrl,
                                        (external_irq_cfg_t const * const)pin_irq_map[irqx].irq_cfg);
            /* Handle error */
            if (FSP_SUCCESS != err)
            {
                /* ICU Open failure message */
                LOG_E("\r\n**R_ICU_ExternalIrqOpen API FAILED**\r\n");
                return -RT_ERROR;
            }

            err = R_ICU_ExternalIrqEnable((external_irq_ctrl_t *const)pin_irq_map[irqx].irq_ctrl);
            /* Handle error */
            if (FSP_SUCCESS != err)
            {
                /* ICU Enable failure message */
                LOG_E("\r\n**R_ICU_ExternalIrqEnable API FAILED**\r\n");
                return -RT_ERROR;
            }
        }
    }
    else if (PIN_IRQ_DISABLE == enabled)
    {
        err = R_ICU_ExternalIrqDisable((external_irq_ctrl_t *const)pin_irq_map[irqx].irq_ctrl);
        if (FSP_SUCCESS != err)
        {
            /* ICU Disable failure message */
            LOG_E("\r\n**R_ICU_ExternalIrqDisable API FAILED**\r\n");
            return -RT_ERROR;
        }
        err = R_ICU_ExternalIrqClose((external_irq_ctrl_t *const)pin_irq_map[irqx].irq_ctrl);
        if (FSP_SUCCESS != err)
        {
            /* ICU Close failure message */
            LOG_E("\r\n**R_ICU_ExternalIrqClose API FAILED**\r\n");
            return -RT_ERROR;
        }
    }
    return RT_EOK;
#else
    return -RT_ERROR;
#endif
}

static rt_err_t ra_pin_attach_irq(struct rt_device *device, rt_int32_t pin,
                                  rt_uint32_t mode, void (*hdr)(void *args), void *args)
{
#ifdef R_ICU_H
    rt_int32_t irqx = ra_pin_get_irqx(pin);
    if (0 <= irqx && irqx < (sizeof(pin_irq_map) / sizeof(pin_irq_map[0])))
    {
        int level = rt_hw_interrupt_disable();
        if (pin_irq_hdr_tab[irqx].pin == irqx &&
                pin_irq_hdr_tab[irqx].hdr == hdr &&
                pin_irq_hdr_tab[irqx].mode == mode &&
                pin_irq_hdr_tab[irqx].args == args)
        {
            rt_hw_interrupt_enable(level);
            return RT_EOK;
        }
        if (pin_irq_hdr_tab[irqx].pin != -1)
        {
            rt_hw_interrupt_enable(level);
            return RT_EBUSY;
        }
        pin_irq_hdr_tab[irqx].pin = irqx;
        pin_irq_hdr_tab[irqx].hdr = hdr;
        pin_irq_hdr_tab[irqx].mode = mode;
        pin_irq_hdr_tab[irqx].args = args;
        rt_hw_interrupt_enable(level);
    }
    else return -RT_ERROR;
    return RT_EOK;
#else
    return -RT_ERROR;
#endif
}

static rt_err_t ra_pin_dettach_irq(struct rt_device *device, rt_int32_t pin)
{
#ifdef R_ICU_H
    rt_int32_t irqx = ra_pin_get_irqx(pin);
    if (0 <= irqx && irqx < sizeof(pin_irq_map) / sizeof(pin_irq_map[0]))
    {
        int level = rt_hw_interrupt_disable();
        if (pin_irq_hdr_tab[irqx].pin == -1)
        {
            rt_hw_interrupt_enable(level);
            return RT_EOK;
        }
        pin_irq_hdr_tab[irqx].pin = -1;
        pin_irq_hdr_tab[irqx].hdr = RT_NULL;
        pin_irq_hdr_tab[irqx].mode = 0;
        pin_irq_hdr_tab[irqx].args = RT_NULL;
        rt_hw_interrupt_enable(level);
    }
    else
    {
        return -RT_ERROR;
    }
    return RT_EOK;
#else
    return -RT_ERROR;
#endif
}

static rt_base_t ra_pin_get(const char *name)
{
    int pin_number = -1, port = -1, pin = -1;
    if (rt_strlen(name) != 4)
        return -1;
    if ((name[0] == 'P') || (name[0] == 'p'))
    {
        if ('0' <= (int)name[1] && (int)name[1] <= '9')
        {
            port = ((int)name[1] - 48) * 16 * 16;
            if ('0' <= (int)name[2] && (int)name[2] <= '9')
            {
                if ('0' <= (int)name[3] && (int)name[3] <= '9')
                {
                    pin = ((int)name[2] - 48) * 10;
                    pin += (int)name[3] - 48;
                    pin_number = port + pin;
                }
                else return -1;
            }
            else return -1;
        }
        else return -1;
    }
    return pin_number;
}

const static struct rt_pin_ops _ra_pin_ops =
{
    .pin_mode       = ra_pin_mode,
    .pin_write      = ra_pin_write,
    .pin_read       = ra_pin_read,
    .pin_attach_irq = ra_pin_attach_irq,
    .pin_detach_irq = ra_pin_dettach_irq,
    .pin_irq_enable = ra_pin_irq_enable,
    .pin_get        = ra_pin_get,
};

int rt_hw_pin_init(void)
{
#ifdef R_ICU_H
    ra_pin_map_init();
#endif
    return rt_device_pin_register("pin", &_ra_pin_ops, RT_NULL);
}

#ifdef R_ICU_H
void irq0_callback(external_irq_callback_args_t *p_args)
{
    rt_interrupt_enter();
    if (0 == pin_irq_hdr_tab[0].pin)
    {
        pin_irq_hdr_tab[0].hdr(pin_irq_hdr_tab[0].args);
    }
    rt_interrupt_leave();
};

void irq1_callback(external_irq_callback_args_t *p_args)
{
    rt_interrupt_enter();
    if (1 == pin_irq_hdr_tab[1].pin)
    {
        pin_irq_hdr_tab[1].hdr(pin_irq_hdr_tab[1].args);
    }
    rt_interrupt_leave();
};

void irq2_callback(external_irq_callback_args_t *p_args)
{
    rt_interrupt_enter();
    if (2 == pin_irq_hdr_tab[2].pin)
    {
        pin_irq_hdr_tab[2].hdr(pin_irq_hdr_tab[2].args);
    }
    rt_interrupt_leave();
};

void irq3_callback(external_irq_callback_args_t *p_args)
{
    rt_interrupt_enter();
    if (3 == pin_irq_hdr_tab[3].pin)
    {
        pin_irq_hdr_tab[3].hdr(pin_irq_hdr_tab[3].args);
    }
    rt_interrupt_leave();
};

void irq4_callback(external_irq_callback_args_t *p_args)
{
    rt_interrupt_enter();
    if (4 == pin_irq_hdr_tab[4].pin)
    {
        pin_irq_hdr_tab[4].hdr(pin_irq_hdr_tab[4].args);
    }
    rt_interrupt_leave();
};

void irq5_callback(external_irq_callback_args_t *p_args)
{
    rt_interrupt_enter();
    if (5 == pin_irq_hdr_tab[5].pin)
    {
        pin_irq_hdr_tab[5].hdr(pin_irq_hdr_tab[5].args);
    }
    rt_interrupt_leave();
};

void irq6_callback(external_irq_callback_args_t *p_args)
{
    rt_interrupt_enter();
    if (6 == pin_irq_hdr_tab[6].pin)
    {
        pin_irq_hdr_tab[6].hdr(pin_irq_hdr_tab[6].args);
    }
    rt_interrupt_leave();
};

void irq7_callback(external_irq_callback_args_t *p_args)
{
    rt_interrupt_enter();
    if (7 == pin_irq_hdr_tab[7].pin)
    {
        pin_irq_hdr_tab[7].hdr(pin_irq_hdr_tab[7].args);
    }
    rt_interrupt_leave();
};

void irq8_callback(external_irq_callback_args_t *p_args)
{
    rt_interrupt_enter();
    if (8 == pin_irq_hdr_tab[8].pin)
    {
        pin_irq_hdr_tab[8].hdr(pin_irq_hdr_tab[8].args);
    }
    rt_interrupt_leave();
};

void irq9_callback(external_irq_callback_args_t *p_args)
{
    rt_interrupt_enter();
    if (9 == pin_irq_hdr_tab[9].pin)
    {
        pin_irq_hdr_tab[9].hdr(pin_irq_hdr_tab[9].args);
    }
    rt_interrupt_leave();
};

void irq10_callback(external_irq_callback_args_t *p_args)
{
    rt_interrupt_enter();
    if (10 == pin_irq_hdr_tab[10].pin)
    {
        pin_irq_hdr_tab[10].hdr(pin_irq_hdr_tab[10].args);
    }
    rt_interrupt_leave();
};

void irq11_callback(external_irq_callback_args_t *p_args)
{
    rt_interrupt_enter();
    if (11 == pin_irq_hdr_tab[11].pin)
    {
        pin_irq_hdr_tab[11].hdr(pin_irq_hdr_tab[11].args);
    }
    rt_interrupt_leave();
};

void irq12_callback(external_irq_callback_args_t *p_args)
{
    rt_interrupt_enter();
    if (12 == pin_irq_hdr_tab[12].pin)
    {
        pin_irq_hdr_tab[12].hdr(pin_irq_hdr_tab[12].args);
    }
    rt_interrupt_leave();
};

void irq13_callback(external_irq_callback_args_t *p_args)
{
    rt_interrupt_enter();
    if (13 == pin_irq_hdr_tab[13].pin)
    {
        pin_irq_hdr_tab[13].hdr(pin_irq_hdr_tab[13].args);
    }
    rt_interrupt_leave();
};

void irq14_callback(external_irq_callback_args_t *p_args)
{
    rt_interrupt_enter();
    if (14 == pin_irq_hdr_tab[14].pin)
    {
        pin_irq_hdr_tab[14].hdr(pin_irq_hdr_tab[14].args);
    }
    rt_interrupt_leave();
};

void irq15_callback(external_irq_callback_args_t *p_args)
{
    rt_interrupt_enter();
    if (15 == pin_irq_hdr_tab[15].pin)
    {
        pin_irq_hdr_tab[15].hdr(pin_irq_hdr_tab[15].args);
    }
    rt_interrupt_leave();
};
#endif /* R_ICU_H */

#endif /* RT_USING_PIN */
