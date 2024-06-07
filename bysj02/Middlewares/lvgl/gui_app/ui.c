// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: SquareLine_Project

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////


// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
lv_obj_t * ui_Screen1;
lv_obj_t * ui_Container13;
lv_obj_t * ui_Label4;
lv_obj_t * ui_Container8;
lv_obj_t * ui_Container2;
lv_obj_t * ui_Container5;
lv_obj_t * ui_LabelSpeedLeftFront;
lv_obj_t * ui_Container10;
lv_obj_t * ui_LabelDistanceLeft;
lv_obj_t * ui_Container4;
lv_obj_t * ui_LabelSpeedLeftBack;
lv_obj_t * ui_Container9;
lv_obj_t * ui_Container14;
lv_obj_t * ui_LabelDistanceFront;
lv_obj_t * ui_Container11;
lv_obj_t * ui_Container15;
lv_obj_t * ui_LabelDistanceBack;
lv_obj_t * ui_Container3;
lv_obj_t * ui_Container6;
lv_obj_t * ui_LabelSpeedRightFront;
lv_obj_t * ui_Container12;
lv_obj_t * ui_LabelDistanceRight;
lv_obj_t * ui_Container7;
lv_obj_t * ui_LabelSpeedRightBack;
lv_obj_t * ui_Container1;
lv_obj_t * ui_Label1;
lv_obj_t * ui_Label2;
lv_obj_t * ui_Label3;
lv_obj_t * ui____initial_actions0;
const lv_img_dsc_t * ui_imgset_ellipse_[1] = {&ui_img_ellipse_1_png};
const lv_img_dsc_t * ui_imgset_rectangle_[15] = {&ui_img_rectangle_1_png, &ui_img_rectangle_10_png, &ui_img_rectangle_11_png, &ui_img_rectangle_12_png, &ui_img_rectangle_2_png, &ui_img_rectangle_13_png, &ui_img_rectangle_3_png, &ui_img_rectangle_14_png, &ui_img_rectangle_15_png, &ui_img_rectangle_5_png, &ui_img_rectangle_16_png, &ui_img_rectangle_6_png, &ui_img_rectangle_7_png, &ui_img_rectangle_8_png, &ui_img_rectangle_9_png};

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    LV_EVENT_GET_COMP_CHILD = lv_event_register_id();

    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_Screen1);
}