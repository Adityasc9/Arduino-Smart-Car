#include <Arduino.h>
#include "movement.h"
#include <IRremote.h>

// Motor control pins
int left = 5;
int lf = 6;
int lb = 7;
int right = 10;
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
#define IR_SPEED_UP 0xF609FF00
#define IR_SPEED_DOWN 0xF807FF00


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
        if (IrReceiver.decode()) {
        uint32_t receivedCode = IrReceiver.decodedIRData.decodedRawData;

        if (receivedCode == IR_RESET) {
            reset();
            Serial.println("Reset");
            IrReceiver.resume();
            return;
        }

        if (receivedCode != IR_REPEAT) {
            handleIRCode(receivedCode);
        }

        Serial.print("Raw Data: ");
        Serial.println(receivedCode, HEX);

        IrReceiver.resume();
    }
}

int currentSpeed = 160; // Default speed
uint32_t last_code = 0;
void handleIRCode(uint32_t code) {
    if (code == IR_SPEED_UP) {
        currentSpeed += 15; // Increase speed
        currentSpeed = constrain(currentSpeed, 60, 255);
        switch(last_code){
            case IR_UP:
                forward(currentSpeed);
                break;
            case IR_DOWN:
                reverse(currentSpeed);
                break; 
            case IR_LEFT:
                turnLeft(currentSpeed);
                break;
            case IR_RIGHT:
                turnRight(currentSpeed);
                break;
        }
        return;
    } else if (code == IR_SPEED_DOWN) {
        currentSpeed -= 15; // Decrease speed
        currentSpeed = constrain(currentSpeed, 60, 255);
        switch(last_code){
            case IR_UP:
                forward(currentSpeed);
                break;
            case IR_DOWN:
                reverse(currentSpeed);
                break;
            case IR_LEFT:
                turnLeft(currentSpeed);
                break;
            case IR_RIGHT:
                turnRight(currentSpeed);
                break;
        }
        return;
    } 

    // Constrain speed to limits
    
    Serial.println(currentSpeed);

    switch(code){
        case IR_UP:
            Serial.println("Moving Forward");
            forward(currentSpeed);
            break;
        case(IR_LEFT):
            Serial.println("Turning Left");
            turnLeft(currentSpeed);
            break;
        case(IR_DOWN):
            Serial.println("Moving Backward");
            reverse(currentSpeed);
            break;
        case(IR_RIGHT):
            Serial.println("Turning Right");
            turnRight(currentSpeed);
            break;
    }
    last_code = code;
}