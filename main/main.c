#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "i2c-lcd.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/ledc.h"
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "dht11.h"
#include "lwip/err.h"
#include "lwip/sys.h"
/**/

// #define EXAMPLE_ESP_WIFI_SSID "DATN"     // CONFIG_ESP_WIFI_SSID
// #define EXAMPLE_ESP_WIFI_PASS "12345678" // CONFIG_ESP_WIFI_PASSWORD
// #define EXAMPLE_ESP_MAXIMUM_RETRY CONFIG_ESP_MAXIMUM_RETRY                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           ```````` i
/**/
/**/
#define BUZZER_PIN GPIO_NUM_19
#define MQ2_ADC 2
#define MQ2 14
#define DHT11PIN 18
#define I2C_MASTER_SCL_IO 22      /*!< GPIO cho chân clock của I2C master */
#define I2C_MASTER_SDA_IO 21      /*!< GPIO cho chân dữ liệu của I2C master */
#define I2C_MASTER_NUM I2C_NUM_0  /*!< Số cổng I2C cho thiết bị master */
#define I2C_MASTER_FREQ_HZ 100000 /*!< Tần số clock của I2C master */
#define IR_SENSOR_PIN GPIO_NUM_4
/**/
/*
#if CONFIG_ESP_WIFI_AUTH_OPEN
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_OPEN
#elif CONFIG_ESP_WIFI_AUTH_WEP
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WEP
#elif CONFIG_ESP_WIFI_AUTH_WPA_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA2_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA2_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA_WPA2_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA_WPA2_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA3_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA3_PSK
#elif CONFIG_ESP_WIFI_AUTH_WPA2_WPA3_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WPA2_WPA3_PSK
#elif CONFIG_ESP_WIFI_AUTH_WAPI_PSK
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_WAPI_PSK
#endif
    static EventGroupHandle_t s_wifi_event_group;
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT BIT1
static const char *TAG = "wifi station";
static int s_retry_num = 0;
*/
static const char *TAG = "warring";
/**
 * @brief i2c master initialization
 */
/*config wifi*/
//     static void
//     event_handler(void *arg, esp_event_base_t event_base,
//                   int32_t event_id, void *event_data)
// {
//     if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START)
//     {
//         esp_wifi_connect();
//     }
//     else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED)
//     {
//         if (s_retry_num < EXAMPLE_ESP_MAXIMUM_RETRY)
//         {
//             esp_wifi_connect();
//             s_retry_num++;
//             ESP_LOGI(TAG, "retry to connect to the AP");
//         }
//         else
//         {
//             xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
//         }
//         ESP_LOGI(TAG, "connect to the AP fail");
//     }
//     else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
//     {
//         ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
//         ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
//         s_retry_num = 0;
//         xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
//     }
// }

// void wifi_init_sta(void)
// {
//     s_wifi_event_group = xEventGroupCreate();

//     ESP_ERROR_CHECK(esp_netif_init());

//     ESP_ERROR_CHECK(esp_event_loop_create_default());
//     esp_netif_create_default_wifi_sta();

//     wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
//     ESP_ERROR_CHECK(esp_wifi_init(&cfg));

//     esp_event_handler_instance_t instance_any_id;
//     esp_event_handler_instance_t instance_got_ip;
//     ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
//                                                         ESP_EVENT_ANY_ID,
//                                                         &event_handler,
//                                                         NULL,
//                                                         &instance_any_id));
//     ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
//                                                         IP_EVENT_STA_GOT_IP,
//                                                         &event_handler,
//                                                         NULL,
//                                                         &instance_got_ip));

//     wifi_config_t wifi_config = {
//         .sta = {
//             .ssid = EXAMPLE_ESP_WIFI_SSID,
//             .password = EXAMPLE_ESP_WIFI_PASS,
//             /* Setting a password implies station will connect to all security modes including WEP/WPA.
//              * However these modes are deprecated and not advisable to be used. Incase your Access point
//              * doesn't support WPA2, these mode can be enabled by commenting below line */
//             .threshold.authmode = ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD,
//             .sae_pwe_h2e = WPA3_SAE_PWE_BOTH,
//         },
//     };
//     ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
//     ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
//     ESP_ERROR_CHECK(esp_wifi_start());

//     ESP_LOGI(TAG, "wifi_init_sta finished.");

//     /* Waiting until either the connection is established (WIFI_CONNECTED_BIT) or connection failed for the maximum
//      * number of re-tries (WIFI_FAIL_BIT). The bits are set by event_handler() (see above) */
//     EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
//                                            WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
//                                            pdFALSE,
//                                            pdFALSE,
//                                            portMAX_DELAY);

//     /* xEventGroupWaitBits() returns the bits before the call returned, hence we can test which event actually
//      * happened. */
//     if (bits & WIFI_CONNECTED_BIT)
//     {
//         ESP_LOGI(TAG, "connected to ap SSID:%s password:%s",
//                  EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
//     }
//     else if (bits & WIFI_FAIL_BIT)
//     {
//         ESP_LOGI(TAG, "Failed to connect to SSID:%s, password:%s",
//                  EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
//     }
//     else
//     {
//         ESP_LOGE(TAG, "UNEXPECTED EVENT");
//     }

//     /* The event will not be processed after unregister */
//     ESP_ERROR_CHECK(esp_event_handler_instance_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, instance_got_ip));
//     ESP_ERROR_CHECK(esp_event_handler_instance_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID, instance_any_id));
//     vEventGroupDelete(s_wifi_event_group);
// }
// /**/
// /*i2c-lcd*/
void configure_gpio()
{
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << IR_SENSOR_PIN | 1ULL << BUZZER_PIN),
        .mode = GPIO_MODE_INPUT,
        .intr_type = GPIO_INTR_DISABLE,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
    };
    gpio_config(&io_conf);
}
static esp_err_t i2c_master_init(void)
{
    int i2c_master_port = I2C_NUM_0; // xác định số cổng I2C khởi tạo ( giá trị ban đầu là 0 )
    // Lưu trữ thông tin cấu hình I2C
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO, // là số chân GPIO cho dữ liệu (SDA)
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = I2C_MASTER_SCL_IO, // là số chân GPIO cho clock(SCL)
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ, // xác định tốc độ clock của I2C master
    };
    i2c_param_config(I2C_MASTER_NUM, &conf); // để áp dụng cấu hình I2C cho số cổng I2C master đã chọn (I2C_MASTER_NUM).
    return i2c_driver_install(I2C_MASTER_NUM, conf.mode, 0, 0, 0);
}
/**/
void init_buzzer()
{
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << BUZZER_PIN),
        .mode = GPIO_MODE_OUTPUT,
        .intr_type = GPIO_INTR_DISABLE,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
    };
    gpio_config(&io_conf);
}
void buzzer_on()
{
    gpio_set_level(BUZZER_PIN, 1);
}

void buzzer_off()
{
    gpio_set_level(BUZZER_PIN, 0);
}
/**/
void read_ir_sensor_task(void *arg)
{
    for (;;)
    {
        uint32_t gas = 0;
        uint8_t dataGas = 0;
        char buffer[50];
        float humidity, temperature;
        int ir_value = gpio_get_level(IR_SENSOR_PIN);
        dht_read_data(DHT11PIN, &humidity, &temperature);

        // lcd_init();
        // lcd_clear();
        // printf("GAS=%.2f", gas);
        printf("Temp=%f, Humi=%f\r\n", temperature, humidity);
        // lcd_put_cur(0, 0);
        // sprintf(buffer, "Temperature: %.2f°C, Humidity: %.2f%%", temperature, humidity);
        sprintf(buffer, "Temperature: %.2f°C", temperature);
        ESP_LOGI(TAG, "IR Sensor Value: %d", ir_value);
        // ESP_LOGI(TAG, "GAS Value: %f", gas);
        if (ir_value == 1)
        {
            lcd_init();

            // dht_read_data(DHT11PIN, &humidity, &temperature);
            // lcd_put_cur(0, 0);
            // sprintf(buffer, "val=%.2f", ir_value);
            // lcd_put_cur(0, 0);
            // lcd_send_string(buffer);
            // lcd_put_cur(0, 0);
            // printf("Temp=%f, Humi=%f\r\n", temperature, humidity);
            // lcd_put_cur(0, 0);
            // lcd_send_string("Hello world!");
            buzzer_on();
        }
        else
        {
            lcd_clear();
            lcd_init();
            lcd_put_cur(1, 1);
            lcd_send_string("FIRE ALARM");
            buzzer_off();
        }
        if (gas > 2000)
        {
            dataGas = 1;
            printf("Warring");
        }
        // Đoạn code này có thể được thay thế bằng việc xử lý thông tin ánh sáng theo nhu cầu của bạn.

        vTaskDelay(pdMS_TO_TICKS(1000)); // Đợi 1 giây trước khi đọc lại giá trị từ cảm biến
    }
}
/**/
void app_main(void)
{
    init_buzzer();
    lcd_init();
    lcd_clear();
    lcd_put_cur(0, 0);
    lcd_send_string("Hello world!");
    // Initialize NVS
    // esp_err_t ret = nvs_flash_init();
    // if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    // {
    //     ESP_ERROR_CHECK(nvs_flash_erase());
    //     ret = nvs_flash_init();
    // }
    // ESP_ERROR_CHECK(ret);

    // ESP_LOGI(TAG, "ESP_WIFI_MODE_STA");
    // wifi_init_sta();
    xTaskCreate(read_ir_sensor_task, "read_ir_sensor_task", 6000, NULL, 18, NULL);
}
