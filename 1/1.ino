#define LED1 13
#define LED2 26
#define LED3 4
#define LED4 2
#define SW1 32
#define SW2 27


TaskHandle_t blinkLED1Task = NULL;
TaskHandle_t blinkLED2Task = NULL;
TaskHandle_t LEDstateTask = NULL;
TaskHandle_t HWControlTask = NULL;


char func = 0;


void blinkLED1(void *pvParam) {
  while (1) {
    digitalWrite(LED1, !digitalRead(LED1));
    vTaskDelay(170);
  }
}


void blinkLED2(void *pvParam) {
  while (1) {
    digitalWrite(LED2, !digitalRead(LED2));
    vTaskDelay(270);
  }
}


void LEDstate(void *pvParam) {
  while (1) {
    String LED1st = digitalRead(LED1) ? "ON" : "OFF";
    String LED2st = digitalRead(LED2) ? "ON" : "OFF";
    int ADC33 = analogRead(33);
    Serial.printf("LED1 LED2 ADC33 => %s %s %d\n", LED1st.c_str(), LED2st.c_str(), ADC33);
    vTaskDelay(500);
  }
}




void HWControl(void *pvParam) {
  while (1) {
    if (func == 'a') {
      digitalWrite(LED3, HIGH);
      func = 0;
    } else if (func == 'b') {
      digitalWrite(LED3, LOW);
      func = 0;
    } else if (func == 'x') {
      vTaskSuspend(blinkLED1Task);
      func = 0;
    } else if (func == 'y') {
      vTaskSuspend(blinkLED2Task);
      func = 0;
    } else if (func == 'z') {
      vTaskResume(blinkLED1Task);
      vTaskResume(blinkLED2Task);
      func = 0;
    }
    vTaskDelay(10);
  }
}
void setup() {
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  xTaskCreatePinnedToCore(blinkLED1, "blinkLED1", 10000, NULL, 1, &blinkLED1Task, 1);
  xTaskCreatePinnedToCore(blinkLED2, "blinkLED2", 10000, NULL, 1, &blinkLED2Task, 1);
  xTaskCreatePinnedToCore(LEDstate, "LEDstate", 10000, NULL, 1, &LEDstateTask, 0);
  xTaskCreatePinnedToCore(HWControl, "HWControl", 10000, NULL, 1, &HWControlTask, 0);
}
void loop() {
}
