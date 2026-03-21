#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

#define LED_PIN GPIO_NUM_2

// Queue Handle — Global-ஆ declare செய்யி
QueueHandle_t xQueue;

// ─────────────────────────────
// Sender Task — Data அனுப்பும்
// ─────────────────────────────
void sender_task(void *pvParameters)
{
    int led_state = 0;

    while(1)
    {
        // LED state toggle செய்யி
        led_state = !led_state;

        // Queue-ல அனுப்பு
        xQueueSend(xQueue, &led_state, portMAX_DELAY);
        printf("[SENDER]   Sent: %d\n", led_state);

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

// ─────────────────────────────
// Receiver Task — Data எடுக்கும்
// ─────────────────────────────
void receiver_task(void *pvParameters)
{
    int received_state = 0;

    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    while(1)
    {
        // Queue-லிருந்து எடு
        xQueueReceive(xQueue, &received_state, portMAX_DELAY);
        printf("[RECEIVER] Received: %d\n", received_state);

        // LED control செய்யி
        gpio_set_level(LED_PIN, received_state);

        if(received_state == 1)
            printf("[RECEIVER] LED ON! 💡\n");
        else
            printf("[RECEIVER] LED OFF!\n");
    }
}

// ─────────────────────────────
// Main Function
// ─────────────────────────────
void app_main(void)
{
    printf("=== FreeRTOS Queue Demo ===\n");

    // Queue Create — 5 items, int size
    xQueue = xQueueCreate(5, sizeof(int));

    if(xQueue == NULL)
    {
        printf("Queue creation failed!\n");
        return;
    }

    printf("Queue created successfully!\n");

    // Tasks Create செய்யி
    xTaskCreate(sender_task,   "Sender",   2048, NULL, 1, NULL);
    xTaskCreate(receiver_task, "Receiver", 2048, NULL, 1, NULL);

    while(1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
