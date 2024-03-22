/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"

#include "esp_log.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"

EventGroupHandle_t xCreatedEventGroup;
#define BIT_0 (1 << 0)
#define BIT_1 (1 << 1)
#define BIT_2 (1 << 2)
#define ALL_SYNC_TASKS_BIT (BIT_0 | BIT_1 | BIT_2 )



void task0(void *pvParam)
{

    while (1)
    {
        printf("task0 : \n");
        vTaskDelay(pdMS_TO_TICKS(1000));
        printf("task0 :set  bit0\n");
        xEventGroupSync(
            xCreatedEventGroup, /* The event group being tested. */
            BIT_0 ,      /* The bits within the event group to wait for. */
            ALL_SYNC_TASKS_BIT,             /* BIT_0 and BIT_4 should be cleared before returning. */
            portMAX_DELAY);     /* Wait a maximum of 100ms for either bit to be set. */
        printf("ALL_SYNC_TASKS_BIT,task0\n");
        vTaskDelay(pdMS_TO_TICKS(10000));
    }

}
void task1(void *pvParam)
{

    while (1)
    {
        printf("task1 : \n");
        vTaskDelay(pdMS_TO_TICKS(3000));
        printf("task1 :set  bit1\n");
        xEventGroupSync(
            xCreatedEventGroup, /* The event group being tested. */
            BIT_1,      /* The bits within the event group to wait for. */
            ALL_SYNC_TASKS_BIT,             /* BIT_0 and BIT_4 should be cleared before returning. */
            portMAX_DELAY);     /* Wait a maximum of 100ms for either bit to be set. */
        printf("ALL_SYNC_TASKS_BIT,task1\n");
        vTaskDelay(pdMS_TO_TICKS(10000));
    }

}
void task2(void *pvParam)
{

    while (1)
    {
        printf("task2 : \n");
        vTaskDelay(pdMS_TO_TICKS(5000));
        printf("task2 :set  bit2\n");
        xEventGroupSync(
            xCreatedEventGroup, /* The event group being tested. */
            BIT_2,      /* The bits within the event group to wait for. */
            ALL_SYNC_TASKS_BIT,             /* BIT_0 and BIT_4 should be cleared before returning. */
            portMAX_DELAY);     /* Wait a maximum of 100ms for either bit to be set. */
        printf("ALL_SYNC_TASKS_BIT,task2\n");
        vTaskDelay(pdMS_TO_TICKS(10000));
    }

}
void app_main(void)
{
    xCreatedEventGroup = xEventGroupCreate();
    /* Was the event group created successfully? */
    if (xCreatedEventGroup == NULL)
    {
        printf("xCreatedEventGroup fail\n");
    }
    else
    {
        vTaskSuspendAll();
        xTaskCreate(task0, "Task1", 2048 * 5, NULL, 1, NULL);
        xTaskCreate(task1, "Task2", 2048 * 5, NULL, 1, NULL);
        xTaskCreate(task2, "Task2", 2048 * 5, NULL, 1, NULL);
        xTaskResumeAll();
    }
    // xSemaphoreGive(xSemaphore);

    while (1)
    {
        // printf("car_num: %d\n", uxSemaphoreGetCount(xSemaphore));
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
