/**
 ****************************************************************************************************
 * @file        lcd.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.1
 * @date        2023-05-29
 * @brief       2.8��/3.5��/4.3��/7�� TFTLCD(MCU��) ��������
 *              ֧������IC�ͺŰ���:ILI9341/NT35310/NT35510/SSD1963/ST7789/ST7796/ILI9806��
 *
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� ̽���� F407������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 * �޸�˵��
 * V1.0 20211016
 * ��һ�η���
 * V1.1 20230529
 * 1��������ST7796��ILI9806 IC֧��
 * 2���򻯲��ִ��룬���ⳤ�ж�
 ****************************************************************************************************
 */

#include "stdlib.h"
#include "lcd.h"
#include "lcdfont.h"
#include "usart.h"


/* lcd_ex.c��Ÿ���LCD����IC�ļĴ�����ʼ�����ִ���,�Լ�lcd.c,��.c�ļ�
 * ��ֱ�Ӽ��뵽��������,ֻ��lcd.c���õ�,����ͨ��include����ʽ���.(��Ҫ��
 * �����ļ��ٰ�����.c�ļ�!!����ᱨ��!)
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

SRAM_HandleTypeDef g_sram_handle;   /* SRAM���(���ڿ���LCD) */

/* LCD�Ļ�����ɫ�ͱ���ɫ */
uint32_t g_point_color = 0xF800;    /* ������ɫ */
uint32_t g_back_color  = 0xFFFF;    /* ����ɫ */

/* ����LCD��Ҫ���� */
_lcd_dev lcddev;

/**
 * @brief       LCDд����
 * @param       data: Ҫд�������
 * @retval      ��
 */
void lcd_wr_data(volatile uint16_t data)
{
    data = data;            /* ʹ��-O2�Ż���ʱ��,����������ʱ */
    LCD->LCD_RAM = data;
}

/**
 * @brief       LCDд�Ĵ������/��ַ����
 * @param       regno: �Ĵ������/��ַ
 * @retval      ��
 */
void lcd_wr_regno(volatile uint16_t regno)
{
    regno = regno;          /* ʹ��-O2�Ż���ʱ��,����������ʱ */
    LCD->LCD_REG = regno;   /* д��Ҫд�ļĴ������ */
}

/**
 * @brief       LCDд�Ĵ���
 * @param       regno:�Ĵ������/��ַ
 * @param       data:Ҫд�������
 * @retval      ��
 */
void lcd_write_reg(uint16_t regno, uint16_t data)
{
    LCD->LCD_REG = regno;   /* д��Ҫд�ļĴ������ */
    LCD->LCD_RAM = data;    /* д������ */
}

/**
 * @brief       LCD��ʱ����,�����ڲ�����mdk -O1ʱ���Ż�ʱ��Ҫ���õĵط�
 * @param       t:��ʱ����ֵ
 * @retval      ��
 */
static void lcd_opt_delay(uint32_t i)
{
    while (i--); /* ʹ��AC6ʱ��ѭ�����ܱ��Ż�,��ʹ��while(1) __asm volatile(""); */
}

/**
 * @brief       LCD������
 * @param       ��
 * @retval      ��ȡ��������
 */
static uint16_t lcd_rd_data(void)
{
    volatile uint16_t ram;  /* ��ֹ���Ż� */
    lcd_opt_delay(2);
    ram = LCD->LCD_RAM;
    return ram;
}

/**
 * @brief       ׼��дGRAM
 * @param       ��
 * @retval      ��
 */
void lcd_write_ram_prepare(void)
{
    LCD->LCD_REG = lcddev.wramcmd;
}

/**
 * @brief       ��ȡ��ĳ�����ɫֵ
 * @param       x,y:����
 * @retval      �˵����ɫ(32λ��ɫ,�������LTDC)
 */
uint32_t lcd_read_point(uint16_t x, uint16_t y)
{
    uint16_t r = 0, g = 0, b = 0;

    if (x >= lcddev.width || y >= lcddev.height)
    {
        return 0;   /* �����˷�Χ,ֱ�ӷ��� */
    }

    lcd_set_cursor(x, y);       /* �������� */

    if (lcddev.id == 0x5510)
    {
        lcd_wr_regno(0x2E00);   /* 5510 ���Ͷ�GRAMָ�� */
    }
    else
    {
        lcd_wr_regno(0x2E);     /* 9341/5310/1963/7789/7796/9806 �ȷ��Ͷ�GRAMָ�� */
    }


    r = lcd_rd_data();          /* �ٶ�(dummy read) */

    if (lcddev.id == 0x1963)
    {
        return r;   /* 1963ֱ�Ӷ��Ϳ��� */
    }

    r = lcd_rd_data();          /* ʵ��������ɫ */

    if (lcddev.id == 0x7796)    /* 7796 һ�ζ�ȡһ������ֵ */
    {
        return r;
    }

    /* 9341/5310/5510/7789/9806Ҫ��2�ζ��� */
    b = lcd_rd_data();
    g = r & 0xFF;               /* ����9341/5310/5510/7789/9806,��һ�ζ�ȡ����RG��ֵ,R��ǰ,G�ں�,��ռ8λ */
    g <<= 8;

    return (((r >> 11) << 11) | ((g >> 10) << 5) | (b >> 11));  /* ILI9341/NT35310/NT35510/ST7789/ILI9806��Ҫ��ʽת��һ�� */
}

/**
 * @brief       LCD������ʾ
 * @param       ��
 * @retval      ��
 */
void lcd_display_on(void)
{
    if (lcddev.id == 0x5510)
    {
        lcd_wr_regno(0x2900);   /* ������ʾ */
    }
    else                        /* 9341/5310/1963/7789/7796/9806 �ȷ��Ϳ�����ʾָ�� */
    {
        lcd_wr_regno(0x29);     /* ������ʾ */
    }
}

/**
 * @brief       LCD�ر���ʾ
 * @param       ��
 * @retval      ��
 */
void lcd_display_off(void)
{
    if (lcddev.id == 0x5510)
    {
        lcd_wr_regno(0x2800);   /* �ر���ʾ */
    }
    else                        /* 9341/5310/1963/7789/7796/9806 �ȷ��͹ر���ʾָ�� */
    {
        lcd_wr_regno(0x28);     /* �ر���ʾ */
    }
}

/**
 * @brief       ���ù��λ��(��RGB����Ч)
 * @param       x,y: ����
 * @retval      ��
 */
void lcd_set_cursor(uint16_t x, uint16_t y)
{
    if (lcddev.id == 0x1963)
    {
        if (lcddev.dir == 0)    /* ����ģʽ, x������Ҫ�任 */
        {
            x = lcddev.width - 1 - x;
            lcd_wr_regno(lcddev.setxcmd);
            lcd_wr_data(0);
            lcd_wr_data(0);
            lcd_wr_data(x >> 8);
            lcd_wr_data(x & 0xFF);
        }
        else                    /* ����ģʽ */
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
    else    /* 9341/5310/7789/7796/9806 �� �������� */
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
 * @brief       ����LCD���Զ�ɨ�跽��(��RGB����Ч)
 *   @note
 *              9341/5310/5510/1963/7789/7796/9806��IC�Ѿ�ʵ�ʲ���
 *              ע��:�����������ܻ��ܵ��˺������õ�Ӱ��(������9341),
 *              ����,һ������ΪL2R_U2D����,�������Ϊ����ɨ�跽ʽ,���ܵ�����ʾ������.
 *
 * @param       dir:0~7,����8������(���嶨���lcd.h)
 * @retval      ��
 */
void lcd_scan_dir(uint8_t dir)
{
    uint16_t regval = 0;
    uint16_t dirreg = 0;
    uint16_t temp;

    /* ����ʱ����1963���ı�ɨ�跽������ʱ1963�ı䷽��(���������1963�����⴦��,����������IC��Ч) */
    if ((lcddev.dir == 1 && lcddev.id != 0x1963) || (lcddev.dir == 0 && lcddev.id == 0x1963))
    {
        switch (dir)   /* ����ת�� */
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


    /* ����ɨ�跽ʽ ���� 0x36/0x3600 �Ĵ��� bit 5,6,7 λ��ֵ */
    switch (dir)
    {
        case L2R_U2D:   /* ������,���ϵ��� */
            regval |= (0 << 7) | (0 << 6) | (0 << 5);
            break;

        case L2R_D2U:   /* ������,���µ��� */
            regval |= (1 << 7) | (0 << 6) | (0 << 5);
            break;

        case R2L_U2D:   /* ���ҵ���,���ϵ��� */
            regval |= (0 << 7) | (1 << 6) | (0 << 5);
            break;

        case R2L_D2U:   /* ���ҵ���,���µ��� */
            regval |= (1 << 7) | (1 << 6) | (0 << 5);
            break;

        case U2D_L2R:   /* ���ϵ���,������ */
            regval |= (0 << 7) | (0 << 6) | (1 << 5);
            break;

        case U2D_R2L:   /* ���ϵ���,���ҵ��� */
            regval |= (0 << 7) | (1 << 6) | (1 << 5);
            break;

        case D2U_L2R:   /* ���µ���,������ */
            regval |= (1 << 7) | (0 << 6) | (1 << 5);
            break;

        case D2U_R2L:   /* ���µ���,���ҵ��� */
            regval |= (1 << 7) | (1 << 6) | (1 << 5);
            break;
    }

    dirreg = 0x36;  /* �Ծ��󲿷�����IC, ��0x36�Ĵ������� */

    if (lcddev.id == 0x5510)
    {
        dirreg = 0x3600;    /* ����5510, ����������ic�ļĴ����в��� */
    }

     /* 9341 & 7789 & 7796 Ҫ����BGRλ */
    if (lcddev.id == 0x9341 || lcddev.id == 0x7789 || lcddev.id == 0x7796)
    {
        regval |= 0x08;
    }

    lcd_write_reg(dirreg, regval);

    if (lcddev.id != 0x1963)                    /* 1963�������괦�� */
    {
        if (regval & 0x20)
        {
            if (lcddev.width < lcddev.height)   /* ����X,Y */
            {
                temp = lcddev.width;
                lcddev.width = lcddev.height;
                lcddev.height = temp;
            }
        }
        else
        {
            if (lcddev.width > lcddev.height)   /* ����X,Y */
            {
                temp = lcddev.width;
                lcddev.width = lcddev.height;
                lcddev.height = temp;
            }
        }
    }

    /* ������ʾ����(����)��С */
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
 * @brief       ����
 * @param       x,y: ����
 * @param       color: �����ɫ(32λ��ɫ,�������LTDC)
 * @retval      ��
 */
void lcd_draw_point(uint16_t x, uint16_t y, uint32_t color)
{
    lcd_set_cursor(x, y);       /* ���ù��λ�� */
    lcd_write_ram_prepare();    /* ��ʼд��GRAM */
    LCD->LCD_RAM = color;
}

/**
 * @brief       SSD1963�����������ú���
 * @param       pwm: ����ȼ�,0~100.Խ��Խ��.
 * @retval      ��
 */
void lcd_ssd_backlight_set(uint8_t pwm)
{
    lcd_wr_regno(0xBE);         /* ����PWM��� */
    lcd_wr_data(0x05);          /* 1����PWMƵ�� */
    lcd_wr_data(pwm * 2.55);    /* 2����PWMռ�ձ� */
    lcd_wr_data(0x01);          /* 3����C */
    lcd_wr_data(0xFF);          /* 4����D */
    lcd_wr_data(0x00);          /* 5����E */
    lcd_wr_data(0x00);          /* 6����F */
}

/**
 * @brief       ����LCD��ʾ����
 * @param       dir:0,����; 1,����
 * @retval      ��
 */
void lcd_display_dir(uint8_t dir)
{
    lcddev.dir = dir;   /* ����/���� */

    if (dir == 0)       /* ���� */
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
            lcddev.wramcmd = 0x2C;  /* ����д��GRAM��ָ�� */
            lcddev.setxcmd = 0x2B;  /* ����дX����ָ�� */
            lcddev.setycmd = 0x2A;  /* ����дY����ָ�� */
            lcddev.width = 480;     /* ���ÿ��480 */
            lcddev.height = 800;    /* ���ø߶�800 */
        }
        else   /* ����IC, ����: 9341/5310/7789/7796/9806��IC */
        {
            lcddev.wramcmd = 0x2C;
            lcddev.setxcmd = 0x2A;
            lcddev.setycmd = 0x2B;
        }

        if (lcddev.id == 0x5310 || lcddev.id == 0x7796)     /* �����5310/7796 ���ʾ�� 320*480�ֱ��� */
        {
            lcddev.width = 320;
            lcddev.height = 480;
        }
        
        if (lcddev.id == 0X9806)    /* �����9806 ���ʾ�� 480*800 �ֱ��� */
        {
            lcddev.width = 480;
            lcddev.height = 800;
        }  
    }
    else        /* ���� */
    {
        lcddev.width = 320;         /* Ĭ�Ͽ�� */
        lcddev.height = 240;        /* Ĭ�ϸ߶� */

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
            lcddev.wramcmd = 0x2C;  /* ����д��GRAM��ָ�� */
            lcddev.setxcmd = 0x2A;  /* ����дX����ָ�� */
            lcddev.setycmd = 0x2B;  /* ����дY����ָ�� */
            lcddev.width = 800;     /* ���ÿ��800 */
            lcddev.height = 480;    /* ���ø߶�480 */
        }
        else   /* ����IC, ����:9341/5310/7789/7796��IC */
        {
            lcddev.wramcmd = 0x2C;
            lcddev.setxcmd = 0x2A;
            lcddev.setycmd = 0x2B;
        }

        if (lcddev.id == 0x5310 || lcddev.id == 0x7796)     /* �����5310/7796 ���ʾ�� 320*480�ֱ��� */
        {
            lcddev.width = 480;
            lcddev.height = 320;
        }
    }

    lcd_scan_dir(DFT_SCAN_DIR);     /* Ĭ��ɨ�跽�� */
}

/**
 * @brief       ��ʼ��LCD
 *   @note      �ó�ʼ���������Գ�ʼ�������ͺŵ�LCD(�����.c�ļ���ǰ�������)
 *
 * @param       ��
 * @retval      ��
 */
void lcd_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    FSMC_NORSRAM_TimingTypeDef fsmc_read_handle;
    FSMC_NORSRAM_TimingTypeDef fsmc_write_handle;

    LCD_CS_GPIO_CLK_ENABLE();   /* LCD_CS��ʱ��ʹ�� */
    LCD_WR_GPIO_CLK_ENABLE();   /* LCD_WR��ʱ��ʹ�� */
    LCD_RD_GPIO_CLK_ENABLE();   /* LCD_RD��ʱ��ʹ�� */
    LCD_RS_GPIO_CLK_ENABLE();   /* LCD_RS��ʱ��ʹ�� */
    LCD_BL_GPIO_CLK_ENABLE();   /* LCD_BL��ʱ��ʹ�� */
    
    gpio_init_struct.Pin = LCD_CS_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_AF_PP;                /* ���츴�� */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* ���� */
    gpio_init_struct.Alternate = GPIO_AF12_FSMC;            /* ����ΪFSMC */
    HAL_GPIO_Init(LCD_CS_GPIO_PORT, &gpio_init_struct);     /* ��ʼ��LCD_CS���� */

    gpio_init_struct.Pin = LCD_WR_GPIO_PIN;
    HAL_GPIO_Init(LCD_WR_GPIO_PORT, &gpio_init_struct);     /* ��ʼ��LCD_WR���� */

    gpio_init_struct.Pin = LCD_RD_GPIO_PIN;
    HAL_GPIO_Init(LCD_RD_GPIO_PORT, &gpio_init_struct);     /* ��ʼ��LCD_RD���� */

    gpio_init_struct.Pin = LCD_RS_GPIO_PIN;
    HAL_GPIO_Init(LCD_RS_GPIO_PORT, &gpio_init_struct);     /* ��ʼ��LCD_RS���� */

    gpio_init_struct.Pin = LCD_BL_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* ������� */
    HAL_GPIO_Init(LCD_BL_GPIO_PORT, &gpio_init_struct);     /* LCD_BL����ģʽ����(�������) */

    g_sram_handle.Instance = FSMC_NORSRAM_DEVICE;
    g_sram_handle.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
    
    g_sram_handle.Init.NSBank = FSMC_NORSRAM_BANK4;                        /* ʹ��NE4 */
    g_sram_handle.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;     /* ��ַ/�����߲����� */
    g_sram_handle.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;    /* 16λ���ݿ�� */
    g_sram_handle.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;   /* �Ƿ�ʹ��ͻ������,����ͬ��ͻ���洢����Ч,�˴�δ�õ� */
    g_sram_handle.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW; /* �ȴ��źŵļ���,����ͻ��ģʽ���������� */
    g_sram_handle.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;      /* �洢�����ڵȴ�����֮ǰ��һ��ʱ�����ڻ��ǵȴ������ڼ�ʹ��NWAIT */
    g_sram_handle.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;       /* �洢��дʹ�� */
    g_sram_handle.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;              /* �ȴ�ʹ��λ,�˴�δ�õ� */
    g_sram_handle.Init.ExtendedMode = FSMC_EXTENDED_MODE_ENABLE;           /* ��дʹ�ò�ͬ��ʱ�� */
    g_sram_handle.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;  /* �Ƿ�ʹ��ͬ������ģʽ�µĵȴ��ź�,�˴�δ�õ� */
    g_sram_handle.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;              /* ��ֹͻ��д */
    
    /* FSMC��ʱ����ƼĴ��� */
    fsmc_read_handle.AddressSetupTime = 0x0F;           /* ��ַ����ʱ��(ADDSET)Ϊ15��fsmc_ker_ck(1/168=6)��6*15=90ns */
    fsmc_read_handle.AddressHoldTime = 0x00;            /* ��ַ����ʱ��(ADDHLD) ģʽA��û���õ� */
    fsmc_read_handle.DataSetupTime = 60;                /* ���ݱ���ʱ��(DATAST)Ϊ60��fsmc_ker_ck=6*60=360ns */
                                                        /* ��ΪҺ������IC�Ķ����ݵ�ʱ��,�ٶȲ���̫��,�����Ǹ�������оƬ */
    fsmc_read_handle.AccessMode = FSMC_ACCESS_MODE_A;   /* ģʽA */
    
    /* FSMCдʱ����ƼĴ��� */
    fsmc_write_handle.AddressSetupTime = 9;             /* ��ַ����ʱ��(ADDSET)Ϊ9��fsmc_ker_ck=6*9=54ns */
    fsmc_write_handle.AddressHoldTime = 0x00;           /* ��ַ����ʱ��(ADDHLD) ģʽA��û���õ� */
    fsmc_write_handle.DataSetupTime = 9;                /* ���ݱ���ʱ��(DATAST)Ϊ9��fsmc_ker_ck=6*9=54ns */
                                                        /* ע�⣺ĳЩҺ������IC��д�ź���������Ҳ��50ns */
    fsmc_write_handle.AccessMode = FSMC_ACCESS_MODE_A;  /* ģʽA */
    
    HAL_SRAM_Init(&g_sram_handle, &fsmc_read_handle, &fsmc_write_handle);
    HAL_Delay(50);

    /* ����9341 ID�Ķ�ȡ */
    lcd_wr_regno(0xD3);
    lcddev.id = lcd_rd_data();  /* dummy read */
    lcddev.id = lcd_rd_data();  /* ����0x00 */
    lcddev.id = lcd_rd_data();  /* ��ȡ93 */
    lcddev.id <<= 8;
    lcddev.id |= lcd_rd_data(); /* ��ȡ41 */

    lcd_ex_ili9341_reginit();

    fsmc_write_handle.AddressSetupTime = 2; /* ��ַ����ʱ��(ADDSET)Ϊ2��fsmc_ker_ck=6*2=12ns */
    fsmc_write_handle.DataSetupTime = 2;    /* ���ݱ���ʱ��(DATAST)Ϊ2��fsmc_ker_ck=6*2=12ns */
    FSMC_NORSRAM_Extended_Timing_Init(g_sram_handle.Extended, &fsmc_write_handle, g_sram_handle.Init.NSBank, g_sram_handle.Init.ExtendedMode);
    lcd_display_dir(0); /* Ĭ��Ϊ���� */
    LCD_BL(1);          /* �������� */
}

/**
 * @brief       ��ָ����������䵥����ɫ
 * @param       (sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex - sx + 1) * (ey - sy + 1)
 * @param       color:  Ҫ������ɫ(32λ��ɫ,�������LTDC)
 * @retval      ��
 */
void lcd_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint32_t color)
{
    uint16_t i, j;
    uint16_t xlen = 0;
    xlen = ex - sx + 1;

    for (i = sy; i <= ey; i++)
    {
        lcd_set_cursor(sx, i);      /* ���ù��λ�� */
        lcd_write_ram_prepare();    /* ��ʼд��GRAM */

        for (j = 0; j < xlen; j++)
        {
            LCD->LCD_RAM = color;   /* ��ʾ��ɫ */
        }
    }
}

/**
 * @brief       ��ָ�����������ָ����ɫ��
 * @param       (sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex - sx + 1) * (ey - sy + 1)
 * @param       color: Ҫ������ɫ�����׵�ַ
 * @retval      ��
 */
void lcd_color_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t *color)
{
    uint16_t height, width;
    uint16_t i, j;

    width = ex - sx + 1;            /* �õ����Ŀ�� */
    height = ey - sy + 1;           /* �߶� */

    for (i = 0; i < height; i++)
    {
        lcd_set_cursor(sx, sy + i); /* ���ù��λ�� */
        lcd_write_ram_prepare();    /* ��ʼд��GRAM */

        for (j = 0; j < width; j++)
        {
            LCD->LCD_RAM = color[i * width + j]; /* д������ */
        }
    }
}
