#include <ESP8266WiFi.h>
#include <espnow.h>

uint8_t bufferData[CHANNEL_COUNT];

void hexPrint(byte b) {
  if(b < 16) {
    Serial.print("0");
  }
  Serial.print(b, HEX);
}

void dumpBuffer() {
  Serial.println();
  for(int i = 0; i < CHANNEL_COUNT; i++) {
    if (i % 32 == 0) {
      Serial.println();
    }
    hexPrint(bufferData[i]);
  }
  Serial.println();
}

bool readBuffer = true;

void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  // the first 2 bits make up the offset
  unsigned short offset;
  memcpy(&offset, incomingData, 2);
  for(int i = 0 ; i < len - 2 ; i++) {
    // Seems like somehow 250 long packets still come in so 
    //  check here to avoid overflowing the bufferData
    if (offset+i >= CHANNEL_COUNT) {
      break ;
    }
    if(bufferData[offset+i] != incomingData[i+2]) {
      readBuffer = false;
      bufferData[offset+i] = incomingData[i + 2];
    }
  }
}

void setup() {
  Serial.begin(BAUD_RATE);
  delay(100);

  // Make sure you're in station mode    
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);

  // initialize the buffer data to all 0
  for(int i = 0 ; i < CHANNEL_COUNT ; i++) {
    bufferData[i] = 0;
  }
}

void loop() {
  // TODO: implement whatever you want to do with the data in buffer
  if (!readBuffer) {
    dumpBuffer();
    readBuffer = true;
  }
}
