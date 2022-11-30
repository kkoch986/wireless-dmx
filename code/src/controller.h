#include <LXESP8266UARTDMX.h>
#include <ESP8266WiFi.h>
#include <espnow.h>

uint8_t broadcastAddress[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
uint8_t bufferedData[CHANNEL_COUNT];
bool canSend = true;

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  canSend = true;
}

int dataRecv      = 0;
uint8_t *sendFrom = NULL;
uint8_t *sendTo   = NULL;
void gotDMXCallback(int slots) {
  dataRecv = slots - 1;
}

void setup() {
  delay(1000);

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != 0) {
    return;
  }
  
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

  // initialize the buffer data to all 0
  for(int i = 0 ; i < CHANNEL_COUNT ; i++) {
    bufferedData[i] = 0;
  }
  dataRecv = 0;

  // initialize the DMX reader
  ESP8266DMX.setDataReceivedCallback(&gotDMXCallback);
  ESP8266DMX.startInput();
}

uint8_t page[MAX_BUFFER_SIZE];
void loop() {
  // If we received DMX data,
  // copy it into the buffer and set the sendFrom pointer to start sending it
  if (dataRecv > 0) {
    for (int x = 0 ; x < dataRecv ; x++) {
      bufferedData[x] = ESP8266DMX.getSlot(x+1);
    }
    // if the DMX is coming in too fast, make sure we have time to send all of the pages
    // we are trying to send before accepting new data
    if (sendFrom == NULL) {
      sendFrom = &bufferedData[0];
      sendTo = sendFrom + dataRecv;
    }
    dataRecv = 0;
  }
  
  // If the sendFrom pointer is set and we arent waiting for a previous page to send
  // start sending another page.
  if(sendFrom != NULL && canSend) {
    // compute the offset and distance to the end from where we are
    const uint16_t offset = sendFrom - &bufferedData[0];
    const int waitingToSend = sendTo - (unsigned char *)offset; 
    const int pageSize = min(MAX_BUFFER_SIZE, 2 + waitingToSend);

    // save the first 2 bytes for the DMX offset
    for (int i = 0 ; i < pageSize ; i++) {
      page[i] = 0;
    }

    memcpy(&page, (unsigned char*)&(offset), 2);
    memcpy(&page[2], sendFrom, pageSize - 2);

    // send it and update the pointers
    esp_now_send(broadcastAddress, (uint8_t *)&page, pageSize);

    canSend = false;
    sendFrom += pageSize - 2;
    if (sendFrom >= sendTo) {
      sendFrom = NULL;
    }
  }
  delay(100);
}

