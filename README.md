# Motion-Driven-Water-LED-Animation-

Project Title
A brief description of what this project does and who it's for

in the folder named( 1 pcb hat mpu6050 the design using kicad is presented), I am not a pro in kicad so its not a complete design.

in the folder named (2-wave-with-sensor-control) is the working project, the following is how to run it :

(The project report is written by AI after days of communicating and failing, the report contain where i had issues and the troubleshooting for some errors, note that i don't have 4.7kΩ resistor at home so the serial uploaded will have the wave without the control by the 4.7kΩ resistor, but adding it as in the design picture attached under the name design the wave flow should work flawlessly)

🌊 Water Flow LED Animation Project

📋 Project Overview Create a beautiful water-inspired LED animation that responds to motion using a Raspberry Pi Pico 2, MPU6050 accelerometer, and WS2812B LED strip.

Features
Blue "water glow" that starts in the middle of LED strip
Tilting sensor left/right makes water flow like gravity moving liquid
Shimmer effects, flow delay, bounce, and edge reflections
Serial monitor visualization when LEDs aren't connected
🛠 Hardware Requirements
Components
Raspberry Pi Pico 2
MPU6050 Accelerometer/Gyroscope
WS2812B LED Strip (18 LEDs)
2x 4.7kΩ resistors (CRITICAL for MPU6050)
Breadboard and jumper wires
USB cable (data capable)
Tools
Computer with Arduino IDE
USB cable
🔌 Wiring Diagram
Pico 2 → MPU6050 Connections
Pico 2    →   MPU6050
-----        -----
3V3       →   VCC
GND       →   GND
GP0       →   SDA
GP1       →   SCL
Pico 2 → WS2812B Connections
Pico 2    →   WS2812B
-----        -----
VBUS      →   5V    (for power)
GND       →   GND
GP2       →   DIN   (data in)
⚠️ CRITICAL: Pull-up Resistors for MPU6050
( i tried many test codes and the issue of the pi pico2 doesn't have i2c connection so having 2 4.7kΩ resistors is a must)

3V3 → 4.7kΩ resistor → SDA
3V3 → 4.7kΩ resistor → SCL
💻 Software Setup
Step 1: Install Arduino IDE
Download Arduino IDE from https://www.arduino.cc/
Install on your computer
Step 2: Add Pico 2 Support
Open Arduino IDE
Go to File → Preferences
In "Additional Boards Manager URLs", add:
https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json
Click OK
Step 3: Install Board Package
Go to Tools → Board → Boards Manager
Search for "Raspberry Pi Pico/RP2040"
Install the package
Step 4: Install Required Libraries
Go to Tools → Manage Libraries
Search and install these libraries:
Adafruit NeoPixel by Adafruit
Adafruit MPU6050 by Adafruit
Adafruit BusIO by Adafruit (dependency)
🚀 Uploading Code
Step 1: Board Configuration
In Arduino IDE, set:

Board: "Raspberry Pi Pico"
Board Version: "Raspberry Pi Pico 2"
CPU Speed: "133 MHz"
Flash Size: "2MB (Sketch: 1MB, FS: 1MB)"
Port: Select your Pico's COM port
Programmer: "Picoprobe"
Step 2: Upload Method
BOOTSEL Mode (Recommended):

Hold BOOTSEL button on Pico 2
Plug in USB cable while holding BOOTSEL
Release BOOTSEL button
Pico appears as mass storage device
Select correct port in Arduino IDE
Click Upload
🎮 Operation
With Hardware Connected
Water glow starts in middle of LED strip
Tilt LEFT → Water flows left
Tilt RIGHT → Water flows right
Features shimmer, bounce, and smooth physics
Serial Monitor Only
Open Serial Monitor at 115200 baud
View ASCII water visualization: ___~~~~____
Water movement shown with ~ = - . _ characters
🔧 Troubleshooting
LEDs Not Lighting
Check LED strip direction (arrow points away from Pico)
Verify GP2 → DIN connection
Try external 5V power for LED strip
Reduce brightness in code: strip.setBrightness(50)
MPU6050 Not Detected
Verify pull-up resistors are installed (most common issue)
Check wiring: GP0→SDA, GP1→SCL
Confirm 3V3 power to MPU6050
Try I2C scanner code to detect device
Upload Failures
Use BOOTSEL mode method
Ensure data-capable USB cable
Check correct COM port selection
Restart Arduino IDE if issues persist
📊 Expected Results
Successful Operation
Blue water glow moves smoothly with sensor tilt
Gentle bounce at strip edges
Realistic water physics with momentum
Serial monitor shows flowing ASCII waves
All 18 LEDs work with proper power management
Serial Output Example
______-=-~-=-______
_____-=-~-=-_______
____-=-~-=-________
🎯 Project Completion
You should now have a fully functional water flow animation that responds to motion! The water will realistically accelerate, flow, and decelerate based on how you tilt the MPU6050 sensor.

Remember: The 4.7kΩ pull-up resistors are essential for MPU6050 communication. Don't skip this hardware requirement!

🔧 Hardware Fix for Smooth LED Animation
⚠️ Important Notice: For Optimal Performance
In the demonstration video (media/core_wave.mp4), you may notice that the WS2812B LED ring shows jerky movement while the serial monitor displays perfectly smooth wave motion.

🎯 The Issue & Solution
Problem:
Serial Monitor: Shows smooth wave: ______-=-~-=-______
LED Ring: Shows choppy, incomplete wave
Root Cause: MPU6050 communication issues without pull-up resistors
Solution: Add 2x 4.7kΩ Resistors
Pico 3V3 → 4.7kΩ resistor → MPU6050 SDA
Pico 3V3 → 4.7kΩ resistor → MPU6050 SCL
🛠 Required Components
2x 4.7kΩ resistors (or 2.2kΩ-10kΩ range)
MPU6050 sensor
Raspberry Pi Pico 2
WS2812B LED ring
🔌 Resistor Installation
Connection Diagram:
      4.7kΩ
3V3 ────╱╱╱╱─── SDA
       │
      4.7kΩ  
3V3 ────╱╱╱╱─── SCL
Physical Connection:
Connect resistors between 3V3 and SDA
Connect resistors between 3V3 and SCL
Use breadboard or solder directly
📊 Before vs After Resistors
Without Resistors:
✅ System works with simulated motion
❌ LED animation may be jerky
❌ Tilt control unreliable
❌ MPU6050 may not be detected
With Resistors:
✅ Smooth, fluid LED animation
✅ Perfect tilt-responsive control
✅ Reliable MPU6050 detection
✅ LED ring matches serial monitor smoothness
🚀 Expected Results After Fix
LED Behavior:
Before: Choppy, incomplete wave movements
After: Smooth, continuous water flow
Serial Output:
F:42 | S:REAL | X:0.15 | V:0.08 | ______-=-~-=-______
F:43 | S:REAL | X:0.14 | V:0.07 | ______-=-~-=-______
F:44 | S:REAL | X:0.13 | V:0.06 | ______-=-~-=-______
💡 Why This Matters
The pull-up resistors ensure clean, stable communication with the MPU6050 sensor, which directly translates to smooth, responsive water physics on the LED ring.

🔧 Quick Setup
Add resistors between 3V3 and SDA/SCL
Upload any water animation code
Enjoy smooth, tilt-responsive water flow
This small hardware addition ensures professional-quality animation results! 🌊✨
