#include <Arduino.h>
#include "movement.h"
#include <IRremote.h>

// Motor control pins
int left = 5;
int lf = 6;
int lb = 7;
int right = 11;
int rf = 13;
int rb = 12;
int stby = 8;

// IR Receiver pin
int IR = 2;

// Define IR codes
#define IR_UP 0xEA15FF00
#define IR_LEFT 0xE916FF00
#define IR_DOWN 0xE718FF00
#define IR_RIGHT 0xF20DFF00
#define IR_REPEAT 0x0 // Your repeat signal
#define IR_RESET 0xE619FF00
void handleIRCode(uint32_t code);

// Timeout for detecting IR release
unsigned long lastSignalTime = 0; // Timestamp of the last IR signal
const unsigned long signalTimeout = 100; // Timeout in milliseconds

uint32_t lastCode = 0; // Store the last received IR code

void setup() {
    Serial.begin(9600); // Establish serial communication
    IrReceiver.begin(IR, DISABLE_LED_FEEDBACK); // Start the receiver

    // Configure motor control pins
    pinMode(left, OUTPUT);
    pinMode(lf, OUTPUT);
    pinMode(lb, OUTPUT);
    pinMode(right, OUTPUT);
    pinMode(rf, OUTPUT);
    pinMode(rb, OUTPUT);
    pinMode(stby, OUTPUT);
    digitalWrite(stby, HIGH); // Enable the motor driver
    delay(1000); // Short startup delay
}

void loop() {
    if (IrReceiver.decode()) { // Check if an IR signal is received
        uint32_t receivedCode = IrReceiver.decodedIRData.decodedRawData; // Store the received code
        if(receivedCode != 0x0){
            handleIRCode(receivedCode);
        }
        if(receivedCode == IR_RESET){
            reset();
            Serial.println("reset"); 
            
        }
        Serial.print("Raw Data: ");
        Serial.println(receivedCode, HEX); // Print received raw data
        IrReceiver.resume();
    }
    
    
}

// Function to handle IR codes and control movement
void handleIRCode(uint32_t code) {
    if (code == IR_UP) {
        Serial.println("Moving Forward");
        forward(1, 150); // Move forward at 150 speed
    } else if (code == IR_LEFT) {
        Serial.println("Turning Left");
        turnLeft(90); // Turn left at 90 degrees
    } else if (code == IR_DOWN) {
        Serial.println("Moving Backward");
        reverse(1, 150); // Move backward at 150 speed
    } else if (code == IR_RIGHT) {
        Serial.println("Turning Right");
        turnRight(90); // Turn right at 90 degrees
    } else {
        Serial.println("Unknown Command");
    }
}