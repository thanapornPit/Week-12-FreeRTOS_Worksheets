#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "build_info.h"

void app_main(void)
{
    printf("=== %s v%s ===\n", PROJECT_NAME, PROJECT_VERSION);
    printf("Built on: %s %s\n", BUILD_DATE, BUILD_TIME);
    printf("ESP-IDF Version: %s\n", esp_get_idf_version());
    printf("Chip: %s\n", CONFIG_IDF_TARGET);
    printf("Free heap: %d bytes\n", esp_get_free_heap_size());
    
    while(1) {
        printf("System is running...\n");
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}