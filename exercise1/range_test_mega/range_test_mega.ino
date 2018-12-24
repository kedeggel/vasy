#include <EEPROM.h>

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  writeEEPROM(0, 0, 0, 0);
}

void writeEEPROM(int offset, int per, int rssi, int rtt) {
  // packet error rate
  // received signal strenght indicator
  // round trip time

}
