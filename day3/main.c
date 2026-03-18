#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED1_PIN  GPIO_NUM_2
#define LED2_PIN  GPIO_NUM_4
#define LED3_PIN  GPIO_NUM_5

void task_low(void *pvParameters)
{
    gpio_reset_pin(LED1_PIN);
    gpio_set_direction(LED1_PIN, GPIO_MODE_OUTPUT);
    while(1)
    {
        gpio_set_level(LED1_PIN, 1);
        printf("[LOW]    LED1 ON  — Priority 1\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
        gpio_set_level(LED1_PIN, 0);
        printf("[LOW]    LED1 OFF — Priority 1\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void task_medium(void *pvParameters)
{
    gpio_reset_pin(LED2_PIN);
    gpio_set_direction(LED2_PIN, GPIO_MODE_OUTPUT);
    while(1)
    {
        gpio_set_level(LED2_PIN, 1);
        printf("[MEDIUM] LED2 ON  — Priority 2\n");
        vTaskDelay(pdMS_TO_TICKS(500));
        gpio_set_level(LED2_PIN, 0);
        printf("[MEDIUM] LED2 OFF — Priority 2\n");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void task_high(void *pvParameters)
{
    gpio_reset_pin(LED3_PIN);
    gpio_set_direction(LED3_PIN, GPIO_MODE_OUTPUT);
    while(1)
    {
        gpio_set_level(LED3_PIN, 1);
        printf("[HIGH]   LED3 ON  — Priority 3\n");
        vTaskDelay(pdMS_TO_TICKS(200));
        gpio_set_level(LED3_PIN, 0);
        printf("[HIGH]   LED3 OFF — Priority 3\n");
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

void app_main(void)
{
    printf("=== FreeRTOS Priority Demo ===\n");
    xTaskCreate(task_low,    "Low Task",    2048, NULL, 1, NULL);
    xTaskCreate(task_medium, "Medium Task", 2048, NULL, 2, NULL);
    xTaskCreate(task_high,   "High Task",   2048, NULL, 3, NULL);
    while(1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}