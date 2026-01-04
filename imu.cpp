/**
 ****************************************************************************************************
 * @file        imu.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-12-01
 * @brief       IMU姿态解算代码
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

#include "imu.h"
#include <math.h>


#define M_PI		  	(3.14159265358979323846f)
#define RAD_TO_DEG	(180.0f / M_PI) 	


/**
 * @brief       得到姿态解算后的欧拉角
 * @param       accl_in  : 3轴加速度数据
 * @param       angle  : 俯仰角、横滚角
 * @retval      返回值 : 欧拉角
 */
void acc_get_angle(float accl_in[3], float angle[2])
{   
    float accl_data[3];
    float acc_normal, pitch, roll;

    acc_normal = sqrtf(accl_in[0] * accl_in[0] + accl_in[1] * accl_in[1] + accl_in[2] * accl_in[2]);
    
    accl_data[0] = accl_in[0] / acc_normal;
    accl_data[1] = accl_in[1] / acc_normal;
    accl_data[2] = accl_in[2] / acc_normal;

    pitch = -atan2f(accl_in[0], accl_in[2]);
    angle[0] = pitch * RAD_TO_DEG;  

    acc_normal = sqrtf(accl_data[0] * accl_data[0] + accl_data[1] * accl_data[1] + accl_data[2] * accl_data[2]);
    roll = asinf((accl_data[1] / acc_normal));
    angle[1] = roll * RAD_TO_DEG; 
    //Serial.printf("g_pitch:%lf g_roll:%lf \r\n", angle[0], angle[1]);
}