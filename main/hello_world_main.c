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
#define BIT_4 (1 << 4)
void task1(void *pvParam)
{
    while (1)
    {

        xEventGroupWaitBits(
            xCreatedEventGroup, /* The event group being tested. */
            BIT_0 | BIT_4,      /* The bits within the event group to wait for. */
            pdTRUE,             /* BIT_0 and BIT_4 should be cleared before returning. */
            pdTRUE,            /* Don't wait for both bits, either bit will do. */
            portMAX_DELAY);     /* Wait a maximum of 100ms for either bit to be set. */
        printf("task1 : bit0,bit4\n");
        // vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
void task2(void *pvParam)
{
    vTaskDelay(pdMS_TO_TICKS(1000));

    while (1)
    {
        printf("task2 : set bit0\n");
        xEventGroupSetBits(xCreatedEventGroup, BIT_0);
        vTaskDelay(pdMS_TO_TICKS(5000));
        printf("task2 : set bit4\n");
        xEventGroupSetBits(xCreatedEventGroup, BIT_4);
        vTaskDelay(pdMS_TO_TICKS(5000));
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
        xTaskCreate(task1, "Task1", 2048 * 5, NULL, 1, NULL);
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
