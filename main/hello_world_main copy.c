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


void Task1(void *pvParm)
{    
    BaseType_t iret;
    while (true)
    {
        printf("Task1\n");
        iret =  xSemaphoreTake(xSemaphore, 1000);
        if (iret == pdPASS)
        {
            printf("Task1 take \n");
            for (int  i = 0; i < 50; i++)
            {
                printf("Task1: %d\n", i);
                vTaskDelay(1000 / portTICK_PERIOD_MS);
            }
            xSemaphoreGive(xSemaphore);
            printf("Task1 give \n");
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
        else
        {
            printf("Task1 take semaphore fail\n");
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }
    
}

void Task2(void *pvParm)
{
    printf("Task2\n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    while (1)
    {
        ;
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    
}

void Task3(void *pvParm)
{
    BaseType_t iret;
    printf("Task3\n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    while (1)
    {
        iret =  xSemaphoreTake(xSemaphore, 1000);
        if (iret == pdPASS)
        {
            printf("Task3 take semaphore\n");
            for (int  i = 0; i < 10; i++)
            {
                printf("Task3: %d\n", i);
                vTaskDelay(1000 / portTICK_PERIOD_MS);
            }
            xSemaphoreGive(xSemaphore);
            printf("Task3 give \n");
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
        else
        {
            printf("Task3 take semaphore fail\n");
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
        
    }
    
}


void app_main(void)
{
    xSemaphore = xSemaphoreCreateMutex();
    vTaskSuspendAll();
    xTaskCreate(Task1, "Task1", 2048*5, NULL, 1, NULL);
    xTaskCreate(Task2, "Task2", 2048*5, NULL, 2, NULL);
    xTaskCreate(Task3, "Task3", 2048*5, NULL, 3, NULL);
    xTaskResumeAll();
    // while (1)
    // {
    //     printf("car_num: %d\n", uxSemaphoreGetCount(xSemaphore));
    //     vTaskDelay(1000 / portTICK_PERIOD_MS);
    // }
}
