#include <XBee.h>

XBee xbee = XBee();

// my 0x10
// dl 0x20

uint8_t payload[] = {0,0};
Tx16Request tx = Tx16Request(0x20, payload, sizeof(payload));

int ledPin = 13;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  //Serial1.begin(9600);
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  xbee.setSerial(Serial);
  delay(1000);
}

int num = 0;

// the loop function runs over and over again forever
void loop() {
  payload[1] = num;
  num += 1;
  num %= 255;
  //Serial.println("Send H");
  //Serial.println("H");   // turn the LED on (HIGH is the voltage level)
  payload[0] = 'H';
  xbee.send(tx);
  digitalWrite(ledPin, HIGH);
  delay(random(100, 1000));                       // wait for a second
  
  //Serial.println("Send L");
  //Serial.println("L");    // turn the LED off by making the voltage LOW
  payload[0] = 'L';
  xbee.send(tx);
  digitalWrite(ledPin, LOW);
  delay(random(100, 1000));                       // wait for a second
}
