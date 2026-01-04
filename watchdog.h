/**
 ****************************************************************************************************
 * @file        watchdog.h
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
 * V1.0 20230809
 * 第一次发布
 *
 ****************************************************************************************************
 */

#ifndef __WATCHDOG_H
#define __WATCHDOG_H

#include "Arduino.h"
#include "esp_system.h"

extern hw_timer_t *wdg_timer;

/* 看门狗定时器定义 */
#define WDG_TIMx       1                    /* 模拟看门狗用到的定时器 */
#define WDG_ISR        tim1_ISR             /* 定时器中断服务函数 */

/* 函数声明 */
void wdg_init(uint32_t arr, uint16_t psc);  /* 看门狗初始化函数 */
void WDG_ISR(void);                         /* 看门狗定时器中断回调函数 */

#endif
