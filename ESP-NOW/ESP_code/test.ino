#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

#define LED 2

// REPLACE WITH YOUR ESP RECEIVER'S MAC ADDRESS
uint8_t broadcastAddress1[] = {0x80, 0x7D, 0x3A, 0x3B, 0xA4, 0x6F};
uint8_t broadcastAddress2[] = {0x80, 0x7D, 0x3A, 0x3B, 0xA4, 0x6D};
// uint8_t broadcastAddress2[] = {0xFF, , , , , };
// uint8_t broadcastAddress3[] = {0xFF, , , , , };

typedef struct test_struct {
  int x;
  int y;
} test_struct;

test_struct test;
test_struct test2;

String x_str;

String FR_received;
String RR_received;
String FL_received;
String RL_received;

String bf1;
String bf2;
String bf3;
String bf4;

int ind1;
int ind2;
int ind3;
int ind4;
int ind5;
int ind6;
int ind7;
int ind8;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  Serial.print("Packet to: ");
  // Copies the sender mac address to a string
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
  Serial.print(" send status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}


int incomingByte = 0; // for incoming serial data

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(100);

  WiFi.mode(WIFI_STA);
 
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  esp_now_register_send_cb(OnDataSent);
   
  // register peer
  esp_now_peer_info_t peerInfo;
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  // register first peer  
  memcpy(peerInfo.peer_addr, broadcastAddress1, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  // register second peer  
  memcpy(peerInfo.peer_addr, broadcastAddress2, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  
  pinMode(LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
}

void loop() {
  // reply only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    x_str = Serial.readString();

    ind1              = x_str.indexOf('/');             //finds location of first ,
    bf1               = x_str.substring(0, ind1);       //captures first data String
    ind2              = x_str.indexOf('/', ind1+1 );
    FR_received       = x_str.substring(ind1+1, ind2);       //captures first data String
    ind3              = x_str.indexOf('/', ind2+1 );    //finds location of second ,
    bf2               = x_str.substring(ind2+1, ind3);
    ind4              = x_str.indexOf('/', ind3+1 );
    RR_received       = x_str.substring(ind3+1, ind4);  //captures second data String
    ind5              = x_str.indexOf('/', ind4+1 );
    bf3               = x_str.substring(ind4+1, ind5);
    ind6              = x_str.indexOf('/', ind5+1 );            //finds location of first ,
    FL_received       = x_str.substring(ind5+1, ind6);
    ind7              = x_str.indexOf('/', ind6+1 );    //finds location of second ,
    bf4               = x_str.substring(ind6+1, ind7);
    ind8              = x_str.indexOf('/', ind7+1 );
    RL_received       = x_str.substring(ind7+1, ind8);

    test.x  = FR_received.toFloat();
    test.y  = RR_received.toFloat();
    test2.x = FL_received.toFloat();
    test2.y = RL_received.toFloat();

    Serial.print("Test.x: ");
    Serial.println(FR_received);
    // Serial.print("Test2.x: ");
    // Serial.print(test2.x);

    esp_err_t result1 = esp_now_send(
    broadcastAddress1, 
    (uint8_t *) &test,
    sizeof(test_struct));
    
    // if (result1 == ESP_OK) {
    //     Serial.println("Sent with success");
    // }
    // else {
    //     Serial.println("Error sending the data");
    // }

    esp_err_t result2 = esp_now_send(
    broadcastAddress2, 
    (uint8_t *) &test2,
    sizeof(test_struct));
    
    // if (result2 == ESP_OK) {
    //     Serial.println("Sent with success");
    // }
    // else {
    //     Serial.println("Error sending the data");
    // }
  }
}