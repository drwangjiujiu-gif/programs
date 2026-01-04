/**
 ****************************************************************************************************
 * @file        oled.cpp
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

#include "oled.h"
#include "xl9555.h"
#include "SSD1306Wire.h"

SSD1306Wire display(OLED_ADDR, OLED_SDA_PIN, OLED_SCL_PIN, GEOMETRY_128_64, I2C_TWO, 800000);   /* 定义OLED对象(显示异常,把800000降低) */

/**
 * @brief       OLED模块初始化
 * @param       无
 * @retval      无
 */
void oled_init(void)
{
    /* 初始化OLED需要用到的引脚 */
    pinMode(OLED_D2_PIN, INPUT_PULLUP);           /* OLED模块的D2和D1引脚需要连接在一起，所以为了不干扰D1，设置D2为输入模式 */
    pinMode(OLED_DC_PIN, OUTPUT);                 /* DC引脚跟地址有关 */
    digitalWrite(OLED_DC_PIN, 0);                 /* DC引脚接GND，8位地址为0x78; 接VCC，8位地址为0x7A */

    xl9555_io_config(OV_RESET, IO_SET_OUTPUT);    /* OLED模块的复位引脚连接到XL9555器件的P05引脚 */
    xl9555_pin_set(OV_RESET, IO_SET_HIGH);        /* 默认拉高复位引脚 */

    /* 硬件复位OLED模块 */
    OLED_RST(0);
    delay(100);
    OLED_RST(1);
    delay(100);

    display.init();                               /* 初始化OLED模块 */
    display.flipScreenVertically();               /* 垂直翻转屏幕设置 */
    display.setFont(ArialMT_Plain_24);            /* 设置24号字体 */
    display.drawString(0, 0, "ALIENTEK");         /* 24号字体显示ALIENTEK */
    display.setFont(ArialMT_Plain_16);            /* 设置16号字体 */    
    display.drawString(0, 24, "0.96' OLED TEST"); /* 16号字体显示0.96' OLED TEST */
    display.setFont(ArialMT_Plain_10);            /* 设置10号字体 */ 
    display.drawString(0, 40, "ATOM 2023/12/1");  /* 10号字体显示ATOM 2023/12/1 */
    display.drawString(0, 50, "ASCII:");          /* 10号字体显示ASCII: */
    display.drawString(64, 50, "CODE:");          /* 10号字体显示CODE: */
    display.display();                            /* 将缓存数据写入到显示器 */
}

/**
 * @brief       OLED模块展示效果
 * @param       无
 * @retval      无
 */
void oled_show_demo(void)
{
    char t = ' ';

    while(1)
    {
        display.setColor(BLACK);                        /* 颜色设置黑色 */
        display.fillRect(35, 50, 10, 15);               /* 清除ASCII显示区域 */
        display.fillRect(104, 50, 20, 15);              /* 清除CODE显示区域 */
        display.setColor(WHITE);                        /* 颜色设置白色 */
        display.drawString(35, 50, String(t));          /* 显示ASCII字符 */
        display.drawString(104, 50, String(t - 0));     /* 显示ASCII字符的码值 */
        display.display();                              /* 更新显示到OLED */

        t++;
        if (t > '~') 
        {
            t = ' ';
        }

        delay(500);
    }
}



  
