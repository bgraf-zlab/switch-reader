#include <FastLED.h>

#define LED_PIN     7
#define NUM_LEDS    11
#define BRIGHTNESS  32
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  delay( 3000 ); // power-up safety delay
  pinMode(3, INPUT_PULLUP);
  
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(BRIGHTNESS);

  for (int i = 0; i < NUM_LEDS; i++) {
    if (i % 2 == 0) {
      leds[i] = CRGB(0, 255, 0);
    } else {
      leds[i] = CRGB(0, 0, 255);
    }
  }
  FastLED.show();
  delay(1000);
}

//uint8_t openCloseCounter = 7; // 0 is closed; 11 is open
uint8_t wasActivatedCounter = 0;
uint8_t wasDeactivatedCounter = 0;

void loop() {

  bool deviceIsActive = digitalRead(3) == LOW;

  if (wasActivatedCounter == 0 && deviceIsActive) {
    wasActivatedCounter += 1; 
  }
  if (wasActivatedCounter > 0 && wasActivatedCounter < NUM_LEDS) {
    wasActivatedCounter += 1; 
  }
  if (wasActivatedCounter == NUM_LEDS && !deviceIsActive) {
    wasActivatedCounter = 0;
  }

  if (wasDeactivatedCounter == 0 && !deviceIsActive) {
    wasDeactivatedCounter += 1; 
  }
  if (wasDeactivatedCounter > 0 && wasDeactivatedCounter < NUM_LEDS) {
    wasDeactivatedCounter += 1; 
  }
  if (wasDeactivatedCounter == NUM_LEDS && deviceIsActive) {
    wasDeactivatedCounter = 0;
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    if (wasActivatedCounter == i) {
      leds[i] = CRGB(255, 0, 0);
    }
    if (wasDeactivatedCounter == i) {
      leds[i] = CRGB(0, 100, 0);
    }

    if (leds[i].r == 0) {
//      leds[i].g = micros() % 20 > 10 ? leds[i].g + 2 : leds[i].g - 2;
//      leds[i].g = max(100, min(155, leds[i].g));
      leds[i].g = 120 + sin(millis() / 1000.0 * 1.5 - i * (6.2 / NUM_LEDS)) * 30;
      leds[i].b = 10 + sin(millis() / 1000.0 * 2.83726 - i * (3.1 / NUM_LEDS)) * 7;
    }
  }
  
//  if (digitalRead(3) == HIGH && openCloseCounter > 0) {
//    openCloseCounter--;
//  }
//  if (digitalRead(3) == LOW && openCloseCounter < NUM_LEDS) {
//    openCloseCounter++                                                 ;
//  }
  
//  for (int i = 0; i < NUM_LEDS; i++) {
//    if (i < openCloseCounter) {
//      leds[i] = CRGB(255, 0, 0);
//    } else {
//      leds[i] = CRGB(0, 255, 0);
//    }
//  }
  
  FastLED.show();
  delay(1000/20);
}
