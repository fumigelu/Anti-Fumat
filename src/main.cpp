#include <SimpleDHT.h>

// for DHT11,
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 22
int pinDHT11 = 22;
SimpleDHT11 dht22(pinDHT11);

void setup() {
  Serial.begin(9600);
}

void loop() {
  float temperature = 0;
  float humidity = 0;
  byte data[40] = {0};
  int err = SimpleDHTErrSuccess;
  
  if ((err = dht22.read2(&temperature, &humidity, data)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT22 failed, err="); Serial.print(SimpleDHTErrCode(err));
    Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); delay(2000);
    return;
  }
  
  Serial.print("Sample OK: ");
  Serial.print((float)temperature); Serial.print(" *C, ");
  Serial.print((float)humidity); Serial.println(" RH%");
  
  // DHT11 sampling rate is 1HZ.
  delay(5000);
}