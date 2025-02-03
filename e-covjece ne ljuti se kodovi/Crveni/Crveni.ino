//Ovo nije finalna verzija koda
//Ovaj kod će dobiti nadogradnju sa dvosmjernom komunikacijom i ANIMACIJAMA
//#include <Adafruit_Neopixel.h>
#include <esp_now.h>
#include <WiFi.h>
#include <TFT_eSPI.h>
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();

#define BTN_A  32  // Change 12 to the actual GPIO pin you're using for the button
#define UPDOWN 35
#define LEFTRIGHT 34
uint8_t broadcastAddress[] = {0xA0, 0x85, 0xE3, 0xE6, 0x8A, 0xEC};
bool igrac[5] = {0, 0, 0, 0, 0};
typedef struct struct_message {
    //int kockabroj;
    bool klik = true;
    bool igracc[5];
} struct_message;

struct_message myData;

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Last Packet Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}
void setup() {
  Serial.begin(115200);
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_RED);
  tft.setTextSize(2);
  tft.setCursor(30, 10);
  tft.println("e-covjece, ne ljuti se");
  tft.setTextSize(6);
  tft.setCursor(60, 80);
  tft.println("VIDI X");
  pinMode(BTN_A, INPUT_PULLUP);
  pinMode(UPDOWN, INPUT_PULLUP);
  pinMode(LEFTRIGHT, INPUT_PULLUP);

  WiFi.mode(WIFI_STA);  // Set ESP32 as Wi-Fi Station

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  
  if (digitalRead(BTN_A) == LOW) {  // Button pressed (active LOW)
    delay(50);  // Debounce delay
    while (digitalRead(BTN_A) == LOW);  // Wait for button release

    myData.klik = true;
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

    if (result == ESP_OK) {
      Serial.print("Sent: ");
      //Serial.println(myData.kockabroj);
    } else {
      Serial.println("Error sending data");
    }

    delay(500);  // Small delay to prevent multiple triggers
    myData.klik = false;
  }
  
  if(analogRead(UPDOWN) > 2048){
    myData.igracc[1] = true;
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    if (result == ESP_OK) {
      Serial.print("Sent UPDOWN: ");
      //Serial.println(myData.kockabroj);
    } else {
      Serial.println("Error sending data");
    }
    delay(500);
    myData.igracc[1] = false;
  }else if(analogRead(UPDOWN) < 2048 && analogRead(UPDOWN) > 10){
    myData.igracc[2] = true;
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    if (result == ESP_OK) {
      Serial.print("Sent UPDOWN: ");
      //Serial.println(myData.kockabroj);
    } else {
      Serial.println("Error sending data");
    }
    delay(500);
    myData.igracc[2] = false;
  }if(analogRead(LEFTRIGHT) > 2048){
    myData.igracc[3] = true;
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    if (result == ESP_OK) {
      Serial.print("Sent UPDOWN: ");
      //Serial.println(myData.kockabroj);
    } else {
      Serial.println("Error sending data");
    }
    delay(500);
    myData.igracc[3] = false;
  }else if(analogRead(LEFTRIGHT) < 2048 && analogRead(LEFTRIGHT) > 10){
    myData.igracc[4] = true;
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    if (result == ESP_OK) {
      Serial.print("Sent UPDOWN: ");
      //Serial.println(myData.kockabroj);
    } else {
      Serial.println("Error sending data");
    }
    delay(500);
    myData.igracc[4] = false;
  }
}
