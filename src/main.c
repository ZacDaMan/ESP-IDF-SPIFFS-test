#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/param.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spiffs.h"
#include "esp_err.h"
#include "esp_vfs_fat.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "sdkconfig.h"
#include "esp_http_server.h"
#include "protocol_examples_common.h"
#include "sdmmc_cmd.h"
#include "soc/soc_caps.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>

#include "time.h"
#include "sys/time.h"

static const char *TAG = "example";

void app_main() {
    sys_delay_ms(5000);
    for(int i = 0; i < 30; i++){
        ESP_LOGI(TAG, "Initializing SPIFFS");
    }
    esp_vfs_spiffs_conf_t conf = {
      .base_path = "/spiffs",
      .partition_label = NULL,
      .max_files = 5,   // This decides the maximum number of files that can be created on the storage
      .format_if_mount_failed = true
    };

    esp_err_t ret = esp_vfs_spiffs_register(&conf);
    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG, "Failed to mount or format filesystem");
        } else if (ret == ESP_ERR_NOT_FOUND) {
            ESP_LOGE(TAG, "Failed to find SPIFFS partition");
        } else {
            ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
        }
        return;
    }

    size_t total = 0, used = 0;
    ret = esp_spiffs_info(NULL, &total, &used);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret));
        return;
    }

    ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);

    FILE* f = fopen("/spiffs/HereIsText.txt", "r");
    if(f == NULL){
        ESP_LOGE(TAG, "Failed to open BANANA file");
    }
    fclose(f);
    return ;
}