#include <EEPROM.h>

int MAX = 100;

void setup() {
  Serial.begin(9600);

  int error_cnt = 0;
  int duration;
  int per;
  int8_t rssi;
  
  for (int i = 0; i < MAX; i++) {
    int duration;
    
    EEPROM.get(i*5, duration);
    EEPROM.get(i*5 + 4, rssi);
    Serial.print(i);
    Serial.print("    DURATION: ");
    Serial.print(duration);
    Serial.print("    -    RSSI: ");
    Serial.println(rssi);
  }
  EEPROM.get(MAX * 5, error_cnt);
  Serial.print("PER (in %): ");
  Serial.println(error_cnt);
  
}

void loop() {
  
}
