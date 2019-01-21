#include <EEPROM.h>
#include <XBee.h>


unsigned int counter = 0;
int MAX = 100;

XBee xbee = XBee();

unsigned long start_times[100];
unsigned long end_times[100];
int8_t rssis[100];
unsigned long wait_timer;
unsigned long last_send_time;

int remoteAddress = 0x10;
uint8_t payload[] = {0};
Tx16Request tx = Tx16Request(remoteAddress, payload, sizeof(payload));
TxStatusResponse txStatus = TxStatusResponse();

Rx16Response rx16 = Rx16Response();

unsigned long initialTime = millis();

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  xbee.setSerial(Serial1); 
  last_send_time = millis();

  for (int i = 0; i < MAX; i++) {
    start_times[i] = 0;
    end_times[i] = 0;
    rssis[i] = 0;
  }
}

void loop() {
  if (millis() - initialTime > 5000) {
    // send
  
    if (counter < MAX && millis() - last_send_time > 50) {
      payload[0] = counter;
      start_times[counter] = millis();
      last_send_time = start_times[counter];
      xbee.send(tx);
      Serial.print("SEND: ");
      Serial.println(payload[0]);
      counter++;

    } else if (counter == MAX) {
      wait_timer = millis();
      counter++;
    } else if (counter == MAX + 1) {
      if (millis() - wait_timer > 1000) {
        counter++;
        int error_cnt = 0;
        for (int i = 0; i < MAX; i++) {
          int duration;
          if (end_times[i] == 0) {
            error_cnt++;
            duration = -1;
          } else {
            duration = end_times[i] - start_times[i];
          }
          EEPROM.put(i*5, duration);
          EEPROM.put(i*5 + 4, rssis[i]);
          Serial.print(i);
          Serial.print("    DURATION: ");
          Serial.print(duration);
          Serial.print("    -    RSSI: ");
          Serial.println(rssis[i]);
        }
        EEPROM.put(MAX * 5, error_cnt);
        Serial.print("PER (in %): ");
        Serial.println(error_cnt);
        }
    }
  } 

  // receive
 xbee.readPacket();
  while (xbee.getResponse().isAvailable()) {        
      // got a response!
     if (xbee.getResponse().getApiId() == RX_16_RESPONSE) {
        xbee.getResponse().getRx16Response(rx16);
        uint8_t data = rx16.getData(0);
        int rssi = -rx16.getRssi();
        Serial.print("RECEIVE: ");
        Serial.print(data);
        Serial.print(" - ");
        Serial.println(rssi);
        end_times[data] = millis();
        rssis[data] = rssi;
     }
      // should be a znet tx status             
    if (xbee.getResponse().getApiId() == TX_STATUS_RESPONSE) {
       xbee.getResponse().getTxStatusResponse(txStatus);
       Serial.println("TX_STATUS_RESPONSE");
      }
    xbee.readPacket();
  }


  writeEEPROM(0, 0, 0, 0);
}
