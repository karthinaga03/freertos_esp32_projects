    #include <stdio.h>
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"
    #include "freertos/semphr.h"

    // Mutex Handle
    SemaphoreHandle_t xMutex;

    // Shared Resource — UART (printf)
    void shared_print(const char *task_name, int value)
    {
        // Lock செய்யி!
        if(xSemaphoreTake(xMutex,
            portMAX_DELAY) == pdTRUE)
        {
            // Safe zone — ஒரே task மட்டும் இங்க!
            printf("[%s] Value: %d\n",
                task_name, value);
            vTaskDelay(pdMS_TO_TICKS(100));

            // Unlock செய்யி!
            xSemaphoreGive(xMutex);
        }
    }

    // ─────────────────────────────
    // Task 1
    // ─────────────────────────────
    void task1(void *pvParameters)
    {
        int count = 0;
        while(1)
        {
            count++;
            shared_print("TASK1", count);
            vTaskDelay(pdMS_TO_TICKS(500));
        }
    }

    // ─────────────────────────────
    // Task 2
    // ─────────────────────────────
    void task2(void *pvParameters)
    {
        int count = 100;
        while(1)
        {
            count++;
            shared_print("TASK2", count);
            vTaskDelay(pdMS_TO_TICKS(700));
        }
    }

    // ─────────────────────────────
    // Task 3
    // ─────────────────────────────
    void task3(void *pvParameters)
    {
        int count = 200;
        while(1)
        {
            count++;
            shared_print("TASK3", count);
            vTaskDelay(pdMS_TO_TICKS(300));
        }
    }

    // ─────────────────────────────
    // Main
    // ─────────────────────────────
void app_main(void)
{
    printf("=== Mutex Demo ===\n");

    xMutex = xSemaphoreCreateMutex();

    if(xMutex == NULL)
    {
        printf("Mutex failed!\n");
        while(1);
    }

    printf("Mutex created! ✅\n");

    xTaskCreate(task1, "Task1", 4096, NULL, 1, NULL);
    xTaskCreate(task2, "Task2", 4096, NULL, 1, NULL);
    xTaskCreate(task3, "Task3", 4096, NULL, 1, NULL);

    vTaskDelay(portMAX_DELAY);   // 🔥 important
}