#include <Adafruit_NeoPixel.h>
#define LED_PIN 2
#define NUM_LEDS 18
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(30); // Very low brightness
  strip.show();
}

void loop() {
  // Simple chase pattern
  for(int i=0; i<NUM_LEDS; i++) {
    strip.clear();
    strip.setPixelColor(i, 0, 0, 100); // Dim blue
    strip.show();
    delay(100);
  }
}
