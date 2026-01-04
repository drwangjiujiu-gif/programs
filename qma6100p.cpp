/**
 ****************************************************************************************************
 * @file        qma6100p.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-12-01
 * @brief       QMA6100P 驱动代码
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

#include "qma6100p.h"
#include <Wire.h>


#define M_G     9.80665f

/**
 * @brief       QMA6100P对寄存器配置函数
 * @param       reg     : 寄存器地址
 * @param       data    : 写入到寄存器数据
 * @retval      无
 */
void qma6100p_write_reg(uint8_t reg, uint8_t data)
{
    Wire.beginTransmission(IMU_DEV_ADDR);     /* 发送从机的7位器件地址到发送队列 */
    Wire.write(reg);                          /* 发送要写入从机寄存器的地址到发送队列 */
    Wire.write(data);                         /* 发送要写入从机寄存器的数据到发送队列 */
    Wire.endTransmission();                   /* IIC 发送 发送队列的数据(不带参数,表示发送stop信号,结束传输) */
}

/**
 * @brief       从QMA6100P读取N字节数据
 * @param       reg  : 寄存器地址
 * @param       buf  : 数据存储buf
 * @param       num   : 读取长度
 * @retval      无
 */
void qma6100p_read_reg(uint8_t reg, uint8_t *buf, uint16_t num)
{
    uint8_t i = 0;

    Wire.beginTransmission(IMU_DEV_ADDR);     /* 发送从机的7位器件地址到发送队列 */
    Wire.write(reg);                          /* 发送要读取从机的寄存器地址到发送队列 */
    Wire.endTransmission(0);                  /* IIC 发送 发送队列的数据(传参为0,表示重新发送一个start信号,保持IIC总线有效连接) */

    Wire.requestFrom(IMU_DEV_ADDR, num);      /* 主机向从机发送数据请求,并获取到数据 */

    while (Wire.available())                  /* 得到已经接收到的数据字节数 */
    {
        buf[i++] = Wire.read();               /* 到数据缓冲区读取数据 */
    }
}

/**
* @brief       qma6100p初始化函数
* @param       无
* @retval      0:成功，非0:失败
*/
uint8_t qma6100p_init(void)
{
    uint8_t id = 0;

    Wire.begin(IIC_SDA, IIC_SCL, 400000);           /* 初始化IIC总线 */

    qma6100p_read_reg(QMA6100P_CHIP_ID, &id, 1);    /* 读取QMA6100P器件ID */
    if (id != QMA6100P_DEVICE_ID)
    {
        Serial.printf("ID:%#x \r\n", id);
        return 0xFF;
    }

    /* 软件复位 */
    qma6100p_write_reg(QMA6100P_REG_RESET, 0xb6);
    delay(5);
    qma6100p_write_reg(QMA6100P_REG_RESET, 0x00);
    delay(10);

    /* 厂家推荐的初始化序列 */
    qma6100p_write_reg(0x11, 0x80);   /* 从standby到active状态(0x11寄存器<7>=1) */
    qma6100p_write_reg(0x11, 0x84);
    qma6100p_write_reg(0x4a, 0x20);
    qma6100p_write_reg(0x56, 0x01);
    qma6100p_write_reg(0x5f, 0x80);
    delay(2);
    qma6100p_write_reg(0x5f, 0x00);
    delay(10);

    /* 设置QMA6100P的配置参数(量程、输出频率、工作模式) */
    qma6100p_write_reg(QMA6100P_REG_RANGE, QMA6100P_RANGE_8G);                              /* 设置加速度计满量程范围(8G) */
    qma6100p_write_reg(QMA6100P_REG_BW_ODR, (uint8_t)(QMA6100P_BW_100 | QMA6100P_LPF_OFF)); /* 设置输出数据速率(100khz) */
    qma6100p_write_reg(QMA6100P_REG_POWER_MANAGE, (uint8_t)QMA6100P_MCLK_51_2K | 0x80);     /* 设置加速度的工作模式 */

    return 0;
}

/**
 * @brief       从QMA6100P寄存器中读取原始x,y,z轴数据
 * @param       data  : 3轴数据存储数组
 * @retval      无
 */
void qma6100p_read_raw_xyz(int16_t data[3])
{
    uint8_t databuf[6] = {0}; 
    int16_t raw_data[3];

    qma6100p_read_reg(QMA6100P_XOUTL, databuf, 6);

    raw_data[0] = (int16_t)(((databuf[1] << 8)) | (databuf[0]));
    raw_data[1] = (int16_t)(((databuf[3] << 8)) | (databuf[2]));
    raw_data[2] = (int16_t)(((databuf[5] << 8)) | (databuf[4]));

    data[0] = raw_data[0] >> 2;
    data[1] = raw_data[1] >> 2;
    data[2] = raw_data[2] >> 2;
}

/**
 * @brief       计算得到加速度计的x,y,z轴数据
 * @param       accdata  : 3轴数据存储数组
 * @retval      无
 */
void qma6100p_read_acc_xyz(float accdata[3]) 
{
    int16_t rawdata[3];

    qma6100p_read_raw_xyz(rawdata);

    accdata[0] = (float)(rawdata[0] * M_G) / 1024;
    accdata[1] = (float)(rawdata[1] * M_G) / 1024;
    accdata[2] = (float)(rawdata[2] * M_G) / 1024;
}

