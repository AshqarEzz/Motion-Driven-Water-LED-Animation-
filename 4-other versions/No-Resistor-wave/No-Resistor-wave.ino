#include <Adafruit_NeoPixel.h>

#define LED_PIN 2
#define NUM_LEDS 18
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

float waterPosition = NUM_LEDS / 2.0;
float waterVelocity = 0.0;

void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.setBrightness(80);
  Serial.println("🌊 Water Flow - Add 4.7kΩ resistors for MPU6050");
}

void loop() {
  // Automatic wave motion
  waterVelocity += random(-10, 11) * 0.01;
  waterVelocity *= 0.95;
  
  waterPosition += waterVelocity;
  
  if (waterPosition < 2) { waterPosition = 2; waterVelocity *= -0.5; }
  if (waterPosition > NUM_LEDS-2) { waterPosition = NUM_LEDS-2; waterVelocity *= -0.5; }
  
  // Update LEDs
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, 0, 0, 0);
  }
  
  int center = (int)waterPosition;
  strip.setPixelColor(center, 0, 50, 200);
  if (center > 0) strip.setPixelColor(center-1, 0, 20, 100);
  if (center < NUM_LEDS-1) strip.setPixelColor(center+1, 0, 20, 100);
  
  strip.show();
  
  // Serial display
  char display[NUM_LEDS+1];
  for (int i = 0; i < NUM_LEDS; i++) display[i] = '_';
  display[NUM_LEDS] = '\0';
  
  int c = (int)waterPosition;
  for (int i = -1; i <= 1; i++) {
    int p = c + i;
    if (p >= 0 && p < NUM_LEDS) display[p] = (i == 0) ? '~' : '=';
  }
  
  Serial.println(display);
  delay(50);
}