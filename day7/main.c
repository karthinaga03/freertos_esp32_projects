#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"

#define BUTTON_PIN  GPIO_NUM_0  // BOOT button ✅
#define LED_PIN     GPIO_NUM_2  // Built-in LED ✅

QueueHandle_t     xDataQueue;
SemaphoreHandle_t xButtonSemaphore;

// ─────────────────────────────
// Fake Sensor Read
// ─────────────────────────────
int fake_sensor_read(void)
{
    return 20 + (rand() % 21); // 20~40 value
}

// ─────────────────────────────
// Button ISR
// ─────────────────────────────
void IRAM_ATTR button_isr(void *arg)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(
        xButtonSemaphore,
        &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

// ─────────────────────────────
// Task 1 — Button Task
// ─────────────────────────────
void button_task(void *pvParameters)
{
    int sensor_value = 0;

    while(1)
    {
        // BOOT button press-க்கு காத்திரு!
        if(xSemaphoreTake(xButtonSemaphore,
            portMAX_DELAY) == pdTRUE)
        {
            // Fake sensor read
            sensor_value = fake_sensor_read();

            printf("\n[BUTTON]  BOOT Pressed! 🔘\n");
            printf("[SENSOR]  Value: %d°C\n",
                sensor_value);

            // Queue-ல அனுப்பு
            xQueueSend(xDataQueue,
                &sensor_value,
                pdMS_TO_TICKS(100));

            printf("[BUTTON]  Queue-ல அனுப்பினேன்! ✅\n");
        }
    }
}

// ─────────────────────────────
// Task 2 — Display Task
// ─────────────────────────────
void display_task(void *pvParameters)
{
    int received_value = 0;

    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    while(1)
    {
        if(xQueueReceive(xDataQueue,
            &received_value,
            portMAX_DELAY) == pdTRUE)
        {
            printf("[DISPLAY] Data: %d°C 🌡️\n",
                received_value);

            // LED Blink — Display simulate
            for(int i = 0; i < 3; i++)
            {
                gpio_set_level(LED_PIN, 1);
                printf("[DISPLAY] LED ON 💡\n");
                vTaskDelay(pdMS_TO_TICKS(200));

                gpio_set_level(LED_PIN, 0);
                printf("[DISPLAY] LED OFF\n");
                vTaskDelay(pdMS_TO_TICKS(200));
            }

            printf("[DISPLAY] Done! ✅\n\n");
        }
    }
}

// ─────────────────────────────
// Task 3 — Monitor Task
// ─────────────────────────────
void monitor_task(void *pvParameters)
{
    while(1)
    {
        UBaseType_t count =
            uxQueueMessagesWaiting(xDataQueue);

        printf("[MONITOR] Queue: %d items | "
               "BOOT button press செய்யி! 👆\n",
               count);

        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}

// ─────────────────────────────
// Main
// ─────────────────────────────
void app_main(void)
{
    printf("============================\n");
    printf("  Queue + Semaphore Demo\n");
    printf("  BOOT Button Press செய்யி!\n");
    printf("============================\n\n");

    // Button Setup
    gpio_reset_pin(BUTTON_PIN);
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_PIN, GPIO_PULLUP_ONLY);
    gpio_install_isr_service(0);
    gpio_isr_handler_add(BUTTON_PIN, button_isr, NULL);
    gpio_set_intr_type(BUTTON_PIN, GPIO_INTR_NEGEDGE);

    // Create Queue + Semaphore
    xDataQueue        = xQueueCreate(5, sizeof(int));
    xButtonSemaphore  = xSemaphoreCreateBinary();

    if(!xDataQueue || !xButtonSemaphore)
    {
        printf("❌ Creation failed!\n");
        return;
    }

    printf("✅ Ready!\n\n");

    // Create Tasks
    xTaskCreate(button_task,  "Button",  2048,
        NULL, 3, NULL);
    xTaskCreate(display_task, "Display", 2048,
        NULL, 2, NULL);
    xTaskCreate(monitor_task, "Monitor", 2048,
        NULL, 1, NULL);

    while(1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}