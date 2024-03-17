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


SemaphoreHandle_t xSemaphore = NULL;


void carinTask(void *pvParam)
{
    int car_num = 5;
    BaseType_t xStatus;
    while (1)
    {
        car_num = uxSemaphoreGetCount(xSemaphore);
        printf("car_num: %d\n", car_num);
        // ESP_LOGI("myTask1:", "waiting for semaphore");
        xStatus = xSemaphoreTake(xSemaphore, 0);
        if (xStatus == pdTRUE)
            printf("car in\n");
        else
            printf("car in failed\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
void carouTask(void *pvParam)
{

    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(6000));
        xSemaphoreGive(xSemaphore);
        printf("car out\n");
        // ESP_LOGI("myTask2:", "waiting for semaphore");
    }
}

void app_main(void)
{
    xSemaphore = xSemaphoreCreateCounting(5, 5);
    xSemaphoreGive(xSemaphore);
    xTaskCreate(carinTask, "Task1", 2048*5, NULL, 1, NULL);
    xTaskCreate(carouTask, "Task2", 2048*5, NULL, 1, NULL);
    while (1)
    {
        printf("car_num: %d\n", uxSemaphoreGetCount(xSemaphore));
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
