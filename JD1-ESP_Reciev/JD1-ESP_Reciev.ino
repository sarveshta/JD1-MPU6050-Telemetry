#include <LiquidCrystal_I2C.h>
#include <esp_now.h>
#include <WiFi.h>

typedef struct struct_message {
  float x;
  float y;
  float z;
} struct_message;

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

// Create a struct_message called myData
struct_message myData;
LiquidCrystal_I2C lcd(0x3F, lcdColumns, lcdRows);  

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("X: ");
  Serial.println(myData.x);
  Serial.print("Y: ");
  Serial.println(myData.y);
  Serial.print("Z: ");
  Serial.println(myData.z);
  Serial.println();
}


void setup(){
  Serial.begin(9600);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));

  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
}

void loop(){
  // set cursor to first column, first row
  lcd.setCursor(0, 0);
  lcd.print("X:" + String(myData.x,2));

  lcd.setCursor(8,0);
  lcd.print("Y:" + String(myData.y,2));

  lcd.setCursor(0,1);
  lcd.print("Z:" + String(myData.z,2));
  

  // lcd.clear(); 
  delay(500);
}
