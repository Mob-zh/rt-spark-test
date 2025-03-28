#include <rtthread.h>
#include <rtdevice.h>
#include <rtdbg.h>

#define THREAD_PRIORITY         25      // 线程优先级
#define THREAD_STACK_SIZE       512     // 线程堆栈大小
#define THREAD_TIMESLICE        5       // 线程时间片

#define ADC_DEV_NAME        "adc1"      /* ADC 设备名称 */
#define ADC_DEV_CHANNEL     0           /* ADC 通道 */
#define REFER_VOLTAGE       330         /* 参考电压 3.3V,数据精度乘以100保留2位小数*/
#define CONVERT_BITS        (1 << 12)   /* 转换位数为12位 */

static rt_thread_t tid1 = RT_NULL;
static rt_adc_device_t adc_dev;

static void adc_entry(void *parameter)
{
    rt_uint32_t value, vol;
    while (1)
    {
        /* 读取采样值 */
        value = rt_adc_read(adc_dev, ADC_DEV_CHANNEL);
        rt_kprintf("the value is :%d \n", value);
        /* 转换为对应电压值 */
        vol = value * REFER_VOLTAGE / CONVERT_BITS;
        rt_kprintf("the voltage is :%d.%02d \n", vol / 100, vol % 100);
        rt_thread_mdelay(500);
    }
}


/* 线程示例 */
int thread_adc(void)
{
    rt_err_t ret = RT_EOK;
    /* 查找设备 */
    adc_dev = (rt_adc_device_t)rt_device_find(ADC_DEV_NAME);
    if (adc_dev == RT_NULL)
    {
        rt_kprintf("adc sample run failed! can't find %s device!\n", ADC_DEV_NAME);
        return RT_ERROR;
    }

    /* 使能设备 */
    ret=rt_adc_enable(adc_dev, ADC_DEV_CHANNEL);
    if (ret != RT_EOK)
    {
        rt_kprintf("adc enable failed ");
        return RT_ERROR;
    }
    tid1 = rt_thread_create("adc_vol_sample",
                            adc_entry, RT_NULL,
                            THREAD_STACK_SIZE,
                            THREAD_PRIORITY, THREAD_TIMESLICE);

    /* 如果获得线程控制块，启动这个线程 */
    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);
    return 0;
}


/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(thread_adc, adc voltage convert sample);