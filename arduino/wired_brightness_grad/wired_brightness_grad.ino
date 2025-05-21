/*// include libraries
#include <FastLED.h>
#include <SoftwareSerial.h>

// declare user constants
#define NUM_LEDS 50
#define FADE_SPEED 10  // higher = slower
//#define DIM 0        // 0 - 255, 255 max brightness
const int dataPin = A0;
int DIM = 0;
char grad = 'u';


// declare variables
uint8_t r = 0;
uint8_t g = 0;
uint8_t b = 0;
char buffer[50];
uint8_t pointer = 0;
char data;

// declare objects
CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);
  // initialize LED
  FastLED.addLeds<WS2812, dataPin, GRB>(leds, NUM_LEDS);
}

void loop() {
  // incoming data from bluetooth
  if (Serial.available() > 0) {
    while (Serial.available()) {
      //Serial.println(Serial.peek());
      data = Serial.read();
      Serial.print("Data received: ");
      Serial.println(data);
      if (data != 0x0A && data != 0x0D) {
        DIM = data;
      }
      
    }
   }
  //FastLED.setBrightness(DIM);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::FairyLight;
  }
  if (DIM < 90 and data == 'u') {
    delay(20);
    DIM++;
  } 
  if (DIM == 90 and data == 'u') {
    delay(3000);
    data = 'd';
    DIM--;
  }
  if (DIM < 90 and DIM > 10 and data == 'd') {
    delay(20);
    DIM--;  
  }
  if (DIM == 10 and data == 'd') {
    delay(3000);
    data = 'u';
  }
  Serial.print("DIM is ");
  Serial.println(DIM);
  FastLED.setBrightness(DIM);
  FastLED.show();
}*/

// include libraries
#include <FastLED.h>
#include <SoftwareSerial.h>

// declare user constants
#define NUM_LEDS 50
#define FADE_SPEED 10  // higher = slower
//#define DIM 0        // 0 - 255, 255 max brightness
const int dataPin = A0;
int DIM = 0;
char grad ='a';


// declare variables
uint8_t r = 0;
uint8_t g = 0;
uint8_t b = 0;
/*char buffer[50];
uint8_t pointer = 0;*/
int bright;

// declare objects
CRGB leds[NUM_LEDS];
//SoftwareSerial bt(2, 3);

void setup() {
  Serial.begin(9600);
  // initialize LED
  FastLED.addLeds<WS2812, dataPin, GRB>(leds, NUM_LEDS);
}

void loop() {
  // incoming data from bluetooth

   if (Serial.available() > 0) {
    char incomingByte = Serial.read();
    if (incomingByte == 'q') {
      Serial.println("Exiting script");
      while (true) {
        FastLED.setBrightness(10);
      }
    }
    if (incomingByte != 0x0A && incomingByte != 0x0D && incomingByte != ' ' && incomingByte != '\n' && incomingByte != '\r') {
      grad = incomingByte;
    }
    
    Serial.print("I got this ");
    Serial.println(grad);
   }
  //FastLED.setBrightness(DIM);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::FairyLight;
  }

  if (grad == 'a') {
    FastLED.setBrightness(10);
  }

  if ( DIM < 90 and grad == 'u') {
    DIM++;
    FastLED.setBrightness(DIM);
    Serial.println(DIM);
    delay(20);
  }

  if (DIM == 90 and grad == 'u') {
    delay(5000);
    grad = 'd';
    DIM--;
  }
  if ( DIM < 90 and DIM > 1 and grad == 'd') {
    DIM--;
    FastLED.setBrightness(DIM);
    Serial.println(DIM);
    delay(20);
  }
  if (DIM == 1 and grad == 'd') {
    delay(3000);
    grad = 'u';
  }
  /*if (g < 200) {
    delay(1000);
    g += 10; 
    Serial.println(g);
  }*/
  FastLED.show();
}
