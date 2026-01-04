/**
 ****************************************************************************************************
 * @file        oled.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-12-01
 * @brief       OLED 驱动代码
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

#ifndef __OLED_H
#define __OLED_H

#include "Arduino.h"

/* 引脚定义 */
#define OLED_SCL_PIN      4
#define OLED_SDA_PIN      5
#define OLED_D2_PIN       6
#define OLED_DC_PIN       38

#define OLED_ADDR         0X3C  /* 7位器件地址 */

#define OLED_RST(x)       xl9555_pin_set(OV_RESET, x ? IO_SET_HIGH : IO_SET_LOW)

/* 函数声明 */
void oled_init(void);           /* OLED模块初始化 */
void oled_show_demo(void);      /* OLED模块展示效果 */

#endif