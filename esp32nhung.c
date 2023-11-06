#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

#include <WiFi.h>
#include <FirebaseESP32.h>
#include <ArduinoJson.h>
#define WIFI_SSID "302"
#define WIFI_PASSWORD "23456789"
#define RXp2 16
#define TXp2 17
FirebaseData firebaseData;
String path = "/";
FirebaseJson json;
#define FIREBASE_HOST "aatqka-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "zIW9tKDUXkU0HMUhdD1Bwwo1nk3HtqO4TtY5T39m"
void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);
  // put your setup code here, to run once:
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  if(!Firebase.beginStream(firebaseData,path)){
    Serial.println("REASON: "+firebaseData.errorReason());
    Serial.println();

  }
  Serial.print("Connected with IP:");
  Serial.println(WiFi.localIP());
  Serial.println();
  Firebase.setReadTimeout(firebaseData,1000*60);
  Firebase.setwriteSizeLimit(firebaseData,"tiny");
  //int nhip = Serial2.readString().toInt();
  //Firebase.setInt(firebaseData,"/nhiptimofthai/nhiptim",nhip);

}

void loop() {
  String My_S = Serial2.readString();
  int nhiet = My_S.substring(0,2).toInt();
  int nhip = My_S.substring(2,4).toInt();
  // put your main code here, to run repeatedly:
  //int nhip =Serial2.readString().toInt();
  //
  
   if(nhip!=0){
  Firebase.setInt(firebaseData,"/chinhno/Nhiptim",nhip);
  Firebase.setInt(firebaseData,"/chinhno/Nhietdo",nhiet);
  //delay(1000);
  }
  

}
