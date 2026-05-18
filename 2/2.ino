hw_timer_t * timer = NULL;

const int led1 = 18;
const int sw1 = 26;
const int sw2 = 27;

volatile int cnt;

portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void onTimer() {
  portENTER_CRITICAL_ISR(&timerMux); 
  digitalWrite(led1, !digitalRead(led1));
  portEXIT_CRITICAL_ISR(&timerMux);
}

void IRAM_ATTR sw1_press()
{
  timerAttachInterrupt(timer, &onTimer);
  timerAlarm(timer, 200000,true,0);
}

void IRAM_ATTR sw2_press()
{
  timerDetachInterrupt(timer);
  digitalWrite(led1, LOW);
  cnt++;
  
}

void setup() { 
  Serial.begin(115200);
  timer = timerBegin(1000000);

  pinMode(led1, OUTPUT);
  pinMode(sw1, INPUT_PULLUP);
  attachInterrupt(sw1, sw1_press, FALLING);

  pinMode(sw2, INPUT_PULLUP);
  attachInterrupt(sw2, sw2_press, FALLING);

  
}

void loop() {
  if (cnt >= 3){
    Serial.println("Timer Interrupt abort 3 times!!");
    Serial.println("ESP Restart....\n\n");
    ESP.restart();
  }
}
