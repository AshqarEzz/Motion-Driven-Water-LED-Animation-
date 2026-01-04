note that 4 needs 2 4.7k resistors to work 

# 📁 Code Versions Summary

## 1. **All Work** - Complete Water Animation with Manual Control
**Purpose**: Full-featured water simulation with serial commands
**Use When**: You want complete control without MPU6050

**Features:**
- 💧 **Manual Control**: Type `l`=left, `r`=right, `s`=stop in Serial Monitor
- 🌊 **Auto Waves**: Random gentle movements when idle
- 🔋 **Power Efficient**: Only 3-4 LEDs lit at once
- 📟 **Serial Display**: Shows ASCII water `___-=-~-=-___`
- 🎯 **Physics**: Realistic bounce, damping, momentum
- 🔧 **Debug Info**: Position/velocity data every 2 seconds

**Best For**: Testing LED strip + learning water physics

---

## 2. **No-Resistor-Wave** - Automatic Waves (No Sensor Needed)
**Purpose**: Basic water animation while waiting for MPU6050 resistors
**Use When**: You don't have pull-up resistors yet

**Features:**
- 🌊 **Auto Motion**: Self-moving waves without input
- 🔋 **Ultra Simple**: Minimal code, easy to understand
- 📟 **Basic Display**: Simple ASCII `___~=~___` pattern
- ⚡ **Low Power**: Only 3 LEDs active

**Best For**: Quick LED test + temporary display

---

## 3. **OneByOneWave** - LED Diagnostic Test
**Purpose**: Verify all LEDs work individually
**Use When**: Testing hardware or troubleshooting

**Features:**
- 🔍 **LED Test**: Lights each LED one by one
- 💡 **Low Brightness**: Safe for power-limited setups
- ⚡ **Simple**: Bare minimum code
- ✅ **Verification**: Confirms all 18 LEDs function

**Best For**: Hardware testing + finding dead LEDs

---

## 🎯 **When to Use Each:**

| Code Version | MPU6050 | Resistors | Purpose |
|-------------|---------|-----------|---------|
| **All Work** | ❌ Not needed | ❌ Not needed | Full water simulation with manual control |
| **No-Resistor-Wave** | ❌ Not connected | ❌ Not available | Automatic waves while waiting for parts |
| **OneByOneWave** | ❌ Not needed | ❌ Not needed | Hardware testing & troubleshooting |

## 🔄 **Progression:**
1. Start with **OneByOneWave** to test LEDs
2. Use **No-Resistor-Wave** for basic animation  
3. Upgrade to **All Work** for full features
4. Add MPU6050 + resistors later for tilt control




4 # 🔧 **Single-Core Water Animation with MPU6050**

## 🎯 **What This Code Does:**

### **Core Function:**
Creates a **water droplet animation** on LED strip that responds to MPU6050 tilt sensor

### **Smart Features:**
- **Auto-detects MPU6050** - Works with or without sensor
- **Auto-calibration** - Removes sensor drift when flat
- **Dual control modes** - Tilt control OR manual serial commands
- **Power-efficient** - Only 3 LEDs lit at once
- **Real-time display** - ASCII water visualization in Serial Monitor

### **Operation Modes:**

**With MPU6050:**
```
Tilt LEFT → Water flows left ←─────┐
Tilt RIGHT → Water flows right     │ MPU6050 Control
Flat → Water stays still ←─────────┘
```

**Without MPU6050:**
```
Type 'l' → Move left ←─────────────┐
Type 'r' → Move right              │ Serial Commands  
Type 's' → Stop ←──────────────────┘
```

### **Visual Output:**
- **LEDs**: Blue water glow (3 LEDs) that moves smoothly
- **Serial**: ASCII waves `______-=-~-=-______`
- **Physics**: Realistic flow with bounce at edges

### **Key Components:**
- **Water Physics**: Position + velocity + damping
- **Sensor Calibration**: Auto-corrects tilt offset
- **Dead Zone**: Ignores tiny sensor movements
- **Boundary Handling**: Gentle bounce at strip ends

### **Use Case:**
Perfect for **testing and demonstration** - works regardless of whether MPU6050 is connected!

**Bottom Line:** Smart water animation that adapts to available hardware automatically! 🌊


All versions work without MPU6050 or resistors! 🎉