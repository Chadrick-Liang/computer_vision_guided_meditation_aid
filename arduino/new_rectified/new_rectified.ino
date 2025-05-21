// include libraries
#include <FastLED.h>
#include <SoftwareSerial.h>

// declare user constants
#define NUM_LEDS 50
#define FADE_SPEED 10  // higher = slower
#define DIM 10        // 0 - 255, 255 max brightness

// declare constants

enum stages_t {
  STAGE_1,
  STAGE_2,
  STAGE_3
};

// declare pin
const int dataPin = A0;

// declare variables
uint8_t r, g, b, stage;
int lastMode;
int mode = -1;
long lastFadeTime;
int buffer[100];
uint8_t pointer = 0;

// declare objects
CRGB leds[NUM_LEDS];
SoftwareSerial bt(2, 3);

void setup() {
  // initialize bluetooth port
  bt.begin(9600);
  Serial.begin(9600);
  // initialize LED
  FastLED.addLeds<WS2812, dataPin, GRB>(leds, NUM_LEDS);
}

void loop() {
  // incoming data from bluetooth
  if (bt.available()) {
    // while data is coming in, read it
    while (bt.available()) {
      // read data
      int value = bt.parseInt();
      Serial.print("Received value: ");
      Serial.println(value);
      if (value == 0) {
        Serial.print("Prev value was ");
        Serial.println(buffer[pointer - 1]);
        if (buffer[pointer - 1] == 4) {
          value = 5;
        } else if (buffer[pointer - 1] == 5) {
          value = 4;
        }
        Serial.println("now rectified");
      }

      buffer[pointer++] = value;
      mode = value;
      Serial.print("inserted value: ");
      Serial.println(buffer[pointer - 1]);
      Serial.print("current pointer: ");
      Serial.println(pointer);
    }

    if (lastMode != mode) {
      if (mode == 5) {
        r = 255;
        g = 0;
        b = 0;
        stage = STAGE_1;
      }
      lastMode = mode;
    }
  }

  switch (mode) {
    case -1:
      FastLED.setBrightness(DIM);
      // set all LEDs to warm white
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::FairyLight;
      }
    case 4:
      FastLED.setBrightness(DIM);
      // set all LEDs to warm white
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::FairyLight;
      }
      break;
    case 5:
      // fade leds every set interval
      if (millis() - lastFadeTime > FADE_SPEED) {
        FastLED.setBrightness(100);
        // set all LEDs to RGB values
        for (int i = 0; i < NUM_LEDS; i++) {
          leds[i] = CRGB(r, g, b);
        }

        switch (stage) {
          // fade to green
          case STAGE_1:
            if (g < 100) {
              r--;
              g++;
            } else {
              stage = STAGE_2;
            }
            break;
          // fade to blue
          case STAGE_2:
            if (b < 100) {
              g--;
              b++;
            } else {
              stage = STAGE_3;
            }
            break;
          // fade to red
          case STAGE_3:
            if (r < 100) {
              b--;
              r++;
            } else {
              stage = STAGE_1;
            }
            break;
        }
        lastFadeTime = millis();
      }
      break;
  }
  FastLED.show();
}
