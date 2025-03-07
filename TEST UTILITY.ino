// Testing utility to list all the temperature probes attached to ESP32 and collect temperatures to prove it is working. 

#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup(void) {
  Serial.begin(115200);
  sensors.begin();
}

void loop(void) {
  byte i;
  byte addr[8];

  if (!oneWire.search(addr)) {
    Serial.println("No more addresses.");
    Serial.println();
    oneWire.reset_search();
    delay(250);
    return;
  }

  Serial.print("ROM =");
  for (i = 0; i < 8; i++) {
    Serial.write(' ');
    Serial.print(addr[i], HEX);
  }

  DeviceAddress sensorAddr;
  memcpy(sensorAddr, addr, 8);

  Serial.print(" Requesting temperatures...");
  sensors.requestTemperatures();
  Serial.println(" DONE");

  Serial.print("Sensor (*C): ");
  Serial.print(sensors.getTempC(sensorAddr));
  Serial.print(" Sensor (*F): ");
  Serial.println(sensors.getTempF(sensorAddr));

  delay(2000);
}
