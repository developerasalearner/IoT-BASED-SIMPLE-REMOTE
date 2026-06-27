# IoT-Based Simple Remote Control System

## 📱 Project Overview

**IoT-Based Simple Remote Control System** is a comprehensive Arduino-based smart home control solution developed as part of the **ACIC GIETU Foundation's Project-Based IoT Training Program**. This project demonstrates practical IoT implementation by enabling users to control multiple household appliances using a wireless remote interface with real-time feedback on an LCD display.

This project was created during the **1-month Project-Based IoT Training Program** (September 1-30, 2022) conducted by **ACIC GIETU Foundation** as part of their capacity-building initiative to nurture students with hands-on training in emerging IoT technologies.

---

## 🎯 Project Objectives

### Primary Goals:
- **Design & Development**: Create a cost-effective IoT-enabled technology for controlling household appliances
- **Hands-on Learning**: Provide practical exposure to IoT platforms, hardware integration, and communication protocols
- **Real-world Application**: Demonstrate IoT concepts through a practical, implementable project
- **Skill Development**: Build trained manpower in IoT-based application development

### Educational Context:
This project is part of a structured IoT training program that focuses on:
- Arduino microcontroller programming
- Sensor and actuator integration
- I2C communication protocols
- LCD display interfacing
- Relay-based appliance control
- IoT prototyping and rapid development

---

## 🛠️ Hardware Architecture

### Components Used:

| Component | Specification | Purpose |
|-----------|---------------|---------|
| **Arduino Uno** | Microcontroller (ATmega328P) | Main control unit |
| **Keypad** | Analog resistor network (A0 pin) | User input interface |
| **LCD Display** | 16x2 Character LCD | User feedback display |
| **PCF8574** | I2C I/O Expander | LCD control module |
| **Relay Module** | 8-channel relay array | Appliance switching |
| **Digital Pins** | Arduino D2-D9 | Relay control outputs |

### Wiring Diagram:
```
Arduino Uno
    |
    ├─ Pin 2-9 ────> 8-Channel Relay Module
    |               ├─ Relay 1 (D2) ─> FAN1
    |               ├─ Relay 2 (D3) ─> TV
    |               ├─ Relay 3 (D4) ─> AC
    |               ├─ Relay 4 (D5) ─> Smart Plug
    |               ├─ Relay 5 (D6) ─> FAN2
    |               ├─ Relay 6 (D7) ─> DESKTOP
    |               ├─ Relay 7 (D8) ─> LIGHT1
    |               └─ Relay 8 (D9) ─> LIGHT2
    |
    ├─ A0 (Analog) ─> Keypad (Resistor Network)
    |
    └─ SDA/SCL ────> I2C Bus
                    └─ PCF8574 ────> LCD 16x2 Display
```

---

## 📋 Controllable Appliances

The system can control **8 different appliances**:

| Device # | Appliance Name | Pin | Keypad Code | Description |
|----------|----------------|-----|-------------|-------------|
| 1 | FAN1 | D2 | 98 | Living room or bedroom fan |
| 2 | TV | D3 | 90 | Television |
| 3 | AC | D4 | 83 | Air Conditioning unit |
| 4 | S_PLUG (Smart Plug) | D5 | 180 | Generic appliance outlet |
| 5 | FAN2 | D6 | 153 | Secondary fan |
| 6 | DESKTOP | D7 | 133 | Computer workstation |
| 7 | LIGHT1 | D8 | 1023 | Primary lighting system |
| 8 | LIGHT2 | D9 | 512 | Secondary lighting system |

---

## 🎮 User Interface & Controls

### LCD Display:
- **Resolution**: 16 characters × 2 lines
- **Interface**: I2C communication via PCF8574 expander
- **Backlight**: Programmable brightness control

### Keypad Interface:
The keypad uses **analog voltage dividers** to create unique voltage levels for each button:
- Connected to **Arduino Analog Pin A0**
- Each button press generates a specific ADC value (0-1023 range)
- Press the **ON button** (ADC ≈ 68) to view device selection menu

### User Interaction Flow:
```
1. User presses "ON" button on keypad
   └─> Arduino reads ADC value (68)
   └─> LCD displays: "SELECT ONE"
   
2. System displays device options in sequence:
   ├─> "1 for FAN1" | "2 for TV"
   ├─> "3 for AC" | "4 for S_PLUGE"
   ├─> "5 for FAN2" | "6 for DESKTOP"
   ├─> "7 for LIGHT1" | "8 for LIGHT2"
   └─> Instructions to repeat

3. User presses device button (98, 90, 83, etc.)
   └─> Arduino identifies device
   └─> Activates corresponding relay
   └─> Displays confirmation: "[DEVICE] is ON"
   └─> Appliance power activated
```

---

## 💻 Software Architecture

### File Structure:
```
IoT-BASED-SIMPLE-REMOTE/
├── README.md                              # Project documentation
├── remote.ino                             # Main sketch (5.6 KB)
├── Lcd.h                                  # LCD library header (2.5 KB)
├── Lcd.cpp                                # LCD library implementation (8.6 KB)
├── remote.ino.standard.hex                # Compiled hex file
└── remote.ino.with_bootloader.standard.hex # Bootloader included hex file
```

### Core Modules:

#### 1. **remote.ino** (Main Sketch)
The primary Arduino sketch containing:

**Setup Phase:**
```cpp
void setup() {
  // Initialize all 8 relay control pins (D2-D9) as OUTPUT
  // Initialize I2C LCD with 16 columns, 2 rows, address 0x20
  // Set LCD backlight to maximum (255)
  // Clear the display
}
```

**Main Loop Logic:**
```cpp
void loop() {
  // 1. Read analog keypad input (A0)
  // 2. Check if value changed from previous read (debounce)
  // 3. If ON button pressed (ADC = 68):
  //    - Flash all relays (visual feedback)
  //    - Display device selection menu
  // 4. If device button pressed (98, 90, 83, etc.):
  //    - Activate corresponding relay
  //    - Display confirmation on LCD
  //    - Deactivate all other relays (one-at-a-time mode)
}
```

**Keypad Value Mapping:**
- **68**: ON button (Menu trigger)
- **98**: FAN1 button
- **90**: TV button
- **83**: AC button
- **180**: Smart Plug button
- **153**: FAN2 button
- **133**: DESKTOP button
- **1023**: LIGHT1 button
- **512**: LIGHT2 button

#### 2. **Lcd.h** (LCD Library Header)
Defines the LCD interface class with:
- LCD command codes (display control, cursor movement, etc.)
- Display configuration flags
- Public method declarations for display operations

**Key Methods:**
- `begin()`: Initialize LCD with I2C address and backlight
- `clear()`: Clear display content
- `setCursor(col, row)`: Position cursor for text
- `print()`: Write text to display
- `display()` / `noDisplay()`: Toggle display on/off
- `setBacklight()`: Control backlight brightness

#### 3. **Lcd.cpp** (LCD Library Implementation)
Implements I2C-based communication with the LCD:

**I2C Communication Protocol:**
- Uses PCF8574 I/O expander for LCD control
- Bit-mapped control signals:
  - **PCF_RS** (0x01): Register Select
  - **PCF_RW** (0x02): Read/Write control
  - **PCF_EN** (0x04): Enable signal
  - **PCF_BACKLIGHT** (0x08): Backlight control

**LCD Initialization Sequence:**
1. Power-on delay (50ms)
2. 4-bit mode initialization (Hitachi HD44780 standard)
3. Function set configuration
4. Display control setup
5. Entry mode configuration
6. Backlight activation

---

## 🔌 Technical Specifications

### Communication Protocols:
- **I2C**: For LCD module communication (Wire library)
- **Analog Input**: For keypad reading (ADC conversion)
- **Digital Output**: For relay switching (HIGH/LOW control)

### Power Requirements:
- **Arduino Uno**: 5V USB or external power
- **Relays**: 12V (typically, with driver circuit)
- **LCD Display**: 5V (via PCF8574)
- **Keypad**: 5V pull-up resistors

### Timing Specifications:
- **LCD Command execution**: 2000µs delay
- **Nibble transmission**: 37µs settlement time
- **Keypad debounce**: 50ms delay
- **Display refresh**: 100ms update interval

---

## 🚀 Getting Started

### Prerequisites:
- Arduino IDE installed
- Arduino Uno microcontroller
- USB cable for programming
- Required hardware components (as listed in Hardware Architecture)

### Installation Steps:

1. **Clone or Download Repository:**
   ```bash
   git clone https://github.com/developerasalearner/IoT-BASED-SIMPLE-REMOTE.git
   ```

2. **Open in Arduino IDE:**
   - Launch Arduino IDE
   - Open `remote.ino`
   - Ensure Lcd.h and Lcd.cpp are in the same directory

3. **Configure Board Settings:**
   - Select **Board**: Arduino Uno
   - Select **Port**: COM port where Arduino is connected
   - Select **Programmer**: AVRISP mkII

4. **Upload Code:**
   - Click Upload button (→)
   - Wait for "Done uploading" message

5. **Hardware Assembly:**
   - Connect relay module to pins D2-D9
   - Connect keypad to analog pin A0
   - Connect LCD via I2C (SDA/SCL to Arduino A4/A5)
   - Connect appropriate power supplies

6. **Test System:**
   - Power on the Arduino
   - Press ON button on keypad
   - Verify LCD displays menu
   - Test each relay button

### Using Pre-Compiled Hex Files:
- `remote.ino.standard.hex`: Use with existing bootloader
- `remote.ino.with_bootloader.standard.hex`: Full flash including bootloader
- Use **avrdude** or similar programmer to upload

---

## 📊 Project Development Context

### ACIC GIETU Foundation IoT Program:

**Program Duration:** 1 month (September 1-30, 2022)
**Target Students:** 2nd Year B.Tech students
**Prerequisite:** C Programming Language
**Selection Process:** Qualifying test on C language (30 students selected from 130 registrations)

**Student Distribution:**
- Total Participants: 30 students
- CSE Branch: 27 students (1 female)
- ECE Branch: 3 students

**Program Structure:**
- **Theory Sessions**: Alternate days, 1 hour each (6:00-7:00 PM), online
- **Practical Sessions**: Open 10:00 AM - 8:00 PM at ACIC IoT Lab
- **Location**: ACIC GIETU Foundation, Mechanical Building, 1st Floor

**Course Curriculum:**
1. Arduino Environment Installation
2. Arduino Uno Development Board Overview
3. Digital and Analog Pin Configuration
4. Arduino with LED Relay Arrays
5. Serial Communication Protocol
6. Analog Sensor Integration
7. Digital Sensor Integration
8. I2C Communication Protocol
9. LCD Display Integration
10. Keypad Interfacing
11. Arduino-MySQL Database Integration
12. Multi-component System Integration
13. Final Project Development

### Training Delivery:
- **Resource Persons**: Mr. Biswa Ranjan Bhola (Advisor/Mentor) and Mr. Sandeep Sahoo (Technical Assistant)
- **Mentorship**: Industry expert guidance from Mr. Sunil David (Ex-Regional Director, IoT at AT&T)
- **Certification**: Completion certificates issued to successful students

### Student Attendance Record:
```
Date          Students Present
06/09/22           13
07/09/22           15
08/09/22           08
09/09/22           14
12/09/22           15
13/09/22           10
16/09/22           13
17/09/22           11
18/09/22           17
19/09/22           12
20/09/22           10
22/09/22           09
23/09/22           16
24/09/22           11
26/09/22           13
```

---

## 🏆 Project Outcomes & Achievements

### Demo Day:
- **Date**: October 22, 2022
- **Time**: 5:00 PM
- **Venue**: ACIC GIETU Foundation
- **Attendees**: Dr. A.B. Srinivas Rao (Dean SOET) and Dr. A.V.N.L Sharma (Dean Academics)

### Certification:
All successful students received completion certificates signed by:
- Dr. N.V.J. Rao (Registrar)
- Mr. Sunil David (Ex-Regional Director, IoT at AT&T)

### Industry Impact:
- Projects demonstrate IoT fundamentals and practical implementation skills
- Several projects are campus-relevant and implementable
- Students gained exposure to IoT technology stack
- Foundation for pursuing advanced IoT research and development

### Related Student Projects:
While this is the IoT-Based Simple Remote project, other notable projects from the program include:
- Privacy Security System
- Smart Dustbin
- Low-Cost Traffic Light System
- Welcome Board Design
- Water Tank Level Reminder System

---

## 💡 How It Works - Detailed Flow

### Initialization Phase:
1. Arduino powers on
2. Pins D2-D9 configured as OUTPUT (relay control)
3. I2C communication initialized
4. LCD initialized at address 0x20
5. Display cleared and ready

### Operation Phase:

**Step 1: Menu Selection**
```
User presses ON button → Arduino detects ADC = 68
→ All relays flash briefly (visual feedback)
→ LCD displays device selection menu
```

**Step 2: Device Selection**
```
User presses device button (e.g., FAN1 button) → Arduino detects ADC = 98
→ Arduino activates relay 1 (PIN D2 = HIGH)
→ All other relays deactivate (PIN D3-D9 = LOW)
→ LCD displays "FAN1 is ON"
```

**Step 3: Continuous Monitoring**
```
Arduino continuously reads analog input
→ Stores previous read value
→ Compares current value with previous value
→ Only processes changes (debounce mechanism)
→ Maintains current device state
```

---

## 🔧 Customization & Extension

### Modifying Controlled Devices:
Edit the keypad value checks in `loop()` function:
```cpp
if(r==98)  // Replace 98 with your keypad value
{
    digitalWrite(2, HIGH);  // Replace with desired pin
    // ... rest of control logic
}
```

### Adding More Devices:
1. Use additional relay pins (if available)
2. Calculate unique keypad ADC values
3. Add new `if(r==value)` condition blocks
4. Extend LCD menu display logic

### Changing LCD Configuration:
Modify constants at top of `remote.ino`:
```cpp
#define LCD_ADDRESS 0x20      // Change I2C address if needed
#define LCD_ROWS 2            // Change for 4-line display
#define LCD_COLUMNS 16        // Change for 20-char display
#define BACKLIGHT 255         // Adjust brightness (0-255)
```

### Calibrating Keypad Values:
Use Serial Monitor to read raw analog values:
```cpp
Serial.begin(9600);
Serial.println(analogRead(A0));  // Print analog value
```

---

## 🐛 Troubleshooting

### LCD Not Displaying:
- Check I2C address (default 0x20)
- Verify PCF8574 wiring
- Use `checkI2CConnection()` method
- Adjust backlight brightness

### Relays Not Activating:
- Verify relay module connections
- Check pin assignments (D2-D9)
- Test with digitalWrite directly
- Verify external power supply for relays

### Keypad Not Responding:
- Read analog values with Serial Monitor
- Verify resistor network values
- Check analog pin connection (A0)
- Test with different calibration values

### LCD I2C Communication Errors:
- Check SDA/SCL pull-up resistors
- Verify Wire library is initialized
- Check for address conflicts on I2C bus
- Use I2C scanner to identify connected devices

---

## 📚 Learning Outcomes

By studying and implementing this project, students gain knowledge in:

1. **Microcontroller Programming**: Arduino sketch development and loop logic
2. **Hardware Integration**: Interfacing multiple components (relays, LCD, keypad)
3. **Communication Protocols**: I2C for LCD, analog reading for input
4. **Digital Electronics**: Relay control, GPIO pin management
5. **User Interface Design**: LCD feedback and menu navigation
6. **System Architecture**: Modular code design and separation of concerns
7. **IoT Concepts**: Real-world smart device control implementation
8. **Debugging & Testing**: Hardware troubleshooting and validation

---

## 🤝 Contributors & Credits

### Project Development:
- **Developer**: Chinmaya Kumar Palo (21CSEDS023)
- **Program**: ACIC GIETU Foundation's Project-Based IoT Training
- **Duration**: September 2022
- **Branch**: CSE (Data Science specialization)

### Mentorship & Support:
- **Advisor/Mentor**: Mr. Biswa Ranjan Bhola
- **Technical Assistant**: Mr. Sandeep Sahoo
- **Program Director**: Mr. Sunil M Ponneth (CEO, ACIC GIETU Foundation)
- **Institutional Support**: Dr. N.V.J. Rao (Registrar), GIETU
- **Industry Mentorship**: Mr. Sunil David (Ex-Regional Director, IoT at AT&T)

---

## 📝 License

This project is provided as part of the ACIC GIETU Foundation's educational initiative. Usage for educational and non-commercial purposes is encouraged.

---

## 🔗 References

### Technology Stack:
- Arduino Programming Language (C++ based)
- Arduino IDE
- Wire Library (I2C Communication)
- Print Library (Text output)

### Hardware Datasheets:
- ATmega328P (Arduino Uno processor)
- PCF8574 (I2C I/O Expander)
- HD44780 (16x2 LCD Controller)
- Standard 8-Channel Relay Module

### Communication Standards:
- I2C (Inter-Integrated Circuit) Protocol
- Arduino Digital/Analog I/O
- Keypad Resistor Network Design

---

## 📞 Support & Feedback

For questions or suggestions regarding this project:
- Review the ACIC GIETU Foundation's IoT Lab resources
- Consult with your IoT training instructors
- Refer to Arduino official documentation

---

## ✨ Project Significance

This project represents a foundational step in IoT learning journey:
- ✅ **Practical Implementation**: From concept to working prototype
- ✅ **Multi-Component Integration**: Combines microcontroller, sensors, displays, and actuators
- ✅ **Real-World Relevance**: Smart home automation is a growing field
- ✅ **Scalability**: Foundation for more complex IoT systems
- ✅ **Cost-Effective**: Uses commonly available components
- ✅ **Educational Value**: Comprehensive learning across multiple domains

---

**Last Updated**: Based on project from September 2022 ACIC GIETU Foundation IoT Training Program

**Repository**: https://github.com/developerasalearner/IoT-BASED-SIMPLE-REMOTE
