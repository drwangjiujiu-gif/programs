/**
 ****************************************************************************************************
 * @file        ds18b20.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-12-01
 * @brief       DS18B20 驱动代码
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

#ifndef __DS18B20_H
#define __DS18B20_H

#include "Arduino.h"
#include "esp_system.h"

/* 引脚定义 */
#define DS18B20_DQ_PIN      GPIO_NUM_0

/* 宏函数 */
#define DS18B20_DQ_OUT(x)   gpio_set_level(DS18B20_DQ_PIN, x)
#define DS18B20_DQ_IN       gpio_get_level(DS18B20_DQ_PIN)

#define DS18B20_MODE_IN     gpio_set_direction(DS18B20_DQ_PIN, GPIO_MODE_INPUT)
#define DS18B20_MODE_OUT    gpio_set_direction(DS18B20_DQ_PIN, GPIO_MODE_OUTPUT)

/* 函数声明 */
uint8_t ds18b20_init(void);             /* DS18B20初始化 */
uint8_t ds18b20_check(void);            /* 检测是否存在DS18B20 */
short ds18b20_get_temperature(void);    /* 获取温度 */

#endif
