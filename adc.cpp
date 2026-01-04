/**
 ****************************************************************************************************
 * @file        adc.cpp
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-12-01
 * @brief       ADC 驱动代码
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

#include "adc.h"

/**
* @brief       获取ADC值函数
* @param       adc_pin：adc引脚
* @retval      获取到的ADC值
*/
uint16_t adc_get(uint8_t adc_pin) 
{
    return analogRead(adc_pin);   /* 返回ADC值 */
}


