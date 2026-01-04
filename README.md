# 🌊 Water Flow LED Animation Project - DUAL CORE

## 📋 Project Overview
Create a beautiful water-inspired LED animation using Raspberry Pi Pico 2's **dual-core processor**. The system provides realistic water physics with or without the MPU6050 sensor.

### 🚀 New Dual-Core Features
- **Core 0**: 50Hz sensor processing & physics calculations
- **Core 1**: 30Hz LED updates & 15Hz serial display
- **Auto-Detection**: Works with/without MPU6050 automatically
- **Professional Output**: Real-time serial monitoring with sensor data

## 🛠 Hardware Requirements

### Essential Components
- Raspberry Pi Pico 2
- WS2812B LED Strip (18 LEDs)
- Breadboard and jumper wires
- USB cable (data capable)

### Optional Components
- MPU6050 Accelerometer/Gyroscope (for tilt control)
- 2x 4.7kΩ resistors (improves MPU6050 reliability)

### Tools
- Computer with Arduino IDE

## 🔌 Wiring Diagram

### Pico 2 → MPU6050 Connections (Optional)
```
Pico 2    →   MPU6050
-----        -----
3V3       →   VCC
GND       →   GND
GP0       →   SDA
GP1       →   SCL
```

### Pico 2 → WS2812B Connections (Required)
```
Pico 2    →   WS2812B
-----        -----
VBUS      →   5V    (for power)
GND       →   GND
GP2       →   DIN   (data in)
```

### 💡 Optional: Pull-up Resistors for MPU6050
```
3V3 → 4.7kΩ resistor → SDA
3V3 → 4.7kΩ resistor → SCL
```

## 💻 Software Setup

### Step 1: Install Arduino IDE
1. Download Arduino IDE from https://www.arduino.cc/
2. Install on your computer

### Step 2: Add Pico 2 Support
1. Open Arduino IDE
2. Go to **File → Preferences**
3. In "Additional Boards Manager URLs", add:
   ```
   https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json
   ```
4. Click OK

### Step 3: Install Board Package
1. Go to **Tools → Board → Boards Manager**
2. Search for "Raspberry Pi Pico/RP2040"
3. Install the package

### Step 4: Install Required Libraries
1. Go to **Tools → Manage Libraries**
2. Search and install these libraries:
   - `Adafruit NeoPixel` by Adafruit
   - `Adafruit MPU6050` by Adafruit
   - `Adafruit BusIO` by Adafruit (dependency)

## 🚀 Uploading Code

### Step 1: Board Configuration
In Arduino IDE, set:
- **Board**: "Raspberry Pi Pico"
- **Board Version**: "Raspberry Pi Pico 2" 
- **CPU Speed**: "133 MHz"
- **Flash Size**: "2MB (Sketch: 1MB, FS: 1MB)"
- **Port**: Select your Pico's COM port
- **Programmer**: "Picoprobe"

### Step 2: Upload Method
**BOOTSEL Mode (Recommended):**
1. Hold **BOOTSEL** button on Pico 2
2. Plug in USB cable while holding BOOTSEL
3. Release BOOTSEL button
4. Pico appears as mass storage device
5. Select correct port in Arduino IDE
6. Click Upload

## 🎮 Operation Modes

### Mode 1: With MPU6050 Connected
- Water glow starts in middle of LED strip
- **Tilt LEFT** → Water flows left
- **Tilt RIGHT** → Water flows right
- Real sensor data with automatic calibration
- Professional physics with momentum and bounce

### Mode 2: Without MPU6050 (Automatic Fallback)
- System auto-detects missing sensor
- Uses simulated motion patterns
- Still provides full water animation
- Perfect for testing and demonstrations

### Mode 3: LED Strip Only
- Works with just Pico 2 + LED strip
- Automatic wave patterns
- Serial monitor visualization available

## 📟 Serial Monitor Output

Open Serial Monitor at **115200 baud** to see real-time data:

```
F:42 | S:REAL | X:0.15 | V:0.08 | ______-=-~-=-______
F:43 | S:REAL | X:-0.12 | V:-0.04 | _____-=-~-=-_______
F:44 | S:SIM  | X:0.08 | V:0.02 | ______-=-~-=-______
```

### Output Legend:
- `F:` Frame counter
- `S:` Sensor status (**REAL**=MPU6050, **SIM**=Simulated)
- `X:` Tilt value (-1.0 to 1.0)
- `V:` Water velocity
- `~=~` ASCII water visualization

## 🔧 Troubleshooting

### LEDs Not Lighting
- Check LED strip direction (arrow points away from Pico)
- Verify GP2 → DIN connection
- Try external 5V power for LED strip
- Reduce brightness: `strip.setBrightness(50)`

### MPU6050 Not Detected
- **No problem!** System will auto-switch to simulated motion
- For better reliability: add 4.7kΩ pull-up resistors
- Check wiring: GP0→SDA, GP1→SCL
- Confirm 3V3 power to MPU6050

### Upload Failures
- Use BOOTSEL mode method
- Ensure data-capable USB cable
- Check correct COM port selection
- Restart Arduino IDE if issues persist

### Serial Monitor Issues
- Set baud rate to **115200**
- Use "No line ending" or "Newline"
- Ensure auto-scroll is enabled

## 🎯 Dual-Core Performance

### Core 0: Sensor & Physics
- **50Hz** MPU6050 reading (or simulated data)
- Real-time physics calculations
- Automatic calibration
- Thread-safe variable management

### Core 1: LED & Display
- **30Hz** LED strip updates
- **15Hz** serial monitor output
- ASCII water visualization
- Real-time status reporting

## 📊 Expected Results

### With MPU6050
- Smooth tilt-responsive water flow
- Real sensor data in serial monitor
- Professional physics simulation
- Status: `S:REAL`

### Without MPU6050  
- Beautiful automatic wave patterns
- Simulated motion data
- Full water animation experience
- Status: `S:SIM`

### Serial Output Examples
**With Sensor:**
```
F:1 | S:REAL | X:0.23 | V:0.12 | ______-=-~-=-______
```

**Without Sensor:**
```
F:1 | S:SIM | X:0.05 | V:0.03 | ______-=-~-=-______
```

## 🎉 Project Completion

### You Now Have:
✅ **Dual-core processing** on Pico 2  
✅ **Robust operation** with/without MPU6050  
✅ **Professional serial monitoring** with real-time data  
✅ **Realistic water physics** with momentum and bounce  
✅ **Power-efficient** LED control (3-4 LEDs active)  

### No Resistors Required!
The system works perfectly without pull-up resistors, automatically falling back to simulated motion when the MPU6050 isn't reliably detected.

**Resistors are optional** - they improve MPU6050 reliability but aren't required for the project to function!

---

## 🔗 Quick Start Checklist
- [ ] Connect Pico 2 to WS2812B LED strip
- [ ] (Optional) Connect MPU6050 for tilt control
- [ ] Install Arduino IDE with Pico 2 support
- [ ] Upload dual-core code
- [ ] Open Serial Monitor at 115200 baud
- [ ] Watch beautiful water flow animation!

# 🔧 **Hardware Fix for Smooth LED Animation**

## ⚠️ **Important Notice: For Optimal Performance**

In the demonstration video (`media/core_wave.mp4`), you may notice that the **WS2812B LED ring shows jerky movement** while the **serial monitor displays perfectly smooth wave motion**.

## 🎯 **The Issue & Solution**

### **Problem:**
- **Serial Monitor**: Shows smooth wave: `______-=-~-=-______`
- **LED Ring**: Shows choppy, incomplete wave
- **Root Cause**: MPU6050 communication issues without pull-up resistors

### **Solution: Add 2x 4.7kΩ Resistors**
```
Pico 3V3 → 4.7kΩ resistor → MPU6050 SDA
Pico 3V3 → 4.7kΩ resistor → MPU6050 SCL
```

## 🛠 **Required Components**
- 2x 4.7kΩ resistors (or 2.2kΩ-10kΩ range)
- MPU6050 sensor
- Raspberry Pi Pico 2
- WS2812B LED ring

## 🔌 **Resistor Installation**

### **Connection Diagram:**
```
      4.7kΩ
3V3 ────╱╱╱╱─── SDA
       │
      4.7kΩ  
3V3 ────╱╱╱╱─── SCL
```

### **Physical Connection:**
- Connect resistors between **3V3 and SDA**
- Connect resistors between **3V3 and SCL** 
- Use breadboard or solder directly

## 📊 **Before vs After Resistors**

### **Without Resistors:**
- ✅ System works with simulated motion
- ❌ LED animation may be jerky
- ❌ Tilt control unreliable
- ❌ MPU6050 may not be detected

### **With Resistors:**
- ✅ **Smooth, fluid LED animation**
- ✅ **Perfect tilt-responsive control**
- ✅ **Reliable MPU6050 detection**
- ✅ **LED ring matches serial monitor smoothness**

## 🚀 **Expected Results After Fix**

### **LED Behavior:**
- **Before**: Choppy, incomplete wave movements
- **After**: Smooth, continuous water flow

### **Serial Output:**
```
F:42 | S:REAL | X:0.15 | V:0.08 | ______-=-~-=-______
F:43 | S:REAL | X:0.14 | V:0.07 | ______-=-~-=-______
F:44 | S:REAL | X:0.13 | V:0.06 | ______-=-~-=-______
```

## 💡 **Why This Matters**

The pull-up resistors ensure **clean, stable communication** with the MPU6050 sensor, which directly translates to **smooth, responsive water physics** on the LED ring.

## 🔧 **Quick Setup**
1. **Add resistors** between 3V3 and SDA/SCL
2. **Upload any water animation code**
3. **Enjoy smooth, tilt-responsive water flow**

**This small hardware addition ensures professional-quality animation results!** 🌊✨
