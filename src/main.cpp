#define BLYNK_TEMPLATE_ID   "TMPL4VNHe72Y1"
#define BLYNK_TEMPLATE_NAME "Quickstart Device"
#define BLYNK_AUTH_TOKEN    "QCRfgaoUZTVbLmFCFspuIIvmoEYuS9Ie"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <BlynkSimpleEsp32.h>
#include <SimpleDHT.h>
#include <WiFi.h>
#include <WiFiClient.h>

char ssid[] = "POCO X3 PRO";
char pass[] = "neagu1234";

#define DHTPIN 22
#define MQ2PIN 33

SimpleDHT11 dht11(DHTPIN);
BlynkTimer timer;

void sendSensor() {
  float temperature = 0;
  float humidity = 0;
  byte data[40] = {0};
  int err = SimpleDHTErrSuccess;

  if ((err = dht11.read2(&temperature, &humidity, data)) !=
      SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err=");
    Serial.print(SimpleDHTErrCode(err));
    Serial.print(",");
    Serial.println(SimpleDHTErrDuration(err));
    delay(2000);
    return;
  }

  Serial.print("Sample OK: ");
  Serial.print((float)temperature);
  Serial.print(" *C, ");
  Serial.print((float)humidity);
  Serial.println(" RH%");

  Blynk.virtualWrite(V1, (float)humidity);
  Blynk.virtualWrite(V2, (float)temperature);
  Blynk.virtualWrite(V3, analogRead(MQ2PIN));
}

void setup() {
  Serial.begin(9600);

  pinMode(MQ2PIN, INPUT);
  adcAttachPin(MQ2PIN);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}