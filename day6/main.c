#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"

#define LED_PIN GPIO_NUM_2

// Semaphore Handle
SemaphoreHandle_t xSemaphore;

// ─────────────────────────────
// Task 1 — Signal குடுக்கும்
// ─────────────────────────────
void giver_task(void *pvParameters)
{
    while(1)
    {
        vTaskDelay(pdMS_TO_TICKS(2000));

        // Signal குடு!
        xSemaphoreGive(xSemaphore);
        printf("[GIVER]  Signal குடுத்தேன்! ✅\n");
    }
}

// ─────────────────────────────
// Task 2 — Signal-க்கு காத்திருக்கும்
// ─────────────────────────────
void taker_task(void *pvParameters)
{
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    while(1)
    {
        printf("[TAKER]  Signal-க்கு காத்திருக்கேன்...\n");

        // Signal வரும்வரை காத்திரு!
        if(xSemaphoreTake(xSemaphore,
            portMAX_DELAY) == pdTRUE)
        {
            printf("[TAKER]  Signal கிடைச்சது! 🎉\n");

            // LED ON
            gpio_set_level(LED_PIN, 1);
            printf("[TAKER]  LED ON! 💡\n");
            vTaskDelay(pdMS_TO_TICKS(500));

            // LED OFF
            gpio_set_level(LED_PIN, 0);
            printf("[TAKER]  LED OFF!\n");
        }
    }
}

// ─────────────────────────────
// Main Function
// ─────────────────────────────
void app_main(void)
{
    printf("=== FreeRTOS Semaphore Demo ===\n");

    // Binary Semaphore Create செய்யி
    xSemaphore = xSemaphoreCreateBinary();

    if(xSemaphore == NULL)
    {
        printf("Semaphore creation failed!\n");
        return;
    }

    printf("Semaphore created! ✅\n");

    xTaskCreate(giver_task, "Giver", 2048,
        NULL, 1, NULL);
    xTaskCreate(taker_task, "Taker", 2048,
        NULL, 1, NULL);

    while(1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
