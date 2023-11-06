#include <Arduino_FreeRTOS.h>
#include <FastLED.h>
#define LED_PIN 2
#define NUM_LEDS 29
#define LED_CONTROL 3
#define Mid 285
#define Mid2 280
#define Step 1
int start =1;
CRGB leds[NUM_LEDS];
// define two tasks for Blink & AnalogRead
void TaskBlink( void *pvParameters );
void TaskAnalogRead( void *pvParameters );
 
// the setup function runs once when you press reset or power the board
void setup() {
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(A1,INPUT);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  FastLED.clear();
  FastLED.show();
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(6,INPUT);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }
 
  // Now set up two tasks to run independently.
  xTaskCreate(
    TaskBlink
    ,  "Blink"   // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  1  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );
 
  xTaskCreate(
    TaskAnalogRead
    ,  "AnalogRead"
    ,  128  // Stack size
    ,  NULL
    ,  2  // Priority
    ,  NULL );
 
  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}
 
void loop()
{
  // Empty. Things are done in Tasks.
}
 
/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/
 
void TaskBlink(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
 

  pinMode(LED_BUILTIN, OUTPUT);
 
  for (;;) 
  {

    digitalWrite(LED_BUILTIN, LOW); 

  }
}
 void wait(){
   for(int i = 0;i<=29;i++){
     leds[i]=CRGB(8*i,255-(8*i),8*i);
     FastLED.setBrightness(100); 
     FastLED.show();
    delay(100);
   }
 }
void TaskAnalogRead(void *pvParameters)  
{
  (void) pvParameters;
  

 int counter = 0;
 int count = 0;
  for (;;)
  {
    int Touch1 = digitalRead(4);
  int Touch2 = digitalRead(5);
  int Touch3 = digitalRead(6);
 int  s= analogRead(A1);
  if(Touch1 == 0 && Touch2 == 0 && Touch3 ==0){
    RUN(1,1,1);
    }
  if(Touch1 == 0 && Touch2 == 0 && Touch3 ==1){
    //led[1] = CRGB(255,255,0);
    //onTo(0,29,0,0,255);
    RUN(0,0,255);
    }
  if(Touch1 == 0 && Touch2 == 1 && Touch3 ==0){
    //led[1] = CRGB(255,255,255);
    //onTo(0,29,0,255,0);
    RUN(0,255,0);
    }
  if(Touch1 == 0 && Touch2 == 1 && Touch3 ==1){
    //led[0] = CRGB(255,0,255);
    //onTo(0,29,0,255,255);
    RUN(0,255,255);
    }
  if(Touch1 == 1 && Touch2 == 0 && Touch3 ==0){
    //led[1] = CRGB(0,0,0);
    //onTo(0,29,255,0,0);
    RUN(255,0,0);
    }
  if(Touch1 == 1 && Touch2 == 0 && Touch3 ==1){
    //led[0] = CRGB(0,255,0);
    //onTo(0,29,255,0,255);
    RUN(255,0,255);
    }
  if(Touch1 == 1 && Touch2 == 1 && Touch3 ==0){
    //led[0] = CRGB(0,0,255);
    //onTo(0,29,255,255,0);
    RUN(255,255,0);
    }
  if(Touch1 == 1 && Touch2 == 1 && Touch3 ==1){
    //led[0] = CRGB(0,255,255);
    //onTo(0,29,255,255,255);
    RUNRANDOM();
  }





    if(s >(Mid2-3) && s <(Mid+3)){
      counter++;
    } 
    else{
      counter = 0;
      count = 0;
    }
    if(count != 3){
      if (counter == 50){
      wait();
      counter = 0;
      count++;
      //digitalWrite(13,LOW);
      //vTaskDelay(1000);
      }
      
    }
    else vTaskDelay(100000);
    
  }
}
void onTo(int batdau , int ketthuc, int r, int g, int b){
  for(int i = batdau;i<=ketthuc;i++){
    leds[i] = CRGB(r, g, b );
    FastLED.setBrightness(100);  
    }
    FastLED.show();
  }
void on(int vitri, int r, int g, int b){
  leds[vitri] = CRGB(r,g,b);
  FastLED.setBrightness(100);
  FastLED.show();
  //flshow
  }
void RUN(int r,int g,int b){
  int s = analogRead(A1);
  Serial.println(s);
  Serial.print(digitalRead(4));
  Serial.print(digitalRead(5));
  Serial.println(digitalRead(6));
  if(s==Mid){onTo(0,1,r,g,b);}
  if(s==Mid+1||s==Mid2-1){onTo(0,3,r,g,b);}
  if(s==Mid+2||s==Mid2-2){onTo(0,5,r,g,b);}
  if(s==Mid+3||s==Mid2-3){onTo(0,6,r,g,b);}
  if(s==Mid+4||s==Mid2-4){onTo(0,8,r,g,b);}
  if(s==Mid+5||s==Mid2-5){onTo(0,9,r,g,b);}
  if(s==Mid+6||s==Mid2-6){onTo(0,11,r,g,b);}
  if(s==Mid+7||s==Mid2-7){onTo(0,12,r,g,b);}
  if(s==Mid+8||s==Mid2-8){onTo(0,13,r,g,b);}
  if(s==Mid+9||s==Mid2-9){onTo(0,14,r,g,b);}
  if(s==Mid+10||s==Mid2-10){onTo(0,15,r,g,b);}
  if(s==Mid+11||s==Mid2-11){onTo(0,17,r,g,b);}
  if(s==Mid+12||s==Mid2-12){onTo(0,19,r,g,b);}
  if(s==Mid+13||s==Mid2-13){onTo(0,21,r,g,b);}
  if(s==Mid+14||s==Mid2-14){onTo(0,23,r,g,b);}
  if(s==Mid+15||s==Mid2-15){onTo(0,25,r,g,b);}
  if(s==Mid+16||s==Mid2-16){onTo(0,27,r,g,b);}
  if(s==Mid+17||s==Mid2-17){onTo(0,29,r,g,b);}
  FastLED.show();
  delay(3);
  for(int i = 0;i<=29;i++){
    leds[i]= CRGB(1,1,1);
    //FastLED.setBrightness(10);
    FastLED.show();
    }
  }
void RUNRANDOM(){
  int s = analogRead(A1);
  Serial.println(s);
  Serial.print(digitalRead(4));
  Serial.print(digitalRead(5));
  Serial.println(digitalRead(6));
  if(s==Mid){onTo(0,1,0,0,255);}
  if(s==Mid+1||s==Mid2-1){onTo(0,1,0,255,0);}
  if(s==Mid+2||s==Mid2-2){onTo(0,1,0,255,255);}
  if(s==Mid+3||s==Mid2-3){onTo(0,6,255,0,0);}
  if(s==Mid+4||s==Mid2-4){onTo(0,8,255,0,255);}
  if(s==Mid+5||s==Mid2-5){onTo(0,9,255,255,0);}
  if(s==Mid+6||s==Mid2-6){onTo(0,11,0,0,255);}
  if(s==Mid+7||s==Mid2-7){onTo(0,12,0,255,0);}
  if(s==Mid+8||s==Mid2-8){onTo(0,13,0,255,255);}
  if(s==Mid+9||s==Mid2-9){onTo(0,14,255,0,0);}
  if(s==Mid+10||s==Mid2-10){onTo(0,15,255,0,255);}
  if(s==Mid+11||s==Mid2-11){onTo(0,17,255,255,0);}
  if(s==Mid+12||s==Mid2-12){onTo(0,19,255,255,255);}
  if(s==Mid+13||s==Mid2-13){onTo(0,21,0,255,255);}
  if(s==Mid+14||s==Mid2-14){onTo(0,23,255,0,0);}
  if(s==Mid+15||s==Mid2-15){onTo(0,25,255,255,0);}
  if(s==Mid+16||s==Mid2-16){onTo(0,27,0,255,0);}
  if(s==Mid+17||s==Mid2-17){onTo(0,29,255,0,255);}
  FastLED.show();
  delay(3);
  for(int i = 0;i<=29;i++){
    leds[i]= CRGB(1,1,1);
    //FastLED.setBrightness(10);
    FastLED.show();
    }
  }
