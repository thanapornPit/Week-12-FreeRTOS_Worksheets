#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include <inttypes.h>

#define LED1_PIN GPIO_NUM_2
#define LED2_PIN GPIO_NUM_4

static const char *TAG = "BASIC_TASKS";

// Task function สำหรับ LED1
void led1_task(void *pvParameters)
{
    // Cast parameter ถ้ามี
    int *task_id = (int *)pvParameters;
    
    ESP_LOGI(TAG, "LED1 Task started with ID: %d", *task_id);
    
    // Task loop - ต้องมี infinite loop
    while (1) {
        ESP_LOGI(TAG, "LED1 ON");
        gpio_set_level(LED1_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS(500)); // 500ms delay
        
        ESP_LOGI(TAG, "LED1 OFF");
        gpio_set_level(LED1_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(500)); // 500ms delay
    }
    
    // หมายเหตุ: จุดนี้จะไม่เคยถูกเรียก เพราะ infinite loop
    ESP_LOGI(TAG, "LED1 Task ended"); // จะไม่ถูกเรียก
    vTaskDelete(NULL); // Delete ตัวเอง
}

// Task function สำหรับ LED2
void led2_task(void *pvParameters)
{
    char *task_name = (char *)pvParameters;
    
    ESP_LOGI(TAG, "LED2 Task started: %s", task_name);
    
    while (1) {
        ESP_LOGI(TAG, "LED2 Blink Fast");
        
        // Fast blink pattern
        for (int i = 0; i < 5; i++) {
            gpio_set_level(LED2_PIN, 1);
            vTaskDelay(pdMS_TO_TICKS(100));
            gpio_set_level(LED2_PIN, 0);
            vTaskDelay(pdMS_TO_TICKS(100));
        }
        
        // Pause between patterns
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Task สำหรับแสดงสถิติระบบ
void system_info_task(void *pvParameters)
{
    ESP_LOGI(TAG, "System Info Task started");
    
    while (1) {
        // แสดงข้อมูลระบบ
        ESP_LOGI(TAG, "=== System Information ===");
        ESP_LOGI(TAG, "Free heap: %d bytes", esp_get_free_heap_size());
        ESP_LOGI(TAG, "Min free heap: %d bytes", esp_get_minimum_free_heap_size());
        
        // แสดงจำนวน tasks ที่กำลังทำงาน
        UBaseType_t task_count = uxTaskGetNumberOfTasks();
        ESP_LOGI(TAG, "Number of tasks: %d", task_count);
        
        // แสดง uptime
        TickType_t uptime = xTaskGetTickCount();
        uint32_t uptime_sec = uptime * portTICK_PERIOD_MS / 1000;
        ESP_LOGI(TAG, "Uptime: %d seconds", uptime_sec);
        
        vTaskDelay(pdMS_TO_TICKS(3000)); // รายงานทุก 3 วินาที
    }
}

void app_main(void)
{
    ESP_LOGI(TAG, "=== FreeRTOS Basic Tasks Demo ===");
    
    // GPIO Configuration
    gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = (1ULL << LED1_PIN) | (1ULL << LED2_PIN),
        .pull_down_en = 0,
        .pull_up_en = 0,
    };
    gpio_config(&io_conf);
    
    // Parameters สำหรับ tasks
    static int led1_id = 1;
    static char led2_name[] = "FastBlinker";
    
    // สร้าง tasks
    TaskHandle_t led1_handle = NULL;
    TaskHandle_t led2_handle = NULL;
    TaskHandle_t info_handle = NULL;
    
    // Task 1: LED1 Blink
    BaseType_t result1 = xTaskCreate(
        led1_task,          // Task function
        "LED1_Task",        // Task name (for debugging)
        2048,               // Stack size (bytes)
        &led1_id,           // Parameters
        2,                  // Priority (0-24, สูงกว่า = priority สูงกว่า)
        &led1_handle        // Task handle
    );
    
    if (result1 == pdPASS) {
        ESP_LOGI(TAG, "LED1 Task created successfully");
    } else {
        ESP_LOGE(TAG, "Failed to create LED1 Task");
    }
    
    // Task 2: LED2 Fast Blink
    BaseType_t result2 = xTaskCreate(
        led2_task,
        "LED2_Task",
        2048,
        led2_name,
        2,                  // Same priority as LED1
        &led2_handle
    );
    
    if (result2 == pdPASS) {
        ESP_LOGI(TAG, "LED2 Task created successfully");
    } else {
        ESP_LOGE(TAG, "Failed to create LED2 Task");
    }
    
    // Task 3: System Info
    BaseType_t result3 = xTaskCreate(
        system_info_task,
        "SysInfo_Task",
        3072,               // Larger stack for logging
        NULL,
        1,                  // Lower priority
        &info_handle
    );
    
    if (result3 == pdPASS) {
        ESP_LOGI(TAG, "System Info Task created successfully");
    } else {
        ESP_LOGE(TAG, "Failed to create System Info Task");
    }
    
    ESP_LOGI(TAG, "All tasks created. Main task will now idle.");
    ESP_LOGI(TAG, "Task handles - LED1: %p, LED2: %p, Info: %p", 
             led1_handle, led2_handle, info_handle);
    
    // Main task can continue or be deleted
    // Option 1: Keep main task running
    while (1) {
        ESP_LOGI(TAG, "Main task heartbeat");
        vTaskDelay(pdMS_TO_TICKS(5000)); // 5 seconds
    }
    
    // Option 2: Delete main task (uncomment below)
    // vTaskDelete(NULL);
}
// เพิ่มใน basic_tasks.c

// Task สำหรับควบคุม tasks อื่นๆ
void task_manager(void *pvParameters)
{
    ESP_LOGI(TAG, "Task Manager started");
    
    TaskHandle_t *handles = (TaskHandle_t *)pvParameters;
    TaskHandle_t led1_handle = handles[0];
    TaskHandle_t led2_handle = handles[1];
    
    int command_counter = 0;
    
    while (1) {
        command_counter++;
        
        switch (command_counter % 6) {
    // Forward declaration for task_manager so it can be created in app_main
    void task_manager(void *pvParameters);
            case 1:
                ESP_LOGI(TAG, "Manager: Suspending LED1");
                vTaskSuspend(led1_handle);
                break;
                
            case 2:
                ESP_LOGI(TAG, "Manager: Resuming LED1");
                vTaskResume(led1_handle);
                break;
                
            case 3:
                ESP_LOGI(TAG, "Manager: Suspending LED2");
                vTaskSuspend(led2_handle);
                break;
                
            case 4:
                ESP_LOGI(TAG, "Manager: Resuming LED2");
                vTaskResume(led2_handle);
                break;
                
            case 5:
                ESP_LOGI(TAG, "Manager: Getting task info");
                ESP_LOGI(TAG, "LED1 State: %s", 
                         eTaskGetState(led1_handle) == eRunning ? "Running" : "Not Running");
                ESP_LOGI(TAG, "LED2 State: %s", 
                         eTaskGetState(led2_handle) == eRunning ? "Running" : "Not Running");
                break;
                
            case 0:
                ESP_LOGI(TAG, "Manager: Reset cycle");
                break;
        }
        
        vTaskDelay(pdMS_TO_TICKS(2000)); // 2 seconds
    }
}

// (Task manager is created inside app_main after task handles are available)
// Task สำหรับทดสอบ priorities
void high_priority_task(void *pvParameters)
{
    ESP_LOGI(TAG, "High Priority Task started");
    
    while (1) {
        ESP_LOGW(TAG, "HIGH PRIORITY TASK RUNNING!");
        
        // Simulate high priority work
        for (int i = 0; i < 1000000; i++) {
            volatile int dummy = i;
        }
        
        ESP_LOGW(TAG, "High priority task yielding");
        vTaskDelay(pdMS_TO_TICKS(5000)); // 5 seconds
    }
}

void low_priority_task(void *pvParameters)
{
    ESP_LOGI(TAG, "Low Priority Task started");
    
    while (1) {
        ESP_LOGI(TAG, "Low priority task running");
        
        // This task will be preempted by higher priority tasks
        for (int i = 0; i < 100; i++) {
            ESP_LOGI(TAG, "Low priority work: %d/100", i+1);
            vTaskDelay(pdMS_TO_TICKS(100));
        }
    }
}

// Task สำหรับแสดง runtime statistics
void runtime_stats_task(void *pvParameters)
{
    ESP_LOGI(TAG, "Runtime Stats Task started");
    
    // Allocate buffer for runtime stats
    char *buffer = malloc(1024);
    if (buffer == NULL) {
        ESP_LOGE(TAG, "Failed to allocate buffer for runtime stats");
        vTaskDelete(NULL);
        return;
    }
    
    while (1) {
        ESP_LOGI(TAG, "\n=== Runtime Statistics ===");
        
        // Get runtime statistics
        vTaskGetRunTimeStats(buffer);
        ESP_LOGI(TAG, "Task\t\tAbs Time\tPercent Time");
        ESP_LOGI(TAG, "%s", buffer);
        
        // Get task list
        ESP_LOGI(TAG, "\n=== Task List ===");
        vTaskList(buffer);
        ESP_LOGI(TAG, "Name\t\tState\tPriority\tStack\tNum");
        ESP_LOGI(TAG, "%s", buffer);
        
        vTaskDelay(pdMS_TO_TICKS(10000)); // 10 seconds
    }
    
    free(buffer);
}