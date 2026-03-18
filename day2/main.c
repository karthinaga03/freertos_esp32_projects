#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED1_PIN  GPIO_NUM_2
#define LED2_PIN  GPIO_NUM_4

// ─────────────────────────────
// Task 1 — LED 1 — Slow blink
// ─────────────────────────────
void task1_led(void *pvParameters)
{
    gpio_reset_pin(LED1_PIN);
    gpio_set_direction(LED1_PIN, GPIO_MODE_OUTPUT);

    while(1)
    {
        gpio_set_level(LED1_PIN, 1);
        printf("LED1 ON\n");                  // Serial print
        vTaskDelay(pdMS_TO_TICKS(500));

        gpio_set_level(LED1_PIN, 0);
        printf("LED1 OFF\n");                 // Serial print
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

// ─────────────────────────────
// Task 2 — LED 2 — Fast blink
// ─────────────────────────────
void task2_led(void *pvParameters)
{
    gpio_reset_pin(LED2_PIN);
    gpio_set_direction(LED2_PIN, GPIO_MODE_OUTPUT);

    while(1)
    {
        gpio_set_level(LED2_PIN, 1);
        printf("LED2 ON\n");                  // Serial print
        vTaskDelay(pdMS_TO_TICKS(200));

        gpio_set_level(LED2_PIN, 0);
        printf("LED2 OFF\n");                 // Serial print
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

// ─────────────────────────────
// Main Function
// ─────────────────────────────
void app_main(void)
{
    printf("FreeRTOS Task Demo Starting...\n");

    xTaskCreate(task1_led, "LED Task 1", 2048, NULL, 1, NULL);
    xTaskCreate(task2_led, "LED Task 2", 2048, NULL, 1, NULL);
        while(1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
