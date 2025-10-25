#define BLYNK_TEMPLATE_ID "TMPL6aU8BmkoH"
#define BLYNK_TEMPLATE_NAME "Smart Light Switch"
#define BLYNK_AUTH_TOKEN "0bpADB-GuVMYBZrwzPYss8USpzQxNaS6"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wokwi-GUEST"; // Wokwi mặc định
char pass[] = "";

#define LED_PIN 23
#define BUTTON_PIN 21

BlynkTimer timer;
bool ledState = false;
bool lastButtonState = HIGH; // pull-up mode

// Khi người dùng thay đổi công tắc trên Blynk
BLYNK_WRITE(V1) {
  ledState = param.asInt();
  digitalWrite(LED_PIN, ledState);
  Serial.print("Blynk switch changed: ");
  Serial.println(ledState);
}

// Hàm đọc nút vật lý
void checkButton() {
  bool buttonState = digitalRead(BUTTON_PIN);

  // Nút nhấn xuống (LOW nếu dùng INPUT_PULLUP)
  if (buttonState == LOW && lastButtonState == HIGH) {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
    Blynk.virtualWrite(V1, ledState); // đồng bộ lên Blynk
    delay(300); // debounce
  }
  lastButtonState = buttonState;
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(100L, checkButton);
}

void loop() {
  Blynk.run();
  timer.run();
}