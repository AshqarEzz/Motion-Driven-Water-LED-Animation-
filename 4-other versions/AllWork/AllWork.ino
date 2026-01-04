#include <Adafruit_NeoPixel.h>

// LED strip configuration
#define LED_PIN 2
#define NUM_LEDS 18
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Water animation parameters
float waterPosition = NUM_LEDS / 2.0;
float waterVelocity = 0.0;
const float damping = 0.90;
unsigned long lastUpdate = 0;
const int UPDATE_INTERVAL = 60;

void setup() {
  Serial.begin(115200);
  Serial.println("💧 Low-Power Water Flow Started");
  Serial.println("Send: l=left, r=right, s=stop");
  Serial.println("=================================");
  
  strip.begin();
  strip.show();
  strip.setBrightness(80); // Medium brightness for few LEDs
}

void loop() {
  // Manual control via serial
  if (Serial.available()) {
    char command = Serial.read();
    if (command == 'l') waterVelocity = -0.6;
    else if (command == 'r') waterVelocity = 0.6;
    else if (command == 's') waterVelocity = 0;
  }
  
  // Auto movement for demo
  waterVelocity += (random(100) < 5) ? (random(2) ? 0.3 : -0.3) : 0;
  
  unsigned long currentTime = millis();
  if (currentTime - lastUpdate >= UPDATE_INTERVAL) {
    lastUpdate = currentTime;
    
    updateWaterPhysics();
    updateLEDs();
    updateSerialVisualization();
  }
}

void updateWaterPhysics() {
  waterPosition += waterVelocity;
  waterVelocity *= damping;
  
  // Boundary with bounce
  if (waterPosition < 2.0) {
    waterPosition = 2.0;
    waterVelocity = -waterVelocity * 0.4;
  } else if (waterPosition > NUM_LEDS - 2.0) {
    waterPosition = NUM_LEDS - 2.0;
    waterVelocity = -waterVelocity * 0.4;
  }
}

void updateLEDs() {
  // Clear only the area around previous position for smoother transition
  int clearStart = max(0, (int)waterPosition - 4);
  int clearEnd = min(NUM_LEDS - 1, (int)waterPosition + 4);
  
  for (int i = clearStart; i <= clearEnd; i++) {
    strip.setPixelColor(i, 0, 0, 0);
  }
  
  // Draw compact water glow (only 3 LEDs max for power saving)
  int center = (int)waterPosition;
  
  // Main center LED - brightest
  strip.setPixelColor(center, 0, 50, 200);
  
  // Side LEDs - dimmer
  if (center > 0) strip.setPixelColor(center - 1, 0, 20, 100);
  if (center < NUM_LEDS - 1) strip.setPixelColor(center + 1, 0, 20, 100);
  
  // Optional: Very dim 4th LED for trail effect
  if (waterVelocity > 0.2 && center < NUM_LEDS - 2) {
    strip.setPixelColor(center + 2, 0, 5, 30);
  } else if (waterVelocity < -0.2 && center > 1) {
    strip.setPixelColor(center - 2, 0, 5, 30);
  }
  
  strip.show();
}

void updateSerialVisualization() {
  char display[NUM_LEDS + 1];
  
  // Initialize with empty
  for (int i = 0; i < NUM_LEDS; i++) {
    display[i] = '_';
  }
  display[NUM_LEDS] = '\0';
  
  int center = (int)waterPosition;
  
  // Create water effect in ASCII
  for (int i = -2; i <= 2; i++) {
    int pos = center + i;
    if (pos >= 0 && pos < NUM_LEDS) {
      if (i == 0) display[pos] = '~';      // Center - brightest
      else if (abs(i) == 1) display[pos] = '='; // Inner glow
      else display[pos] = '-';             // Outer glow
    }
  }
  
  // Add motion trail
  if (waterVelocity > 0.1 && center < NUM_LEDS - 3) {
    display[center + 2] = '.';
  } else if (waterVelocity < -0.1 && center > 2) {
    display[center - 2] = '.';
  }
  
  Serial.println(display);
  
  // Debug info
  static unsigned long lastDebug = 0;
  if (millis() - lastDebug > 2000) {
    Serial.print("💧 Pos: ");
    Serial.print(waterPosition, 1);
    Serial.print(" | 📈 Vel: ");
    Serial.print(waterVelocity, 2);
    Serial.print(" | 🔌 LEDs on: 3-4");
    Serial.println();
    lastDebug = millis();
  }
}

