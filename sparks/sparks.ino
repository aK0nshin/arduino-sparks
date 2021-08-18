#define SPARK_MAX_DURATION 100 // максимальное время искры в миллисекундах
#define DARK_MAX_DURATION 10 // максимальное время покоя в миллисекундах
#define SPARK_PIN_COUNT 1 // количество искрящих пинов
uint8_t sparkPins[SPARK_PIN_COUNT] = {10}; // искрящие пины

uint32_t sparkTime[SPARK_PIN_COUNT];
boolean sparkStatus[SPARK_PIN_COUNT];

void setup() {
  randomSeed(analogRead(A0)); // А0 никуда не подключен, берём из него шум
  initSpark();
}

void loop() {
  // put your main code here, to run repeatedly:
  sparkCheck();
}

void initSpark() {
  for (int i = 0; i < SPARK_PIN_COUNT; i++) {
    pinMode(sparkPins[i], OUTPUT);
    digitalWrite(sparkPins[i], LOW);
    sparkTime[i] = millis() + random(DARK_MAX_DURATION);
    sparkStatus[i] = false;
  }
}

void sparkCheck() {
  for (int i = 0; i < SPARK_PIN_COUNT; i++) {
    if (millis() > sparkTime[i]) {
      switchSpark(i);
    }
  }
}

void switchSpark(uint8_t spark_n) {
  if (sparkStatus[spark_n]) {
    digitalWrite(sparkPins[spark_n], LOW);
    sparkTime[spark_n] = millis() + random(DARK_MAX_DURATION);
    sparkStatus[spark_n] = false;
  } else {
    digitalWrite(sparkPins[spark_n], HIGH);
    sparkTime[spark_n] = millis() + random(SPARK_MAX_DURATION);
    sparkStatus[spark_n] = true;
  }
}
