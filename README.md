# Arduino Smart Car

This project showcases a remote-controlled robotic car powered by an Arduino Uno R3, with an infrared (IR) receiver for receiving signals and sensors for avoiding obstacles. The car is designed to navigate in all directions, adjust speed, and respond to obstacles using an ultrasonic sensor.

## Features
- **Directional Movement**: Move forward, backward, turn left, and turn right.
- **Speed Control**: Adjust speed up or down using IR remote commands.
- **Obstacle Detection**: Automatically stop and prevent forward or backward movement when obstacles are detected.
- **Remote Control**: Controlled via an IR remote, with defined commands for movement and functionality.

---

## Components
1. **Arduino Uno R3**
2. **Motor Driver**: TB6612FNG
3. **4 * DC Motors**
4. **IR Receiver Module**
5. **IR Remote**
6. **Ultrasonic Sensor**
7. **6V Power Supply** for motor controls
8. **9V Power Supply** for Arduino and powering other components (4 * AA battery)
9. Additional components: Wires, breadboard, and chassis

---

## Setup and Wiring
### Motor Driver Connections:
- **Left Motor**: Connected to `lf` (pin 6), `lb` (pin 7), and pwma a pin `left` (pin 5).
- **Right Motor**: Connected to `rf` (pin 13), `rb` (pin 12), and pwma b pin `right` (pin 10).
- **Standby Pin**: Pin 8, set HIGH to enable the motor driver.
- Vcc: 5V from arduino
- Vm (motor supply) of 6v from 4 * AA batteries

### IR Receiver:
- Connect to pin 2 on the Arduino.
- 3.3V pin from Arduino for power

### Ultrasonic Sensor:
- **Trigger Pin**: Pin 4
- **Echo Pin**: Pin 3
- Vcc: 5V from Arduino
  
---

## Installation
1. Clone the repository or copy the code to your Arduino IDE.
2. Install the necessary library:
   - [IRremote Library](https://github.com/Arduino-IRremote/Arduino-IRremote)
3. Upload the code to your Arduino board.
4. Monitor 9600 Baud Serial monitor.

---

## Usage
(COMMENT OUT Sensor_test.cpp as these are only tests and project wont compile if tests are not commented)
1. Turn on the car and ensure the motors are enabled.
2. Find a suitable IR remote such as a TV remote or LED light remote
3. Use the IR remote and find buttons and their hex values to input into the hex values into the definiations at the start of the code:
   - **Forward**: IR_UP button
   - **Backward**: IR_DOWN button
   - **Turn Left**: IR_LEFT button
   - **Turn Right**: IR_RIGHT button
   - **Increase Speed**: IR_SPEED_UP button
   - **Decrease Speed**: IR_SPEED_DOWN button
   - **Reset/Stop**: IR_RESET button
4. Use buttons to control car
5. Obstacle detection is automatic and prevents backward and forward movement when obstacles are within 25 cm.

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
2. **Obstacle Detection Not Working**:
   - Verify sensor connections and ensure the obstacle is within the detection range.
3. **Car Doesn’t Move**:
   - Check motor connections, enable pin status, and power supply.
   - Usually the motor power supple does not provide enough current to drive motors.

---

## Future Enhancements
- Add Bluetooth control for universal device compatibility using HC-05 Bluetooth module.
- Implement autonomous navigation using more sensors.
- Enhance obstacle detection with servo motor for ultrasonic sensor.

---

## License
This project is open-source and licensed under the MIT License.
