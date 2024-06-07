/**
 ****************************************************************************************************
 * @file        lcd.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.1
 * @date        2023-05-29
 * @brief       2.8寸/3.5寸/4.3寸/7寸 TFTLCD(MCU屏) 驱动代码
 *              支持驱动IC型号包括:ILI9341/NT35310/NT35510/SSD1963/ST7789/ST7796/ILI9806等
 *
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 探索者 F407开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 * 修改说明
 * V1.0 20211016
 * 第一次发布
 * V1.1 20230529
 * 1，新增对ST7796和ILI9806 IC支持
 * 2，简化部分代码，避免长判定
 ****************************************************************************************************
 */

#include "stdlib.h"
#include "lcd.h"
#include "lcdfont.h"
#include "usart.h"


/* lcd_ex.c存放各个LCD驱动IC的寄存器初始化部分代码,以简化lcd.c,该.c文件
 * 不直接加入到工程里面,只有lcd.c会用到,所以通过include的形式添加.(不要在
 * 其他文件再包含该.c文件!!否则会报错!)
 */

void lcd_ex_ili9341_reginit(void)
{
    lcd_wr_regno(0xCF);
    lcd_wr_data(0x00);
    lcd_wr_data(0xC1);
    lcd_wr_data(0x30);
    lcd_wr_regno(0xED);
    lcd_wr_data(0x64);
    lcd_wr_data(0x03);
    lcd_wr_data(0x12);
    lcd_wr_data(0x81);
    lcd_wr_regno(0xE8);
    lcd_wr_data(0x85);
    lcd_wr_data(0x10);
    lcd_wr_data(0x7A);
    lcd_wr_regno(0xCB);
    lcd_wr_data(0x39);
    lcd_wr_data(0x2C);
    lcd_wr_data(0x00);
    lcd_wr_data(0x34);
    lcd_wr_data(0x02);
    lcd_wr_regno(0xF7);
    lcd_wr_data(0x20);
    lcd_wr_regno(0xEA);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_regno(0xC0); /* Power control */
    lcd_wr_data(0x1B);  /* VRH[5:0] */
    lcd_wr_regno(0xC1); /* Power control */
    lcd_wr_data(0x01);  /* SAP[2:0];BT[3:0] */
    lcd_wr_regno(0xC5); /* VCM control */
    lcd_wr_data(0x30);  /* 3F */
    lcd_wr_data(0x30);  /* 3C */
    lcd_wr_regno(0xC7); /* VCM control2 */
    lcd_wr_data(0xB7);
    lcd_wr_regno(0x36); /* Memory Access Control */
    lcd_wr_data(0x48);
    lcd_wr_regno(0x3A);
    lcd_wr_data(0x55);
    lcd_wr_regno(0xB1);
    lcd_wr_data(0x00);
    lcd_wr_data(0x1A);
    lcd_wr_regno(0xB6); /* Display Function Control */
    lcd_wr_data(0x0A);
    lcd_wr_data(0xA2);
    lcd_wr_regno(0xF2); /* 3Gamma Function Disable */
    lcd_wr_data(0x00);
    lcd_wr_regno(0x26); /* Gamma curve selected */
    lcd_wr_data(0x01);
    lcd_wr_regno(0xE0); /* Set Gamma */
    lcd_wr_data(0x0F);
    lcd_wr_data(0x2A);
    lcd_wr_data(0x28);
    lcd_wr_data(0x08);
    lcd_wr_data(0x0E);
    lcd_wr_data(0x08);
    lcd_wr_data(0x54);
    lcd_wr_data(0xA9);
    lcd_wr_data(0x43);
    lcd_wr_data(0x0A);
    lcd_wr_data(0x0F);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_regno(0xE1); /* Set Gamma */
    lcd_wr_data(0x00);
    lcd_wr_data(0x15);
    lcd_wr_data(0x17);
    lcd_wr_data(0x07);
    lcd_wr_data(0x11);
    lcd_wr_data(0x06);
    lcd_wr_data(0x2B);
    lcd_wr_data(0x56);
    lcd_wr_data(0x3C);
    lcd_wr_data(0x05);
    lcd_wr_data(0x10);
    lcd_wr_data(0x0F);
    lcd_wr_data(0x3F);
    lcd_wr_data(0x3F);
    lcd_wr_data(0x0F);
    lcd_wr_regno(0x2B);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x01);
    lcd_wr_data(0x3f);
    lcd_wr_regno(0x2A);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0x00);
    lcd_wr_data(0xef);
    lcd_wr_regno(0x11); /* Exit Sleep */
    HAL_Delay(120);
    lcd_wr_regno(0x29); /* display on */
}

SRAM_HandleTypeDef g_sram_handle;   /* SRAM句柄(用于控制LCD) */

/* LCD的画笔颜色和背景色 */
uint32_t g_point_color = 0xF800;    /* 画笔颜色 */
uint32_t g_back_color  = 0xFFFF;    /* 背景色 */

/* 管理LCD重要参数 */
_lcd_dev lcddev;

/**
 * @brief       LCD写数据
 * @param       data: 要写入的数据
 * @retval      无
 */
void lcd_wr_data(volatile uint16_t data)
{
    data = data;            /* 使用-O2优化的时候,必须插入的延时 */
    LCD->LCD_RAM = data;
}

/**
 * @brief       LCD写寄存器编号/地址函数
 * @param       regno: 寄存器编号/地址
 * @retval      无
 */
void lcd_wr_regno(volatile uint16_t regno)
{
    regno = regno;          /* 使用-O2优化的时候,必须插入的延时 */
    LCD->LCD_REG = regno;   /* 写入要写的寄存器序号 */
}

/**
 * @brief       LCD写寄存器
 * @param       regno:寄存器编号/地址
 * @param       data:要写入的数据
 * @retval      无
 */
void lcd_write_reg(uint16_t regno, uint16_t data)
{
    LCD->LCD_REG = regno;   /* 写入要写的寄存器序号 */
    LCD->LCD_RAM = data;    /* 写入数据 */
}

/**
 * @brief       LCD延时函数,仅用于部分在mdk -O1时间优化时需要设置的地方
 * @param       t:延时的数值
 * @retval      无
 */
static void lcd_opt_delay(uint32_t i)
{
    while (i--); /* 使用AC6时空循环可能被优化,可使用while(1) __asm volatile(""); */
}

/**
 * @brief       LCD读数据
 * @param       无
 * @retval      读取到的数据
 */
static uint16_t lcd_rd_data(void)
{
    volatile uint16_t ram;  /* 防止被优化 */
    lcd_opt_delay(2);
    ram = LCD->LCD_RAM;
    return ram;
}

/**
 * @brief       准备写GRAM
 * @param       无
 * @retval      无
 */
void lcd_write_ram_prepare(void)
{
    LCD->LCD_REG = lcddev.wramcmd;
}

/**
 * @brief       读取个某点的颜色值
 * @param       x,y:坐标
 * @retval      此点的颜色(32位颜色,方便兼容LTDC)
 */
uint32_t lcd_read_point(uint16_t x, uint16_t y)
{
    uint16_t r = 0, g = 0, b = 0;

    if (x >= lcddev.width || y >= lcddev.height)
    {
        return 0;   /* 超过了范围,直接返回 */
    }

    lcd_set_cursor(x, y);       /* 设置坐标 */

    if (lcddev.id == 0x5510)
    {
        lcd_wr_regno(0x2E00);   /* 5510 发送读GRAM指令 */
    }
    else
    {
        lcd_wr_regno(0x2E);     /* 9341/5310/1963/7789/7796/9806 等发送读GRAM指令 */
    }


    r = lcd_rd_data();          /* 假读(dummy read) */

    if (lcddev.id == 0x1963)
    {
        return r;   /* 1963直接读就可以 */
    }

    r = lcd_rd_data();          /* 实际坐标颜色 */

    if (lcddev.id == 0x7796)    /* 7796 一次读取一个像素值 */
    {
        return r;
    }

    /* 9341/5310/5510/7789/9806要分2次读出 */
    b = lcd_rd_data();
    g = r & 0xFF;               /* 对于9341/5310/5510/7789/9806,第一次读取的是RG的值,R在前,G在后,各占8位 */
    g <<= 8;

    return (((r >> 11) << 11) | ((g >> 10) << 5) | (b >> 11));  /* ILI9341/NT35310/NT35510/ST7789/ILI9806需要公式转换一下 */
}

/**
 * @brief       LCD开启显示
 * @param       无
 * @retval      无
 */
void lcd_display_on(void)
{
    if (lcddev.id == 0x5510)
    {
        lcd_wr_regno(0x2900);   /* 开启显示 */
    }
    else                        /* 9341/5310/1963/7789/7796/9806 等发送开启显示指令 */
    {
        lcd_wr_regno(0x29);     /* 开启显示 */
    }
}

/**
 * @brief       LCD关闭显示
 * @param       无
 * @retval      无
 */
void lcd_display_off(void)
{
    if (lcddev.id == 0x5510)
    {
        lcd_wr_regno(0x2800);   /* 关闭显示 */
    }
    else                        /* 9341/5310/1963/7789/7796/9806 等发送关闭显示指令 */
    {
        lcd_wr_regno(0x28);     /* 关闭显示 */
    }
}

/**
 * @brief       设置光标位置(对RGB屏无效)
 * @param       x,y: 坐标
 * @retval      无
 */
void lcd_set_cursor(uint16_t x, uint16_t y)
{
    if (lcddev.id == 0x1963)
    {
        if (lcddev.dir == 0)    /* 竖屏模式, x坐标需要变换 */
        {
            x = lcddev.width - 1 - x;
            lcd_wr_regno(lcddev.setxcmd);
            lcd_wr_data(0);
            lcd_wr_data(0);
            lcd_wr_data(x >> 8);
            lcd_wr_data(x & 0xFF);
        }
        else                    /* 横屏模式 */
        {
            lcd_wr_regno(lcddev.setxcmd);
            lcd_wr_data(x >> 8);
            lcd_wr_data(x & 0xFF);
            lcd_wr_data((lcddev.width - 1) >> 8);
            lcd_wr_data((lcddev.width - 1) & 0xFF);
        }

        lcd_wr_regno(lcddev.setycmd);
        lcd_wr_data(y >> 8);
        lcd_wr_data(y & 0xFF);
        lcd_wr_data((lcddev.height - 1) >> 8);
        lcd_wr_data((lcddev.height - 1) & 0xFF);

    }
    else if (lcddev.id == 0x5510)
    {
        lcd_wr_regno(lcddev.setxcmd);
        lcd_wr_data(x >> 8);
        lcd_wr_regno(lcddev.setxcmd + 1);
        lcd_wr_data(x & 0xFF);
        lcd_wr_regno(lcddev.setycmd);
        lcd_wr_data(y >> 8);
        lcd_wr_regno(lcddev.setycmd + 1);
        lcd_wr_data(y & 0xFF);
    }
    else    /* 9341/5310/7789/7796/9806 等 设置坐标 */
    {
        lcd_wr_regno(lcddev.setxcmd);
        lcd_wr_data(x >> 8);
        lcd_wr_data(x & 0xFF);
        lcd_wr_regno(lcddev.setycmd);
        lcd_wr_data(y >> 8);
        lcd_wr_data(y & 0xFF);
    }
}

/**
 * @brief       设置LCD的自动扫描方向(对RGB屏无效)
 *   @note
 *              9341/5310/5510/1963/7789/7796/9806等IC已经实际测试
 *              注意:其他函数可能会受到此函数设置的影响(尤其是9341),
 *              所以,一般设置为L2R_U2D即可,如果设置为其他扫描方式,可能导致显示不正常.
 *
 * @param       dir:0~7,代表8个方向(具体定义见lcd.h)
 * @retval      无
 */
void lcd_scan_dir(uint8_t dir)
{
    uint16_t regval = 0;
    uint16_t dirreg = 0;
    uint16_t temp;

    /* 横屏时，对1963不改变扫描方向！竖屏时1963改变方向(这里仅用于1963的特殊处理,对其他驱动IC无效) */
    if ((lcddev.dir == 1 && lcddev.id != 0x1963) || (lcddev.dir == 0 && lcddev.id == 0x1963))
    {
        switch (dir)   /* 方向转换 */
        {
            case 0:
                dir = 6;
                break;

            case 1:
                dir = 7;
                break;

            case 2:
                dir = 4;
                break;

            case 3:
                dir = 5;
                break;

            case 4:
                dir = 1;
                break;

            case 5:
                dir = 0;
                break;

            case 6:
                dir = 3;
                break;

            case 7:
                dir = 2;
                break;
        }
    }


    /* 根据扫描方式 设置 0x36/0x3600 寄存器 bit 5,6,7 位的值 */
    switch (dir)
    {
        case L2R_U2D:   /* 从左到右,从上到下 */
            regval |= (0 << 7) | (0 << 6) | (0 << 5);
            break;

        case L2R_D2U:   /* 从左到右,从下到上 */
            regval |= (1 << 7) | (0 << 6) | (0 << 5);
            break;

        case R2L_U2D:   /* 从右到左,从上到下 */
            regval |= (0 << 7) | (1 << 6) | (0 << 5);
            break;

        case R2L_D2U:   /* 从右到左,从下到上 */
            regval |= (1 << 7) | (1 << 6) | (0 << 5);
            break;

        case U2D_L2R:   /* 从上到下,从左到右 */
            regval |= (0 << 7) | (0 << 6) | (1 << 5);
            break;

        case U2D_R2L:   /* 从上到下,从右到左 */
            regval |= (0 << 7) | (1 << 6) | (1 << 5);
            break;

        case D2U_L2R:   /* 从下到上,从左到右 */
            regval |= (1 << 7) | (0 << 6) | (1 << 5);
            break;

        case D2U_R2L:   /* 从下到上,从右到左 */
            regval |= (1 << 7) | (1 << 6) | (1 << 5);
            break;
    }

    dirreg = 0x36;  /* 对绝大部分驱动IC, 由0x36寄存器控制 */

    if (lcddev.id == 0x5510)
    {
        dirreg = 0x3600;    /* 对于5510, 和其他驱动ic的寄存器有差异 */
    }

     /* 9341 & 7789 & 7796 要设置BGR位 */
    if (lcddev.id == 0x9341 || lcddev.id == 0x7789 || lcddev.id == 0x7796)
    {
        regval |= 0x08;
    }

    lcd_write_reg(dirreg, regval);

    if (lcddev.id != 0x1963)                    /* 1963不做坐标处理 */
    {
        if (regval & 0x20)
        {
            if (lcddev.width < lcddev.height)   /* 交换X,Y */
            {
                temp = lcddev.width;
                lcddev.width = lcddev.height;
                lcddev.height = temp;
            }
        }
        else
        {
            if (lcddev.width > lcddev.height)   /* 交换X,Y */
            {
                temp = lcddev.width;
                lcddev.width = lcddev.height;
                lcddev.height = temp;
            }
        }
    }

    /* 设置显示区域(开窗)大小 */
    if (lcddev.id == 0x5510)
    {
        lcd_wr_regno(lcddev.setxcmd);
        lcd_wr_data(0);
        lcd_wr_regno(lcddev.setxcmd + 1);
        lcd_wr_data(0);
        lcd_wr_regno(lcddev.setxcmd + 2);
        lcd_wr_data((lcddev.width - 1) >> 8);
        lcd_wr_regno(lcddev.setxcmd + 3);
        lcd_wr_data((lcddev.width - 1) & 0xFF);
        lcd_wr_regno(lcddev.setycmd);
        lcd_wr_data(0);
        lcd_wr_regno(lcddev.setycmd + 1);
        lcd_wr_data(0);
        lcd_wr_regno(lcddev.setycmd + 2);
        lcd_wr_data((lcddev.height - 1) >> 8);
        lcd_wr_regno(lcddev.setycmd + 3);
        lcd_wr_data((lcddev.height - 1) & 0xFF);
    }
    else
    {
        lcd_wr_regno(lcddev.setxcmd);
        lcd_wr_data(0);
        lcd_wr_data(0);
        lcd_wr_data((lcddev.width - 1) >> 8);
        lcd_wr_data((lcddev.width - 1) & 0xFF);
        lcd_wr_regno(lcddev.setycmd);
        lcd_wr_data(0);
        lcd_wr_data(0);
        lcd_wr_data((lcddev.height - 1) >> 8);
        lcd_wr_data((lcddev.height - 1) & 0xFF);
    }
}

/**
 * @brief       画点
 * @param       x,y: 坐标
 * @param       color: 点的颜色(32位颜色,方便兼容LTDC)
 * @retval      无
 */
void lcd_draw_point(uint16_t x, uint16_t y, uint32_t color)
{
    lcd_set_cursor(x, y);       /* 设置光标位置 */
    lcd_write_ram_prepare();    /* 开始写入GRAM */
    LCD->LCD_RAM = color;
}

/**
 * @brief       SSD1963背光亮度设置函数
 * @param       pwm: 背光等级,0~100.越大越亮.
 * @retval      无
 */
void lcd_ssd_backlight_set(uint8_t pwm)
{
    lcd_wr_regno(0xBE);         /* 配置PWM输出 */
    lcd_wr_data(0x05);          /* 1设置PWM频率 */
    lcd_wr_data(pwm * 2.55);    /* 2设置PWM占空比 */
    lcd_wr_data(0x01);          /* 3设置C */
    lcd_wr_data(0xFF);          /* 4设置D */
    lcd_wr_data(0x00);          /* 5设置E */
    lcd_wr_data(0x00);          /* 6设置F */
}

/**
 * @brief       设置LCD显示方向
 * @param       dir:0,竖屏; 1,横屏
 * @retval      无
 */
void lcd_display_dir(uint8_t dir)
{
    lcddev.dir = dir;   /* 竖屏/横屏 */

    if (dir == 0)       /* 竖屏 */
    {
        lcddev.width = 240;
        lcddev.height = 320;

        if (lcddev.id == 0x5510)
        {
            lcddev.wramcmd = 0x2C00;
            lcddev.setxcmd = 0x2A00;
            lcddev.setycmd = 0x2B00;
            lcddev.width = 480;
            lcddev.height = 800;
        }
        else if (lcddev.id == 0x1963)
        {
            lcddev.wramcmd = 0x2C;  /* 设置写入GRAM的指令 */
            lcddev.setxcmd = 0x2B;  /* 设置写X坐标指令 */
            lcddev.setycmd = 0x2A;  /* 设置写Y坐标指令 */
            lcddev.width = 480;     /* 设置宽度480 */
            lcddev.height = 800;    /* 设置高度800 */
        }
        else   /* 其他IC, 包括: 9341/5310/7789/7796/9806等IC */
        {
            lcddev.wramcmd = 0x2C;
            lcddev.setxcmd = 0x2A;
            lcddev.setycmd = 0x2B;
        }

        if (lcddev.id == 0x5310 || lcddev.id == 0x7796)     /* 如果是5310/7796 则表示是 320*480分辨率 */
        {
            lcddev.width = 320;
            lcddev.height = 480;
        }
        
        if (lcddev.id == 0X9806)    /* 如果是9806 则表示是 480*800 分辨率 */
        {
            lcddev.width = 480;
            lcddev.height = 800;
        }  
    }
    else        /* 横屏 */
    {
        lcddev.width = 320;         /* 默认宽度 */
        lcddev.height = 240;        /* 默认高度 */

        if (lcddev.id == 0x5510)
        {
            lcddev.wramcmd = 0x2C00;
            lcddev.setxcmd = 0x2A00;
            lcddev.setycmd = 0x2B00;
            lcddev.width = 800;
            lcddev.height = 480;
        }
        else if (lcddev.id == 0x1963 || lcddev.id == 0x9806)
        {
            lcddev.wramcmd = 0x2C;  /* 设置写入GRAM的指令 */
            lcddev.setxcmd = 0x2A;  /* 设置写X坐标指令 */
            lcddev.setycmd = 0x2B;  /* 设置写Y坐标指令 */
            lcddev.width = 800;     /* 设置宽度800 */
            lcddev.height = 480;    /* 设置高度480 */
        }
        else   /* 其他IC, 包括:9341/5310/7789/7796等IC */
        {
            lcddev.wramcmd = 0x2C;
            lcddev.setxcmd = 0x2A;
            lcddev.setycmd = 0x2B;
        }

        if (lcddev.id == 0x5310 || lcddev.id == 0x7796)     /* 如果是5310/7796 则表示是 320*480分辨率 */
        {
            lcddev.width = 480;
            lcddev.height = 320;
        }
    }

    lcd_scan_dir(DFT_SCAN_DIR);     /* 默认扫描方向 */
}

/**
 * @brief       初始化LCD
 *   @note      该初始化函数可以初始化各种型号的LCD(详见本.c文件最前面的描述)
 *
 * @param       无
 * @retval      无
 */
void lcd_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    FSMC_NORSRAM_TimingTypeDef fsmc_read_handle;
    FSMC_NORSRAM_TimingTypeDef fsmc_write_handle;

    LCD_CS_GPIO_CLK_ENABLE();   /* LCD_CS脚时钟使能 */
    LCD_WR_GPIO_CLK_ENABLE();   /* LCD_WR脚时钟使能 */
    LCD_RD_GPIO_CLK_ENABLE();   /* LCD_RD脚时钟使能 */
    LCD_RS_GPIO_CLK_ENABLE();   /* LCD_RS脚时钟使能 */
    LCD_BL_GPIO_CLK_ENABLE();   /* LCD_BL脚时钟使能 */
    
    gpio_init_struct.Pin = LCD_CS_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;                /* 推挽复用 */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
    gpio_init_struct.Alternate = GPIO_AF12_FSMC;            /* 复用为FSMC */
    HAL_GPIO_Init(LCD_CS_GPIO_PORT, &gpio_init_struct);     /* 初始化LCD_CS引脚 */

    gpio_init_struct.Pin = LCD_WR_GPIO_PIN;
    HAL_GPIO_Init(LCD_WR_GPIO_PORT, &gpio_init_struct);     /* 初始化LCD_WR引脚 */

    gpio_init_struct.Pin = LCD_RD_GPIO_PIN;
    HAL_GPIO_Init(LCD_RD_GPIO_PORT, &gpio_init_struct);     /* 初始化LCD_RD引脚 */

    gpio_init_struct.Pin = LCD_RS_GPIO_PIN;
    HAL_GPIO_Init(LCD_RS_GPIO_PORT, &gpio_init_struct);     /* 初始化LCD_RS引脚 */

    gpio_init_struct.Pin = LCD_BL_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* 推挽输出 */
    HAL_GPIO_Init(LCD_BL_GPIO_PORT, &gpio_init_struct);     /* LCD_BL引脚模式设置(推挽输出) */

    g_sram_handle.Instance = FSMC_NORSRAM_DEVICE;
    g_sram_handle.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
    
    g_sram_handle.Init.NSBank = FSMC_NORSRAM_BANK4;                        /* 使用NE4 */
    g_sram_handle.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;     /* 地址/数据线不复用 */
    g_sram_handle.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;    /* 16位数据宽度 */
    g_sram_handle.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;   /* 是否使能突发访问,仅对同步突发存储器有效,此处未用到 */
    g_sram_handle.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW; /* 等待信号的极性,仅在突发模式访问下有用 */
    g_sram_handle.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;      /* 存储器是在等待周期之前的一个时钟周期还是等待周期期间使能NWAIT */
    g_sram_handle.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;       /* 存储器写使能 */
    g_sram_handle.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;              /* 等待使能位,此处未用到 */
    g_sram_handle.Init.ExtendedMode = FSMC_EXTENDED_MODE_ENABLE;           /* 读写使用不同的时序 */
    g_sram_handle.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;  /* 是否使能同步传输模式下的等待信号,此处未用到 */
    g_sram_handle.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;              /* 禁止突发写 */
    
    /* FSMC读时序控制寄存器 */
    fsmc_read_handle.AddressSetupTime = 0x0F;           /* 地址建立时间(ADDSET)为15个fsmc_ker_ck(1/168=6)即6*15=90ns */
    fsmc_read_handle.AddressHoldTime = 0x00;            /* 地址保持时间(ADDHLD) 模式A是没有用到 */
    fsmc_read_handle.DataSetupTime = 60;                /* 数据保存时间(DATAST)为60个fsmc_ker_ck=6*60=360ns */
                                                        /* 因为液晶驱动IC的读数据的时候,速度不能太快,尤其是个别奇葩芯片 */
    fsmc_read_handle.AccessMode = FSMC_ACCESS_MODE_A;   /* 模式A */
    
    /* FSMC写时序控制寄存器 */
    fsmc_write_handle.AddressSetupTime = 9;             /* 地址建立时间(ADDSET)为9个fsmc_ker_ck=6*9=54ns */
    fsmc_write_handle.AddressHoldTime = 0x00;           /* 地址保持时间(ADDHLD) 模式A是没有用到 */
    fsmc_write_handle.DataSetupTime = 9;                /* 数据保存时间(DATAST)为9个fsmc_ker_ck=6*9=54ns */
                                                        /* 注意：某些液晶驱动IC的写信号脉宽，最少也得50ns */
    fsmc_write_handle.AccessMode = FSMC_ACCESS_MODE_A;  /* 模式A */
    
    HAL_SRAM_Init(&g_sram_handle, &fsmc_read_handle, &fsmc_write_handle);
    HAL_Delay(50);

    /* 尝试9341 ID的读取 */
    lcd_wr_regno(0xD3);
    lcddev.id = lcd_rd_data();  /* dummy read */
    lcddev.id = lcd_rd_data();  /* 读到0x00 */
    lcddev.id = lcd_rd_data();  /* 读取93 */
    lcddev.id <<= 8;
    lcddev.id |= lcd_rd_data(); /* 读取41 */

    lcd_ex_ili9341_reginit();

    fsmc_write_handle.AddressSetupTime = 2; /* 地址建立时间(ADDSET)为2个fsmc_ker_ck=6*2=12ns */
    fsmc_write_handle.DataSetupTime = 2;    /* 数据保持时间(DATAST)为2个fsmc_ker_ck=6*2=12ns */
    FSMC_NORSRAM_Extended_Timing_Init(g_sram_handle.Extended, &fsmc_write_handle, g_sram_handle.Init.NSBank, g_sram_handle.Init.ExtendedMode);
    lcd_display_dir(0); /* 默认为竖屏 */
    LCD_BL(1);          /* 点亮背光 */
}

/**
 * @brief       在指定区域内填充单个颜色
 * @param       (sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex - sx + 1) * (ey - sy + 1)
 * @param       color:  要填充的颜色(32位颜色,方便兼容LTDC)
 * @retval      无
 */
void lcd_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint32_t color)
{
    uint16_t i, j;
    uint16_t xlen = 0;
    xlen = ex - sx + 1;

    for (i = sy; i <= ey; i++)
    {
        lcd_set_cursor(sx, i);      /* 设置光标位置 */
        lcd_write_ram_prepare();    /* 开始写入GRAM */

        for (j = 0; j < xlen; j++)
        {
            LCD->LCD_RAM = color;   /* 显示颜色 */
        }
    }
}

/**
 * @brief       在指定区域内填充指定颜色块
 * @param       (sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex - sx + 1) * (ey - sy + 1)
 * @param       color: 要填充的颜色数组首地址
 * @retval      无
 */
void lcd_color_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t *color)
{
    uint16_t height, width;
    uint16_t i, j;

    width = ex - sx + 1;            /* 得到填充的宽度 */
    height = ey - sy + 1;           /* 高度 */

    for (i = 0; i < height; i++)
    {
        lcd_set_cursor(sx, sy + i); /* 设置光标位置 */
        lcd_write_ram_prepare();    /* 开始写入GRAM */

        for (j = 0; j < width; j++)
        {
            LCD->LCD_RAM = color[i * width + j]; /* 写入数据 */
        }
    }
}
