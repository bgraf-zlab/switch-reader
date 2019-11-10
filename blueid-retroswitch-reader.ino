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

uint8_t openCloseCounter = 7; // 0 is closed; 11 is open

void loop() {
  // put your main code here, to run repeatedly:
  
  if (digitalRead(3) == HIGH && openCloseCounter > 0) {
    openCloseCounter--;
  }
  if (digitalRead(3) == LOW && openCloseCounter < NUM_LEDS) {
    openCloseCounter++                                                 ;
  }
  
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i < openCloseCounter) {
      leds[i] = CRGB(255, 0, 0);
    } else {
      leds[i] = CRGB(0, 255, 0);
    }
  }
  
  FastLED.show();
  delay(1000/20);
}
