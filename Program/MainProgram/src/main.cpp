#include <Arduino.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <semphr.h>

static QueueHandle_t qSensor = nullptr;
static SemaphoreHandle_t serialMutex = nullptr;

// --- Contoh ISR pakai IntervalTimer (Teensy) ---
IntervalTimer isrTimer;

void isrTick() {
  static uint32_t counter = 0;
  counter++;
  BaseType_t xHigherWoken = pdFALSE;
  xQueueSendFromISR(qSensor, &counter, &xHigherWoken);
  portYIELD_FROM_ISR(xHigherWoken);
}

// --- Task 1: baca queue (data “datang” dari ISR) ---
void taskConsumer(void* pv) {
  uint32_t val;
  for (;;) {
    if (xQueueReceive(qSensor, &val, portMAX_DELAY) == pdPASS) {
      // Proteksi Serial dengan mutex agar output rapi
      xSemaphoreTake(serialMutex, portMAX_DELAY);
      Serial.printf("[consumer] got: %lu\n", (unsigned long)val);
      xSemaphoreGive(serialMutex);
    }
  }
}

// --- Task 2: kerja periodik (blink) ---
void taskBlink(void* pv) {
  pinMode(LED_BUILTIN, OUTPUT);
  for (;;) {
    digitalWrite(LED_BUILTIN, HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_BUILTIN, LOW);
    vTaskDelay(pdMS_TO_TICKS(900));

    xSemaphoreTake(serialMutex, portMAX_DELAY);
    Serial.println("[blink] alive");
    xSemaphoreGive(serialMutex);
  }
}

void setup() {
  // Serial
  Serial.begin(115200);
  while (!Serial) { /* tunggu enumerasi USB */ }

  // RTOS primitives
  qSensor = xQueueCreate(16, sizeof(uint32_t));
  serialMutex = xSemaphoreCreateMutex();

  // Buat tasks (stack size & priority bisa disetel sesuai beban)
  xTaskCreate(
    taskConsumer, "consumer",
    2048 / sizeof(StackType_t),  // stack bytes/sizeof(StackType_t)
    nullptr,
    tskIDLE_PRIORITY + 2,
    nullptr
  );

  xTaskCreate(
    taskBlink, "blink",
    2048 / sizeof(StackType_t),
    nullptr,
    tskIDLE_PRIORITY + 1,
    nullptr
  );

  // Start ISR timer setiap 5 ms (200 Hz) untuk “mengirim data”
  isrTimer.begin(isrTick, 5000); // microseconds

  // Start scheduler (kebanyakan port Arduino+FreeRTOS perlu ini)
  vTaskStartScheduler();

  // Jika sampai sini, berarti gagal start scheduler (kehabisan heap)
  Serial.println("ERROR: vTaskStartScheduler failed!");
}

void loop() {
  // Tidak dipakai ketika RTOS jalan; boleh kosong atau yield
  vTaskDelay(pdMS_TO_TICKS(1000));
}
