#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

SemaphoreHandle_t xCountSemaphore;

// ─────────────────────────────
// Car Park Task — Parking-ல நுழை
// ─────────────────────────────
void car_park_task(void *pvParameters)
{
    int car_id = (int)pvParameters;

    // Slot கிடைக்குமா பாரு
    if(xSemaphoreTake(xCountSemaphore,
        pdMS_TO_TICKS(1000)) == pdTRUE)
    {
        printf("[CAR %d] Parking-ல நுழைந்தேன்! 🚗\n",
            car_id);

        // Parking-ல இருக்கும் நேரம்
        vTaskDelay(pdMS_TO_TICKS(3000));

        printf("[CAR %d] Parking விட்டு போறேன்!\n",
            car_id);

        // Slot திரும்ப குடு
        xSemaphoreGive(xCountSemaphore);
    }
    else
    {
        printf("[CAR %d] Slot இல்லை! 😢\n", car_id);
    }

    vTaskDelete(NULL);
}

void app_main(void)
{
    printf("=== Counting Semaphore Demo ===\n");
    printf("Parking Slots: 3\n\n");

    // Max=3, Initial=3
    xCountSemaphore = xSemaphoreCreateCounting(3, 3);

    if(xCountSemaphore == NULL)
    {
        printf("Semaphore failed!\n");
        return;
    }

    // 5 cars வருது — ஆனா 3 slots மட்டும்!
    for(int i = 1; i <= 5; i++)
    {
        xTaskCreate(car_park_task, "Car",
            2048, (void*)i, 1, NULL);
        vTaskDelay(pdMS_TO_TICKS(500));
    }

    while(1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}