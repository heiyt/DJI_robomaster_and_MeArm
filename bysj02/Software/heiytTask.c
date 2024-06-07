//
// Created by heiyt_R9000P on 2024/4/9.
//

#include "heiytTask.h"
#include "motor_run.h"
#include "weight.h"


#define DISTANCE_MIN 10

//左边是x正方向，前面是y正方向
int16_t Wx = 0, Wy = 0;
//角度从0-360，不能为负数
int16_t angle = 0, speed_A = 0, speed_M = 0;
char run = 0, fx = 0;
bool zhangai = false;

bool celiang = false;
uint32_t weight;
uint8_t send_buffer[5];

extern osTimerId_t floorRunTimerHandle;

void StartlvglTask(void *argument)
{
    /* USER CODE BEGIN StartlvglTask */
    /* Infinite loop */
    for(;;)
    {
        lv_timer_handler();
        osDelay(10);
    }
    /* USER CODE END StartlvglTask */
}

void StartFloorRunTask(void *argument)
{
    /* USER CODE BEGIN StartFloorRunTask */
    int16_t time;
    uint8_t dis_send = 0x08;
    int send_za = 0;
    /* Infinite loop */
    for(;;)
    {
        zhangai = false;
        if (distance1 < DISTANCE_MIN) {
            if (Wy > 0) {
                zhangai = true;
            }
        }
        if (distance2 < DISTANCE_MIN) {
            if (Wy < 0) {
                zhangai = true;
            }
        }
        if (distance3 < DISTANCE_MIN) {
            if (Wx < 0) {
                zhangai = true;
            }
        }
        if (distance4 < DISTANCE_MIN) {
            if (Wx > 0) {
                zhangai = true;
            }
        }
        if (zhangai) {
            floor_stop();
            if (send_za == 0) {
                send_za = 1;
            }
        } else {
            send_za = 0;
            if (run == 1) {
                floor_run(Wx, Wy);
            }
            if (run == 2) {
                time = floor_rotate(angle, speed_A);
                osTimerStart(floorRunTimerHandle, pdMS_TO_TICKS(time));
                run = 4;
            }
            if (run == 3) {
                floor_rotate_M(fx, speed_M);
            }
            if (run == 4) {
                floor_stop();
            }
        }
        if (send_za == 1) {
            HAL_UART_Transmit_IT(&huart3, &dis_send, 8);
            send_za = 2;
        }
        osDelay(10);
    }
    /* USER CODE END StartFloorRunTask */
}

void StartArmRunTask(void *argument)
{
    /* USER CODE BEGIN StartArmRunTask */
    /* Infinite loop */
    for(;;)
    {
        arm_x = arm_x_buff;
        arm_y = arm_y_buff;
        arm_z = arm_z_buff;
        arm_move_to((double)arm_x, (double)arm_y, (double)arm_z);
        guanjie1(gj1_angle);
        guanjie2(gj2_angle);
        guanjie3(gj3_angle);
        guanjie4(gj4_angle);
        osDelay(50);
    }
    /* USER CODE END StartArmRunTask */
}

void StartDistanceTask(void *argument)
{
    /* USER CODE BEGIN StartGetdistanceTask */
    /* Infinite loop */
    for(;;)
    {
        distance1 = getDistance1();
        distance2 = getDistance2();
        distance3 = getDistance3();
        distance4 = getDistance4();
        osDelay(100);
    }
    /* USER CODE END StartGetdistanceTask */
}

void StartUpdatelvglTask(void *argument)
{
    /* USER CODE BEGIN StartUpdatelvglTask */
    /* Infinite loop */
    for(;;)
    {
        lv_label_set_text_fmt(ui_LabelSpeedRightFront, "%d", wheel_speed[0]);
        lv_label_set_text_fmt(ui_LabelSpeedLeftFront, "%d", wheel_speed[1]);
        lv_label_set_text_fmt(ui_LabelSpeedLeftBack, "%d", wheel_speed[2]);
        lv_label_set_text_fmt(ui_LabelSpeedRightBack, "%d", wheel_speed[3]);
        lv_label_set_text_fmt(ui_LabelDistanceFront, "%.1f", distance1);
        lv_label_set_text_fmt(ui_LabelDistanceBack, "%.1f", distance2);
        lv_label_set_text_fmt(ui_LabelDistanceLeft, "%.1f", distance4);
        lv_label_set_text_fmt(ui_LabelDistanceRight, "%.1f", distance3);
        lv_label_set_text_fmt(ui_Label1, "%d", arm_x);
        lv_label_set_text_fmt(ui_Label2, "%d", arm_y);
        lv_label_set_text_fmt(ui_Label3, "%d", arm_z);
        osDelay(200);
    }
    /* USER CODE END StartUpdatelvglTask */
}

void getWeight(uint32_t *list) {
    for (int i = 0; i < 15; i++) {
        list[i] = ReadCount();
        osDelay(20);
    }
}
void GetWeightTask(void *argument)
{
    /* USER CODE BEGIN StartWeightTask */
    /* Infinite loop */
    for (;;) {
        if (celiang) {
            celiang = false;
//            getWeight(weight_list);
//            BubbleSort(weight_list);
            weight = ReadCount() / 107 - 478 - 2816 - 147;
            send_buffer[0] = 0x02;
            send_buffer[1] = weight / 16777216;
            send_buffer[2] = weight / 65536 % 256;
            send_buffer[3] = weight / 256 % 256;
            send_buffer[4] = weight % 256;
            HAL_UART_Transmit_IT(&huart3, send_buffer, 8);
        }
        osDelay(500);
    }
    /* USER CODE END StartWeightTask */
}

void floorRunTimerCallback(void *argument)
{
    /* USER CODE BEGIN floorRunTimerCallback */
    run = 4;
    osTimerStop(floorRunTimerHandle);
    /* USER CODE END floorRunTimerCallback */
}
void floorTimerCallback(void *argument)
{
    /* USER CODE BEGIN floorTimerCallback */
    HAL_UART_Transmit_IT(&huart2, Speed0_TABLE, 22);
    HAL_UART_Transmit_IT(&huart2, Speed1_TABLE, 22);
    HAL_UART_Transmit_IT(&huart2, Speed2_TABLE, 22);
    HAL_UART_Transmit_IT(&huart2, Speed3_TABLE, 22);
    /* USER CODE END floorTimerCallback */
}
