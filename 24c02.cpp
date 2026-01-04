/**
 ****************************************************************************************************
 * @file        24c02.cpp
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

#include "24c02.h"
#include <Wire.h>

/**
 * @brief       初始化EEPROM器件
 * @param       无
 * @retval      无
 */
void at24c02_init(void)
{
    Wire.begin(IIC_SDA, IIC_SCL, 400000);    /* 初始化IIC连接 */
}

/**
 * @brief       在AT24C02指定地址读出一个数据
 * @param       addr: 开始读取数据的地址
 * @retval      读到的数据 / 0xFF:未接收到数据
 */
uint8_t at24c02_read_one_byte(uint8_t addr)
{
    Wire.beginTransmission(EEPROM_ADDR);      /* 发送从机的7位器件地址到发送队列 */
    Wire.write(addr);                         /* 发送要读取从机数据的地址到发送队列 */
    Wire.endTransmission(0);                  /* IIC 发送 发送队列的数据(传参为0,表示重新发送一个start信号,保持IIC总线有效连接) */

    Wire.requestFrom(EEPROM_ADDR, 1);         /* 主机向从机发送数据请求,并获取到数据 */
    if (Wire.available() != 0)                /* 得到已经接收到的数据字节数 */
    {
        return Wire.read();                   /* 到数据缓冲区读取数据 */
    }

    return 0xFF;
}

/**
 * @brief       在AT24C02指定地址写入一个数据
 * @param       addr: 写入数据的目的地址
 * @param       data: 要写入的数据
 * @retval      无
 */
void at24c02_write_one_byte(uint8_t addr, uint8_t data)
{
    Wire.beginTransmission(EEPROM_ADDR);    /* 发送从机的7位器件地址到发送队列 */
    Wire.write(addr);                       /* 发送要写入从机数据的地址到发送队列 */
    Wire.write(data);                       /* 发送要写入从机数据到发送队列 */
    Wire.endTransmission(1);                /* IIC 发送 发送队列的数据(传参为1,表示发送stop信号,结束传输) */

    delay(10);    /* 注意: EEPROM 写入比较慢,必须等到10ms后再写下一个字节 */
}

/**
 * @brief       检查AT24C02是否正常
 *   @note      检测原理: 在器件的末地址写如0X55, 然后再读取, 如果读取值为0X55
 *              则表示检测正常. 否则,则表示检测失败.
 *
 * @param       无
 * @retval      检测结果
 *              0: 检测成功
 *              1: 检测失败
 */
uint8_t at24c02_check(void)
{
    uint8_t temp;

    temp = at24c02_read_one_byte(255);      /* 避免每次开机都写AT24CXX */

    if (temp == 0X55)                       /* 读取数据正常 */
    {
        return 0;
    }
    else                                    /* 排除第一次初始化的情况 */
    {
        at24c02_write_one_byte(255, 0X55);  /* 先写入数据 */
        temp = at24c02_read_one_byte(255);  /* 再读取数据 */
        
        if (temp == 0X55) 
        {
            return 0;
        }
    }

    return 1;
}

/**
 * @brief       在AT24C02里面的指定地址开始读出指定个数的数据
 * @param       addr    : 开始读出的地址 对24c02为0~255
 * @param       pbuf    : 数据数组首地址
 * @param       datalen : 要读出数据的个数
 * @retval      无
 */
void at24c02_read(uint8_t addr, uint8_t *pbuf, uint8_t datalen)
{
    while (datalen--)
    {
        *pbuf++ = at24c02_read_one_byte(addr++);
    }
}

/**
 * @brief       在AT24C02里面的指定地址开始写入指定个数的数据
 * @param       addr    : 开始写入的地址 对24c02为0~255
 * @param       pbuf    : 数据数组首地址
 * @param       datalen : 要写入数据的个数
 * @retval      无
 */
void at24c02_write(uint8_t addr, uint8_t *pbuf, uint8_t datalen)
{
    while (datalen--)
    {
        at24c02_write_one_byte(addr, *pbuf);
        addr++;
        pbuf++;
    }
}
