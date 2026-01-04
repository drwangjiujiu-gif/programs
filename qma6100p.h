/**
 ****************************************************************************************************
 * @file        qma6100p.h
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

#ifndef __QMA6100P_H
#define __QMA6100P_H

#include "Arduino.h"

#define IIC_SCL     42
#define IIC_SDA     41

#define IMU_DEV_ADDR              0x12    /* 7位器件地址 */

#define QMA6100P_DEVICE_ID        0x90
#define QMA6100P_CHIP_ID          0x00

#define QMA6100P_XOUTL            0x01    /* QMA6100P寄存器X轴加速度地址 */
#define QMA6100P_XOUTH            0x02
#define QMA6100P_YOUTL            0x03    /* QMA6100P寄存器Y轴加速度地址 */
#define QMA6100P_YOUTH            0x04
#define QMA6100P_ZOUTL            0x05    /* QMA6100P寄存器Z轴加速度地址 */
#define QMA6100P_ZOUTH            0x06

#define QMA6100P_STEP_CNT_L       0x07
#define QMA6100P_STEP_CNT_M       0x08
#define QMA6100P_STEP_CNT_H       0x0d

#define QMA6100P_INT_STATUS_0     0x09
#define QMA6100P_INT_STATUS_1     0x0a
#define QMA6100P_INT_STATUS_2     0x0b
#define QMA6100P_INT_STATUS_3     0x0c

#define QMA6100P_FIFO_STATE       0x0e

#define QMA6100P_REG_RANGE        0x0f
#define QMA6100P_REG_BW_ODR       0x10
#define QMA6100P_REG_POWER_MANAGE 0x11

#define QMA6100P_STEP_SAMPLE_CNT  0x12
#define QMA6100P_STEP_PRECISION   0x13
#define QMA6100P_STEP_TIME_LOW    0x14
#define QMA6100P_STEP_TIME_UP     0x15

#define QMA6100P_INT_EN_0         0x16
#define QMA6100P_INT_EN_1         0x17
#define QMA6100P_INT_EN_2         0x18

#define QMA6100P_INT1_MAP_0       0x19
#define QMA6100P_INT1_MAP_1       0x1a
#define QMA6100P_INT2_MAP_0       0x1b
#define QMA6100P_INT2_MAP_1       0x1c

#define QMA6100P_INTPIN_CFG       0x20

#define QMA6100P_INT_CFG          0x21

#define QMA6100P_OS_CUST_X        0x27
#define QMA6100P_OS_CUST_Y        0x28
#define QMA6100P_OS_CUST_Z        0x29

#define QMA6100P_REG_NVM          0x33
#define QMA6100P_REG_RESET        0x36

#define QMA6100P_DRDY_BIT         0x10

#define QMA6100P_AMD_X_BIT        0x01
#define QMA6100P_AMD_Y_BIT        0x02
#define QMA6100P_AMD_Z_BIT        0x04

typedef enum
{
  QMA6100P_BW_100 = 0,
  QMA6100P_BW_200 = 1,
  QMA6100P_BW_400 = 2,
  QMA6100P_BW_800 = 3,
  QMA6100P_BW_1600 = 4,
  QMA6100P_BW_50 = 5,
  QMA6100P_BW_25 = 6,
  QMA6100P_BW_12_5 = 7,
  QMA6100P_BW_OTHER = 8
}qma6100p_bw;

typedef enum
{
  QMA6100P_RANGE_2G = 0x01,
  QMA6100P_RANGE_4G = 0x02,
  QMA6100P_RANGE_8G = 0x04,
  QMA6100P_RANGE_16G = 0x08,
  QMA6100P_RANGE_32G = 0x0f
} qma6100p_range;

typedef enum
{
  QMA6100P_LPF_OFF = (0x00<<5),
  QMA6100P_LPF_1 = (0x04<<5),
  QMA6100P_LPF_2 = (0x01<<5),
  QMA6100P_LPF_4 = (0x02<<5),
  QMA6100P_LPF_8 = (0x03<<5),
  QMA6100P_LPF_RESERVED = 0xff
} qma6100p_nlpf;

typedef enum
{
  QMA6100P_MODE_STANDBY = 0,
  QMA6100P_MODE_ACTIVE = 1,
  QMA6100P_MODE_MAX
} qma6100p_mode;

typedef enum
{
  QMA6100P_MCLK_102_4K = 0x03,
  QMA6100P_MCLK_51_2K = 0x04,
  QMA6100P_MCLK_25_6K = 0x05,
  QMA6100P_MCLK_12_8K = 0x06,
  QMA6100P_MCLK_6_4K = 0x07,
  QMA6100P_MCLK_RESERVED = 0xff
} qma6100p_mclk;

/* 函数声明 */
uint8_t qma6100p_init(void);                                      /* QMA6100P初始化 */
void qma6100p_read_reg(uint8_t reg, uint8_t *buf, uint16_t num);  /* 从QMA6100P读取N字节数据 */
void qma6100p_write_reg(uint8_t reg, uint8_t data);               /* QMA6100P对寄存器配置 */
void qma6100p_read_raw_xyz(int16_t data[3]);                      /* 从QMA6100P寄存器中读取原始x,y,z轴数据 */
void qma6100p_read_acc_xyz(float accdata[3]);                     /* 计算得到加速度计的x,y,z轴数据 */

#endif
