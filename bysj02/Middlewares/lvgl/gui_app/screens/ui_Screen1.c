// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: SquareLine_Project

#include "../ui.h"

void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_flex_flow(ui_Screen1, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_Screen1, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);

    ui_Container13 = lv_obj_create(ui_Screen1);
    lv_obj_remove_style_all(ui_Container13);
    lv_obj_set_width(ui_Container13, 237);
    lv_obj_set_height(ui_Container13, 20);
    lv_obj_set_align(ui_Container13, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Container13, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label4 = lv_label_create(ui_Container13);
    lv_obj_set_width(ui_Label4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label4, "control information");

    ui_Container8 = lv_obj_create(ui_Screen1);
    lv_obj_remove_style_all(ui_Container8);
    lv_obj_set_width(ui_Container8, 240);
    lv_obj_set_height(ui_Container8, 220);
    lv_obj_set_align(ui_Container8, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_Container8, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_Container8, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
    lv_obj_clear_flag(ui_Container8, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Container2 = lv_obj_create(ui_Container8);
    lv_obj_remove_style_all(ui_Container2);
    lv_obj_set_width(ui_Container2, 60);
    lv_obj_set_height(ui_Container2, 220);
    lv_obj_set_align(ui_Container2, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_Container2, LV_FLEX_FLOW_COLUMN_WRAP);
    lv_obj_set_flex_align(ui_Container2, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_SPACE_BETWEEN);
    lv_obj_clear_flag(ui_Container2, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Container5 = lv_obj_create(ui_Container2);
    lv_obj_remove_style_all(ui_Container5);
    lv_obj_set_width(ui_Container5, 50);
    lv_obj_set_height(ui_Container5, 50);
    lv_obj_set_x(ui_Container5, -5);
    lv_obj_set_y(ui_Container5, -101);
    lv_obj_clear_flag(ui_Container5, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Container5, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Container5, lv_color_hex(0xF8C943), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Container5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelSpeedLeftFront = lv_label_create(ui_Container5);
    lv_obj_set_width(ui_LabelSpeedLeftFront, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelSpeedLeftFront, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelSpeedLeftFront, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelSpeedLeftFront, "0");

    ui_Container10 = lv_obj_create(ui_Container2);
    lv_obj_remove_style_all(ui_Container10);
    lv_obj_set_width(ui_Container10, 50);
    lv_obj_set_height(ui_Container10, 50);
    lv_obj_set_align(ui_Container10, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Container10, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Container10, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Container10, lv_color_hex(0xA3C8FB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Container10, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelDistanceLeft = lv_label_create(ui_Container10);
    lv_obj_set_width(ui_LabelDistanceLeft, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelDistanceLeft, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelDistanceLeft, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelDistanceLeft, "0");

    ui_Container4 = lv_obj_create(ui_Container2);
    lv_obj_remove_style_all(ui_Container4);
    lv_obj_set_width(ui_Container4, 50);
    lv_obj_set_height(ui_Container4, 50);
    lv_obj_set_align(ui_Container4, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Container4, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Container4, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Container4, lv_color_hex(0xF8C943), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Container4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelSpeedLeftBack = lv_label_create(ui_Container4);
    lv_obj_set_width(ui_LabelSpeedLeftBack, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelSpeedLeftBack, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelSpeedLeftBack, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelSpeedLeftBack, "0");

    ui_Container9 = lv_obj_create(ui_Container8);
    lv_obj_remove_style_all(ui_Container9);
    lv_obj_set_width(ui_Container9, 120);
    lv_obj_set_height(ui_Container9, 220);
    lv_obj_set_align(ui_Container9, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_Container9, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_Container9, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_AROUND);
    lv_obj_clear_flag(ui_Container9, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Container9, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Container14 = lv_obj_create(ui_Container9);
    lv_obj_remove_style_all(ui_Container14);
    lv_obj_set_width(ui_Container14, 50);
    lv_obj_set_height(ui_Container14, 50);
    lv_obj_set_align(ui_Container14, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Container14, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Container14, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Container14, lv_color_hex(0xA3C8FB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Container14, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelDistanceFront = lv_label_create(ui_Container14);
    lv_obj_set_width(ui_LabelDistanceFront, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelDistanceFront, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelDistanceFront, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelDistanceFront, "0");

    ui_Container11 = lv_obj_create(ui_Container9);
    lv_obj_remove_style_all(ui_Container11);
    lv_obj_set_width(ui_Container11, 100);
    lv_obj_set_height(ui_Container11, 100);
    lv_obj_set_align(ui_Container11, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Container11, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Container11, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Container11, lv_color_hex(0xEDCF8C), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Container11, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Container15 = lv_obj_create(ui_Container9);
    lv_obj_remove_style_all(ui_Container15);
    lv_obj_set_width(ui_Container15, 50);
    lv_obj_set_height(ui_Container15, 50);
    lv_obj_set_align(ui_Container15, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Container15, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Container15, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Container15, lv_color_hex(0xA3C8FB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Container15, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelDistanceBack = lv_label_create(ui_Container15);
    lv_obj_set_width(ui_LabelDistanceBack, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelDistanceBack, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelDistanceBack, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelDistanceBack, "0");

    ui_Container3 = lv_obj_create(ui_Container8);
    lv_obj_remove_style_all(ui_Container3);
    lv_obj_set_width(ui_Container3, 60);
    lv_obj_set_height(ui_Container3, 220);
    lv_obj_set_align(ui_Container3, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_Container3, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_Container3, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_AROUND);
    lv_obj_clear_flag(ui_Container3, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Container6 = lv_obj_create(ui_Container3);
    lv_obj_remove_style_all(ui_Container6);
    lv_obj_set_width(ui_Container6, 50);
    lv_obj_set_height(ui_Container6, 50);
    lv_obj_set_align(ui_Container6, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Container6, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Container6, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Container6, lv_color_hex(0xF8C943), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Container6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelSpeedRightFront = lv_label_create(ui_Container6);
    lv_obj_set_width(ui_LabelSpeedRightFront, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelSpeedRightFront, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelSpeedRightFront, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelSpeedRightFront, "0");

    ui_Container12 = lv_obj_create(ui_Container3);
    lv_obj_remove_style_all(ui_Container12);
    lv_obj_set_width(ui_Container12, 50);
    lv_obj_set_height(ui_Container12, 50);
    lv_obj_set_align(ui_Container12, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Container12, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Container12, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Container12, lv_color_hex(0xA3C8FB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Container12, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelDistanceRight = lv_label_create(ui_Container12);
    lv_obj_set_width(ui_LabelDistanceRight, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelDistanceRight, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelDistanceRight, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelDistanceRight, "0");

    ui_Container7 = lv_obj_create(ui_Container3);
    lv_obj_remove_style_all(ui_Container7);
    lv_obj_set_width(ui_Container7, 50);
    lv_obj_set_height(ui_Container7, 50);
    lv_obj_set_align(ui_Container7, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Container7, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Container7, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Container7, lv_color_hex(0xF8C943), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Container7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelSpeedRightBack = lv_label_create(ui_Container7);
    lv_obj_set_width(ui_LabelSpeedRightBack, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelSpeedRightBack, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelSpeedRightBack, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelSpeedRightBack, "0");

    ui_Container1 = lv_obj_create(ui_Screen1);
    lv_obj_remove_style_all(ui_Container1);
    lv_obj_set_width(ui_Container1, 240);
    lv_obj_set_height(ui_Container1, 60);
    lv_obj_set_align(ui_Container1, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_Container1, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_Container1, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_AROUND);
    lv_obj_clear_flag(ui_Container1, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label1 = lv_label_create(ui_Container1);
    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label1, "0");

    ui_Label2 = lv_label_create(ui_Container1);
    lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label2, "0");

    ui_Label3 = lv_label_create(ui_Container1);
    lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label3, "0");

}