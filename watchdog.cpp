/**
 ****************************************************************************************************
 * @file        watchdog.cpp
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-12-01
 * @brief       WDG 驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 ESP32S3 开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 * 修改说明
 * V1.0 20231201
 * 第一次发布
 *
 ****************************************************************************************************
 */

#include "watchdog.h"

hw_timer_t *wdg_timer = NULL;

/**
 * @brief       初始化看门狗
 * @note
 *              定时器的时钟来自APB,而APB为80M
 *              所以定时器时钟 = (80/psc)Mhz, 单位时间为 1 / (80 / psc) = x us
 *              定时器溢出时间计算方法: Tout = ((arr + 1) * (psc + 1)) / Ft us
 *              Ft=定时器工作频率,单位:Mhz
 *
 * @param       arr: 自动重装值
 * @param       psc: 时钟预分频数
 * @retval      无
 */
void wdg_init(uint32_t arr, uint16_t psc)
{
    wdg_timer = timerBegin(WDG_TIMx, psc, true);         /* 初始化定时器1 */

    timerAlarmWrite(wdg_timer, arr, true);               /* 设置中断时间 */

    timerAttachInterrupt(wdg_timer, &WDG_ISR, true);     /* 配置定时器中断回调函数 */

    timerAlarmEnable(wdg_timer);                         /* 使能定时器中断 */
}

/**
 * @brief       看门狗定时器中断回调函数
 * @param       无
 * @retval      无
 */
void WDG_ISR(void)
{
    ets_printf("reboot\n");
    esp_restart();
}
