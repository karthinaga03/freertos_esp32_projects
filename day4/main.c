#include<stdio.h>
#include<driver/gpio.h>
#include<freertos/FREERTOS.h>
#include<freertos/task.h>

#define led_pin1 2
#define led_pin2 4
void task_delay(void *PVparameters)
{
    gpio_reset_pin(led_pin1);
    gpio_set_direction(led_pin1,GPIO_MODE_OUTPUT);
    while(1)
    {
        gpio_set_level(led_pin1,1);
        printf("vtaskdelay led1 on\n");
        vTaskDelay(pdMS_TO_TICKS(500));

        gpio_set_level(led_pin1,0);
        printf("vtaskdelay led1 off\n");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
    }

void task_delay_until(void *PVparameters)
{
    gpio_reset_pin(led_pin2);
    gpio_set_direction(led_pin2,GPIO_MODE_OUTPUT);

    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xPeriod = pdMS_TO_TICKS(500);

    while(1)
    {
        gpio_set_level(led_pin2,1);
        printf("harini led2 on\n");
        vTaskDelayUntil(&xLastWakeTime,xPeriod);
        

        gpio_set_level(led_pin2,0);
        printf("harini led2 off\n");
        vTaskDelayUntil(&xLastWakeTime,xPeriod);
       
    }
    }

    void app_main()
    {
        printf("day3 taskdelay and taskdelayuntil");
        xTaskCreate(task_delay,"taskdelay",2048,NULL,1,NULL);
        xTaskCreate(task_delay_until,"taskdelayuntil",2048,NULL,1,NULL);
        while(1)
        {
            vTaskDelay(pdMS_TO_TICKS(500));
        }

    }
