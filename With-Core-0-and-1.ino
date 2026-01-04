#include <IRremote.hpp>

#include <IRremote.hpp>

/*
 * FINAL WORKING CODE - Motors were wired backwards
 * Test results showed: 
 * - Right Pattern A = BACKWARD (wrong)
 * - Right Pattern B = No movement (wiring issue)
 * - Left Pattern A = BACKWARD (wrong)
 * - Left Pattern B = FORWARD (correct)
 * 
 * Solution: Use Pattern B for forward movement
 */

#include <Servo.h>

// Pin Definitions
#define TRIG_PIN 7
#define ECHO_PIN 6
#define SERVO_PIN 9

// Motor Pins (AFTER wire swap)
#define IN1 8      // OUT1 - Right RED wires
#define IN2 4      // OUT2 - Right BLACK wires
#define IN3 10     // OUT3 - Left BLACK wires
#define IN4 11     // OUT4 - Left RED wires

// Servo positions
#define CENTER 90
#define LEFT_ANGLE 60
#define RIGHT_ANGLE 120

// Distance settings (cm)
#define CLEAR_DISTANCE 40
#define WARNING_DISTANCE 25
#define MIN_DISTANCE 15

// Timing
#define SCAN_DELAY 400
#define TURN_TIME 350
#define REVERSE_TIME 500

Servo myServo;

void setup() {
  Serial.begin(9600);
  Serial.println("=== FINAL WORKING CAR ===");
  Serial.println("Motors were wired backwards - NOW FIXED");
  
  // Setup pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  myServo.attach(SERVO_PIN);
  myServo.write(CENTER);
  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Verify forward movement
  Serial.println("Testing forward movement (should go STRAIGHT)...");
  moveForward();
  delay(2000);
  stopMotors();
  
  Serial.println("Ready in 3 seconds...");
  delay(3000);
}

void loop() {
  // Check forward distance
  int distance = getDistance();
  Serial.print("Front: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // Decision making
  if (distance > CLEAR_DISTANCE) {
    // Clear path
    Serial.println(">>> GOING STRAIGHT");
    moveForward();
  }
  else if (distance > WARNING_DISTANCE) {
    // Getting close - continue but slower
    Serial.println(">>> CAUTION - CONTINUING");
    moveForward();
    delay(100);
    stopMotors();
    delay(100);
  }
  else if (distance > MIN_DISTANCE) {
    // Obstacle detected
    Serial.println("!!! OBSTACLE - AVOIDING");
    stopMotors();
    delay(300);
    avoidObstacle();
  }
  else {
    // Too close - emergency
    Serial.println("!!! TOO CLOSE - REVERSING");
    emergencyReverse();
  }
  
  delay(100);
}

// ========== CORRECTED MOTOR FUNCTIONS ==========
/*
YOUR MOTORS ARE WIRED BACKWARDS:
- Pattern A (INx=HIGH, INx+1=LOW) = BACKWARD
- Pattern B (INx=LOW, INx+1=HIGH) = FORWARD
*/

void moveForward() {
  // Pattern B for BOTH sides = FORWARD
  // Right: IN1=LOW, IN2=HIGH
  // Left: IN3=LOW, IN4=HIGH
  
  digitalWrite(IN1, LOW);    // Right LOW
  digitalWrite(IN2, HIGH);   // Right HIGH
  
  digitalWrite(IN3, LOW);    // Left LOW  
  digitalWrite(IN4, HIGH);   // Left HIGH
  
  // Serial.println("Motors: R(L,H) L(L,H)");
}

void moveBackward() {
  // Pattern A for BOTH sides = BACKWARD
  // Right: IN1=HIGH, IN2=LOW
  // Left: IN3=HIGH, IN4=LOW
  
  digitalWrite(IN1, HIGH);   // Right HIGH
  digitalWrite(IN2, LOW);    // Right LOW
  
  digitalWrite(IN3, HIGH);   // Left HIGH
  digitalWrite(IN4, LOW);    // Left LOW
  
  // Serial.println("Motors: R(H,L) L(H,L)");
}

void turnLeft() {
  // For LEFT turn:
  // Right motors: FORWARD (push right side forward)
  // Left motors: BACKWARD (pull left side back)
  
  // Right forward: Pattern B
  digitalWrite(IN1, LOW);    // Right LOW
  digitalWrite(IN2, HIGH);   // Right HIGH
  
  // Left backward: Pattern A  
  digitalWrite(IN3, HIGH);   // Left HIGH
  digitalWrite(IN4, LOW);    // Left LOW
  
  Serial.println("Turning LEFT");
}

void turnRight() {
  // For RIGHT turn:
  // Right motors: BACKWARD (pull right side back)
  // Left motors: FORWARD (push left side forward)
  
  // Right backward: Pattern A
  digitalWrite(IN1, HIGH);   // Right HIGH
  digitalWrite(IN2, LOW);    // Right LOW
  
  // Left forward: Pattern B
  digitalWrite(IN3, LOW);    // Left LOW
  digitalWrite(IN4, HIGH);   // Left HIGH
  
  Serial.println("Turning RIGHT");
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// ========== OBSTACLE AVOIDANCE ==========
void avoidObstacle() {
  int leftDist, rightDist;
  
  // Look left
  myServo.write(LEFT_ANGLE);
  delay(SCAN_DELAY);
  leftDist = getDistance();
  Serial.print("Left: ");
  Serial.print(leftDist);
  Serial.println(" cm");
  
  // Look right
  myServo.write(RIGHT_ANGLE);
  delay(SCAN_DELAY);
  rightDist = getDistance();
  Serial.print("Right: ");
  Serial.print(rightDist);
  Serial.println(" cm");
  
  // Return to center
  myServo.write(CENTER);
  delay(300);
  
  // Decide action
  if (leftDist > rightDist && leftDist > MIN_DISTANCE) {
    Serial.println("<<< TURNING LEFT");
    turnLeft();
    delay(TURN_TIME);
    stopMotors();
  }
  else if (rightDist > leftDist && rightDist > MIN_DISTANCE) {
    Serial.println(">>> TURNING RIGHT");
    turnRight();
    delay(TURN_TIME);
    stopMotors();
  }
  else if (leftDist > MIN_DISTANCE) {
    Serial.println("<<< TURNING LEFT (only option)");
    turnLeft();
    delay(TURN_TIME);
    stopMotors();
  }
  else if (rightDist > MIN_DISTANCE) {
    Serial.println(">>> TURNING RIGHT (only option)");
    turnRight();
    delay(TURN_TIME);
    stopMotors();
  }
  else {
    Serial.println("XXX ALL BLOCKED - REVERSING");
    moveBackward();
    delay(REVERSE_TIME);
    stopMotors();
    delay(300);
    turnRight();
    delay(TURN_TIME * 1.5);
    stopMotors();
  }
}

void emergencyReverse() {
  stopMotors();
  delay(100);
  moveBackward();
  delay(REVERSE_TIME);
  stopMotors();
  delay(300);
  turnRight();
  delay(TURN_TIME);
  stopMotors();
}

// ========== ULTRASONIC ==========
int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) return 200;
  
  int distance = duration * 0.034 / 2;
  if (distance > 200) distance = 200;
  return distance;
}

// ========== MANUAL TEST MODE ==========
/*
void loop() {
  // Manual control for testing
  if (Serial.available()) {
    char cmd = Serial.read();
    
    switch(cmd) {
      case 'w':
        moveForward();
        Serial.println("Forward");
        break;
      case 's':
        moveBackward();
        Serial.println("Backward");
        break;
      case 'a':
        turnLeft();
        Serial.println("Left turn");
        break;
      case 'd':
        turnRight();
        Serial.println("Right turn");
        break;
      case 'x':
        stopMotors();
        Serial.println("Stop");
        break;
      case 't':
        // Test sequence
        Serial.println("Test: Forward 2s");
        moveForward();
        delay(2000);
        Serial.println("Test: Backward 2s");
        moveBackward();
        delay(2000);
        Serial.println("Test: Left 1s");
        turnLeft();
        delay(1000);
        Serial.println("Test: Right 1s");
        turnRight();
        delay(1000);
        stopMotors();
        Serial.println("Test complete");
        break;
    }
  }
}
*/