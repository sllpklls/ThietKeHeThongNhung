#include <Wire.h>
#include <Arduino_FreeRTOS.h>
#include "MAX30105.h"
#include "heartRate.h"
#include <LiquidCrystal_I2C.h>
#include <FastLED.h>
#define LED_PIN 2 //chân điều khiển led
#define NUM_LEDS 8
CRGB leds[NUM_LEDS];
LiquidCrystal_I2C lcd(0x27,16,2);
MAX30105 particleSensor;

//const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
//byte rates[RATE_SIZE]; //Array of heart rates
//byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred

float beatsPerMinute;
//int beatAvg;

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  FastLED.clear();
  FastLED.show();
  lcd.init();
  lcd.clear();
  lcd.backlight();
  // Initialize sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("chua ket noi dc cam bien ");
    while (1);
  }
  Serial.println("dat ngon tay len cam bien");

  particleSensor.setup(); 
  particleSensor.setPulseAmplitudeRed(0x0A);
  particleSensor.setPulseAmplitudeGreen(0);

  xTaskCreate(
    TaskRead
    ,  "Read"   // A name just for humans
    ,  1024  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,   1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );
    
}


void TaskRead(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  pinMode(3,OUTPUT);
 
  for (;;) 
  {
    
    long irValue = particleSensor.getIR();
    Serial.println(irValue);
    if (checkForBeat(irValue) == true && irValue >50000) {
      long delta = millis() - lastBeat;
      lastBeat = millis();
      //delay(100);
      beatsPerMinute = 60 / (delta / 1000.0);
      lcd.setCursor(0,0);
      lcd.print("Nhip tim: ");
      lcd.setCursor(11,0);
    
      if(beatsPerMinute<99){
        lcd.print((int)beatsPerMinute);
      }
      lcd.setCursor(0,1);
      lcd.print("Nhiet do: ");
      lcd.setCursor(11,1);
      lcd.print(particleSensor.readTemperature());
      Serial.println(beatsPerMinute);
      
      if(beatsPerMinute>50&&beatsPerMinute<85){
      for(int i=0;i<8;i++){
      leds[i]=CRGB(0,255,0);
      FastLED.setBrightness(100);
      FastLED.show();
      digitalWrite(3,LOW);
          //delay(100);
        } 
      }
      else{
        for(int i=0;i<8;i++){
          leds[i]=CRGB(255,0,0);
          FastLED.setBrightness(100);
          FastLED.show();
          digitalWrite(3,HIGH);
        } 
      }
    }
      if (irValue < 50000){
      
      lcd.clear();
      lcd.setCursor(0,0);
      Serial.print(" No finger?");
      lcd.print("no finger");
      delay(100);
      }
    
    
  }
}




void loop() {
  /*long irValue = particleSensor.getIR();

  if (checkForBeat(irValue) == true) {
    long delta = millis() - lastBeat;
    lastBeat = millis();

    beatsPerMinute = 60 / (delta / 1000.0);

  
  }

  lcd.setCursor(0,0);
  lcd.print("Nhip tim: ");
  lcd.setCursor(11,0);
  
  if(beatsPerMinute<99){
    lcd.print((int)beatsPerMinute);
  }
  
  //lcd.clear();
  Serial.println(beatsPerMinute);
  //lcd.setCursor(0,1);
  //lcd.print("Nhiet do: ");
  //lcd.setCursor(11,1);
  //lcd.print(particleSensor.readTemperature());
  if(beatsPerMinute>50&&beatsPerMinute<85){
    for(int i=0;i<8;i++){
      leds[i]=CRGB(0,255,0);
      FastLED.setBrightness(100);
      FastLED.show();
      //delay(100);
    } 
  }
  else{
    for(int i=0;i<8;i++){
      leds[i]=CRGB(255,0,0);
      FastLED.setBrightness(100);
      FastLED.show();
    } 

    
  }

  if (irValue < 50000){
    lcd.clear();
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    Serial.print(" No finger?");
    lcd.print("no finger");
    delay(1000);
    
    }
  Serial.println();*/
}