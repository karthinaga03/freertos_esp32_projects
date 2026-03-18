#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

<<<<<<< HEAD
#define LED1_PIN  GPIO_NUM_2
#define LED2_PIN  GPIO_NUM_4

// ─────────────────────────────
// Task 1 — LED 1 — Slow blink
// ─────────────────────────────
void task1_led(void *pvParameters)
=======
#define LED1_PIN  GPIO_NUM_2    // LOW priority
#define LED2_PIN  GPIO_NUM_4    // MEDIUM priority
#define LED3_PIN  GPIO_NUM_5    // HIGH priority

// ─────────────────────────────
// Task 1 — LOW Priority (1)
// ─────────────────────────────
void task_low(void *pvParameters)
>>>>>>> 7d73455 (day 3 freertos task priorities)
{
    gpio_reset_pin(LED1_PIN);
    gpio_set_direction(LED1_PIN, GPIO_MODE_OUTPUT);

    while(1)
    {
        gpio_set_level(LED1_PIN, 1);
<<<<<<< HEAD
        printf("LED1 ON\n");                  // Serial print
        vTaskDelay(pdMS_TO_TICKS(500));

        gpio_set_level(LED1_PIN, 0);
        printf("LED1 OFF\n");                 // Serial print
        vTaskDelay(pdMS_TO_TICKS(500));
=======
        printf("[LOW]    LED1 ON  — Priority 1\n");
        vTaskDelay(pdMS_TO_TICKS(1000));

        gpio_set_level(LED1_PIN, 0);
        printf("[LOW]    LED1 OFF — Priority 1\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
>>>>>>> 7d73455 (day 3 freertos task priorities)
    }
}

// ─────────────────────────────
<<<<<<< HEAD
// Task 2 — LED 2 — Fast blink
// ─────────────────────────────
void task2_led(void *pvParameters)
=======
// Task 2 — MEDIUM Priority (2)
// ─────────────────────────────
void task_medium(void *pvParameters)
>>>>>>> 7d73455 (day 3 freertos task priorities)
{
    gpio_reset_pin(LED2_PIN);
    gpio_set_direction(LED2_PIN, GPIO_MODE_OUTPUT);

    while(1)
    {
        gpio_set_level(LED2_PIN, 1);
<<<<<<< HEAD
        printf("LED2 ON\n");                  // Serial print
        vTaskDelay(pdMS_TO_TICKS(200));

        gpio_set_level(LED2_PIN, 0);
        printf("LED2 OFF\n");                 // Serial print
=======
        printf("[MEDIUM] LED2 ON  — Priority 2\n");
        vTaskDelay(pdMS_TO_TICKS(500));

        gpio_set_level(LED2_PIN, 0);
        printf("[MEDIUM] LED2 OFF — Priority 2\n");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

// ─────────────────────────────
// Task 3 — HIGH Priority (3)
// ─────────────────────────────
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
>>>>>>> 7d73455 (day 3 freertos task priorities)
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

// ─────────────────────────────
// Main Function
// ─────────────────────────────
void app_main(void)
{
<<<<<<< HEAD
    printf("FreeRTOS Task Demo Starting...\n");

    xTaskCreate(task1_led, "LED Task 1", 2048, NULL, 1, NULL);
    xTaskCreate(task2_led, "LED Task 2", 2048, NULL, 1, NULL);
        while(1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
=======
    printf("=== FreeRTOS Priority Demo ===\n");
    xTaskCreate(task_low,    "Low Task",    2048, NULL, 1, NULL);
    xTaskCreate(task_medium, "Medium Task", 2048, NULL, 2, NULL);
    xTaskCreate(task_high,   "High Task",   2048, NULL, 3, NULL);

    while(1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
>>>>>>> 7d73455 (day 3 freertos task priorities)
