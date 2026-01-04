#include <Adafruit_NeoPixel.h>
#include <Wire.h>

#define LED_PIN 2
#define NUM_LEDS 18
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

#define MPU6050_ADDR 0x68

// Water animation parameters
float waterPosition = NUM_LEDS / 2.0;
float waterVelocity = 0.0;
const float damping = 0.90;
unsigned long lastUpdate = 0;
const int UPDATE_INTERVAL = 60;

// MPU6050 calibration
bool mpuFound = false;
float tiltOffset = 0.0;
bool calibrated = false;

void setup() {
  Serial.begin(115200);
  Serial.println("🔍 MPU6050 Calibration Starting...");
  
  Wire.begin();
  Wire.setClock(100000);
  delay(100);
  
  mpuFound = testMPU6050();
  
  strip.begin();
  strip.show();
  strip.setBrightness(80);
  
  Serial.println("=================================");
  if (mpuFound) {
    Serial.println("✅ MPU6050 Found! Calibrating...");
    setupMPU6050();
    calibrateMPU6050();
  } else {
    Serial.println("❌ MPU6050 Not Found! Using manual control");
    Serial.println("Send: l=left, r=right, s=stop");
  }
  Serial.println("=================================");
}

// FIXED: Added missing return statement
bool testMPU6050() {
  Serial.println("🔧 Testing MPU6050 connection...");
  
  Wire.beginTransmission(MPU6050_ADDR);
  byte error = Wire.endTransmission();
  
  Serial.print("I2C Error Code: ");
  Serial.println(error);
  
  if (error == 0) {
    Serial.println("✅ Device responded at address 0x68");
    
    // Read WHO_AM_I register
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(0x75); // WHO_AM_I register
    Wire.endTransmission(false);
    Wire.requestFrom(MPU6050_ADDR, 1, true);
    
    if (Wire.available()) {
      byte whoami = Wire.read();
      Serial.print("WHO_AM_I Register: 0x");
      Serial.println(whoami, HEX);
      
      if (whoami == 0x68) {
        Serial.println("✅ Valid MPU6050 detected");
        return true;
      } else {
        Serial.println("❌ Unexpected WHO_AM_I value");
        return false;
      }
    } else {
      Serial.println("❌ No response from WHO_AM_I");
      return false;
    }
  } else {
    Serial.println("❌ No device found at address 0x68");
    
    // Try alternative address
    Serial.println("🔧 Trying alternative address 0x69...");
    Wire.beginTransmission(0x69);
    error = Wire.endTransmission();
    
    if (error == 0) {
      Serial.println("✅ Device found at 0x69! Using this address.");
      return true;  // ← FIXED: Added missing return
    }
    
    return false;  // ← FIXED: This was missing
  }
}

void calibrateMPU6050() {
  Serial.println("🎯 Calibrating MPU6050...");
  Serial.println("Keep sensor FLAT and STILL for 2 seconds");
  
  float totalTilt = 0.0;
  int samples = 0;
  
  // Take 100 readings over 2 seconds
  for (int i = 0; i < 100; i++) {
    float currentTilt = readAccelerometerX();
    totalTilt += currentTilt;
    samples++;
    delay(20);
    
    if (i % 20 == 0) {
      Serial.print(".");
    }
  }
  
  // Calculate average offset
  tiltOffset = totalTilt / samples;
  
  Serial.println();
  Serial.print("✅ Calibration complete! Offset: ");
  Serial.println(tiltOffset, 4);
  Serial.println("Tilt values will now be zero when sensor is flat");
  
  calibrated = true;
}

float readAccelerometerX() {
  if (!mpuFound) return 0.0;
  
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x3B);
  byte error = Wire.endTransmission(false);
  
  if (error != 0) return 0.0;
  
  Wire.requestFrom(MPU6050_ADDR, 6, true);
  
  unsigned long start = millis();
  while (Wire.available() < 6 && millis() - start < 10) {
    delay(1);
  }
  
  if (Wire.available() < 6) return 0.0;
  
  int16_t accelX = Wire.read() << 8 | Wire.read();
  Wire.read(); Wire.read();
  Wire.read(); Wire.read();
  
  float rawTilt = accelX / 16384.0;
  
  // APPLY CALIBRATION OFFSET
  if (calibrated) {
    return rawTilt - tiltOffset;
  } else {
    return rawTilt;
  }
}

void setupMPU6050() {
  // Wake up MPU6050
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x6B); // PWR_MGMT_1
  Wire.write(0x00); // Wake up
  Wire.endTransmission(true);
  
  // Set accelerometer range to ±2g
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x1C); // ACCEL_CONFIG
  Wire.write(0x00); // ±2g
  Wire.endTransmission(true);
  
  delay(100);
  Serial.println("✅ MPU6050 configured");
}

void loop() {
  float tilt = 0.0;
  
  if (mpuFound) {
    // Use CALIBRATED MPU6050 data
    tilt = readAccelerometerX() * 0.5;
    
    // ADD DEAD ZONE - ignore very small movements
    if (abs(tilt) < 0.05) {  // Dead zone threshold
      tilt = 0.0;
    }
  } else {
    // Manual control
    if (Serial.available()) {
      char command = Serial.read();
      if (command == 'l') waterVelocity = -0.6;
      else if (command == 'r') waterVelocity = 0.6;
      else if (command == 's') waterVelocity = 0;
    }
    
    if (random(100) < 3) {
      waterVelocity += (random(2) ? 0.2 : -0.2);
    }
  }
  
  waterVelocity += tilt;
  
  unsigned long currentTime = millis();
  if (currentTime - lastUpdate >= UPDATE_INTERVAL) {
    lastUpdate = currentTime;
    
    updateWaterPhysics();
    updateLEDs();
    updateSerialVisualization();
    
    // Print CALIBRATED tilt data
    static unsigned long lastTiltPrint = 0;
    if (mpuFound && millis() - lastTiltPrint > 1000) {
      Serial.print("📐 Calibrated Tilt X: ");
      Serial.print(tilt, 3);
      Serial.print(" | Offset: ");
      Serial.println(tiltOffset, 3);
      lastTiltPrint = millis();
    }
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
  // Clear only nearby LEDs
  int clearStart = max(0, (int)waterPosition - 4);
  int clearEnd = min(NUM_LEDS - 1, (int)waterPosition + 4);
  
  for (int i = clearStart; i <= clearEnd; i++) {
    strip.setPixelColor(i, 0, 0, 0);
  }
  
  // Draw compact water glow
  int center = (int)waterPosition;
  strip.setPixelColor(center, 0, 50, 200);
  if (center > 0) strip.setPixelColor(center - 1, 0, 20, 100);
  if (center < NUM_LEDS - 1) strip.setPixelColor(center + 1, 0, 20, 100);
  
  strip.show();
}

void updateSerialVisualization() {
  char display[NUM_LEDS + 1];
  for (int i = 0; i < NUM_LEDS; i++) display[i] = '_';
  display[NUM_LEDS] = '\0';
  
  int center = (int)waterPosition;
  for (int i = -2; i <= 2; i++) {
    int pos = center + i;
    if (pos >= 0 && pos < NUM_LEDS) {
      if (i == 0) display[pos] = '~';
      else if (abs(i) == 1) display[pos] = '=';
      else display[pos] = '-';
    }
  }
  
  Serial.println(display);
}
