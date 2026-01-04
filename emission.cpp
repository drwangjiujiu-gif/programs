/**
 ****************************************************************************************************
 * @file        emission.cpp
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2023-12-01
 * @brief       EMISSION 驱动代码
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

#include "emission.h"
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "spilcd.h"

IRsend irsend(RMT_TX_PIN);

/**
 * @brief       红外发送初始化
 * @param       无
 * @retval      无
 */
void emission_init(void)
{
    irsend.begin();
}

/**
 * @brief       发送红外数据
 * @param       data:控制码
 * @retval      无
 */
void emission_send(uint8_t data)
{  
    uint32_t send_data = 0;
    uint8_t data_oppo = 0;

    data_oppo = ~data;
    send_data = 0x00FF0000UL | data << 8 | data_oppo;
    irsend.sendNEC(send_data);
}



