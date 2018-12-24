#include <XBee.h>

XBee xbee = XBee();

// my 0x20
// dl 0x10

XBeeResponse response = XBeeResponse();
Rx16Response rx16 = Rx16Response();


const int ledPin = 13; // the pin that the LED is attached to
int incomingByte;      // a variable to read incoming serial data into

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  Serial1.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  xbee.setSerial(Serial1);
  xbee.begin(Serial1);
  Serial.print("Start");
  delay(1000);
}

uint8_t num = 0;
uint8_t data = 0;

void loop() {

  xbee.readPacket();

  if (xbee.getResponse().isAvailable()) {
    if (xbee.getResponse().getApiId() == RX_16_RESPONSE) {
      xbee.getResponse().getRx16Response(rx16);
      data = rx16.getData(0);
      num = rx16.getData(1);
      Serial.println(data + " " + num);
      if (data == 'H') {
        digitalWrite(ledPin, HIGH);
      }
      if (data == 'L') {
        digitalWrite(ledPin, LOW);
      }
    }
  } else if (xbee.getResponse().isError()) {
    Serial.println("Error: Response");
  }
}
