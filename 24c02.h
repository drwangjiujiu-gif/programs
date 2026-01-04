/**
 ****************************************************************************************************
 * @file        24c02.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-12-01
 * @brief       24C02 驱动代码
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

#ifndef __24C02_H
#define __24C02_H

#include "Arduino.h"

/* 引脚定义 */
#define IIC_SCL     42
#define IIC_SDA     41

#define EEPROM_ADDR 0x50    /* 7位器件地址 */

/* 函数声明 */
void at24c02_init(void);                                            /* 初始化IIC */
uint8_t at24c02_check(void);                                        /* 检查器件 */
uint8_t at24c02_read_one_byte(uint8_t addr);                        /* 指定地址读取一个字节 */
void at24c02_write_one_byte(uint8_t addr,uint8_t data);             /* 指定地址写入一个字节 */
void at24c02_write(uint8_t addr, uint8_t *pbuf, uint8_t datalen);   /* 从指定地址开始写入指定长度的数据 */
void at24c02_read(uint8_t addr, uint8_t *pbuf, uint8_t datalen);    /* 从指定地址开始读出指定长度的数据 */

#endif
