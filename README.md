# IR-Controlled Robotic Car

This project involves a remote-controlled robotic car powered by Arduino, with an infrared (IR) receiver for receiving commands and sensors for detecting obstacles. The car is designed to navigate in all directions, adjust speed, and respond to obstacles using a distance sensor.

## Features
- **Directional Movement**: Move forward, backward, left, and right.
- **Speed Control**: Adjust speed up or down using IR remote commands.
- **Obstacle Detection**: Automatically stop and prevent backward movement when obstacles are detected.
- **Remote Control**: Controlled via an IR remote, with predefined commands for movement and functionality.

---

## Components
1. **Arduino Uno/Nano** (or compatible microcontroller)
2. **Motor Driver** (e.g., L298N or similar)
3. **DC Motors** (2 or 4 depending on design)
4. **IR Receiver Module** (connected to pin 2)
5. **IR Remote** (configured with specific button codes)
6. **Ultrasonic Sensor** (for obstacle detection)
   - **Trigger Pin**: Pin 4
   - **Echo Pin**: Pin 3
7. **6V Power Supply** (for motors)
8. Additional components: Wires, breadboard, and chassis.

---

## Setup and Wiring
### Motor Driver Connections:
- **Left Motor**: Connected to `lf` (pin 6), `lb` (pin 7), and enable pin `left` (pin 5).
- **Right Motor**: Connected to `rf` (pin 13), `rb` (pin 12), and enable pin `right` (pin 10).
- **Standby Pin**: Pin 8, set HIGH to enable the motor driver.

### IR Receiver:
- Connect to pin 2 on the Arduino.

### Ultrasonic Sensor:
- **Trigger Pin**: Pin 4
- **Echo Pin**: Pin 3

### Power Supply:
- Use the Arduino power for control logic.
- Connect a separate 6V supply for the motors.

---

## Installation
1. Clone the repository or copy the code to your Arduino IDE.
2. Install the necessary libraries:
   - [IRremote Library](https://github.com/Arduino-IRremote/Arduino-IRremote)
3. Upload the code to your Arduino board.

---

## Usage
1. Turn on the car and ensure the motors are enabled.
2. Use the IR remote to control the car:
   - **Forward**: IR_UP button
   - **Backward**: IR_DOWN button
   - **Turn Left**: IR_LEFT button
   - **Turn Right**: IR_RIGHT button
   - **Increase Speed**: IR_SPEED_UP button
   - **Decrease Speed**: IR_SPEED_DOWN button
   - **Reset/Stop**: IR_RESET button
3. Obstacle detection is automatic and prevents backward movement when obstacles are within 25 cm.

---

## Code Explanation
The main Arduino script handles:
1. **IR Signal Decoding**:
   - Uses the `IRremote` library to detect and process remote signals.
2. **Motor Control**:
   - Configured for speed adjustments and directional movement via PWM and digital pins.
3. **Obstacle Detection**:
   - Ultrasonic sensor measures distance periodically and sets a `block_back` flag if the obstacle is too close.
4. **State Management**:
   - Tracks current movement state to allow smooth transitions and avoid conflicts.

---

## Troubleshooting
1. **IR Receiver Issues**:
   - If the receiver blinks excessively, ensure no external IR interference (like cameras or sunlight).
   - Add shielding or reposition the receiver if needed.
2. **Obstacle Detection Not Working**:
   - Verify sensor connections and ensure the obstacle is within the detection range.
3. **Car Doesn’t Move**:
   - Check motor connections, enable pin status, and power supply.

---

## Future Enhancements
- Add Bluetooth or Wi-Fi control for smartphone compatibility.
- Implement autonomous navigation using additional sensors.
- Enhance obstacle detection with multi-directional sensors.

---

## Acknowledgments
Special thanks to the Arduino and open-source communities for their libraries and resources.

---

## License
This project is open-source and licensed under the MIT License.
