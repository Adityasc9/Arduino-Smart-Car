#include <Arduino.h>
#include "movement.h"
#include <IRremote.h>
#include "sensor.h"

// Motor control pins
int left = 5;
int lf = 6;
int lb = 7;
int right = 10;
int rf = 13;
int rb = 12;
int stby = 8;
int Trig_back = 4;
int Echo_back = 3;
int Trig_front = 9;
int Echo_front = 11;
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

enum MovementState { NONE, FORWARD, BACKWARD, LEFT, RIGHT };
MovementState currentMovement = NONE; // Initialize as no movement

void setup() {
    Serial.begin(9600); // Establish serial communication
    IrReceiver.begin(IR, DISABLE_LED_FEEDBACK); // Start the receiver

    // Configure motor control pins
    pinMode(Trig_back, OUTPUT);
    pinMode(Echo_back,INPUT);
    pinMode(Trig_front, OUTPUT);
    pinMode(Echo_front,INPUT);
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
bool block_back = false;
bool block_front = false;

unsigned long lastDistanceMeasurement = 0; // Track last measurement time
const unsigned long measurementInterval = 500; // 1 second interval


void loop() {
    unsigned long currentMillis = millis(); // Get the current time
    if (currentMillis - lastDistanceMeasurement >= measurementInterval) {
        lastDistanceMeasurement = currentMillis; // Update last measurement time
        float back_distance = measureBackDistance(); // Measure distance from the sensor
        float front_distance = measureFrontDistance();  // measure distance from the front sensor
        Serial.println("checking distance");
        // Obstacle detection logic
        if (back_distance < 25 && currentMovement == BACKWARD) {
            reset();
            currentMovement = NONE;
            Serial.println("Obstacle detected! Stopping...");
            Serial.println(back_distance);
            delay(500); // Wait to prevent rapid stopping and starting
            block_back = true;
        } else {
            block_back = false; // Clear the flag if no obstacle is detected
        }

        if (front_distance < 25 && currentMovement == FORWARD) {
            reset();
            currentMovement = NONE;
            Serial.println("Obstacle detected! Stopping...");
            Serial.println(front_distance);
            delay(500); // Wait to prevent rapid stopping and starting
            block_front = true;
        } else {
            block_front = false; // Clear the flag if no obstacle is detected
        }
    }

    
    
    if (IrReceiver.decode()) {
        uint32_t receivedCode = IrReceiver.decodedIRData.decodedRawData;

        if (receivedCode == IR_RESET) {
            reset();
            currentMovement = NONE;
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
    } else if (code == IR_SPEED_DOWN) {
        currentSpeed -= 15; // Decrease speed
        currentSpeed = constrain(currentSpeed, 60, 255);
        
    } 

    if (code == IR_SPEED_DOWN || code == IR_SPEED_UP){
        switch(last_code){
            case IR_UP:
                if (!block_front) { // Allow reverse only if back is not blocked
                    forward(currentSpeed);
                    currentMovement = FORWARD;
                } else {
                    Serial.println("Cannot go forward! Path is blocked.");
                }
                break;
            case IR_DOWN:
                if (!block_back) { // Allow reverse only if back is not blocked
                    reverse(currentSpeed);
                    currentMovement = BACKWARD;
                } else {
                    Serial.println("Cannot reverse! Backward path is blocked.");
                }
                break;
            case IR_LEFT:
                turnLeft(currentSpeed);
                currentMovement = LEFT;
                break;
            case IR_RIGHT:
                turnRight(currentSpeed);
                currentMovement = RIGHT;
                break;
        }
        return;

    }
    
    switch(code){
        case IR_UP:
            if (!block_front) { // Allow reverse only if back is not blocked
                    forward(currentSpeed);
                    currentMovement = FORWARD;
                } else {
                    Serial.println("Cannot go forward! Path is blocked.");
                }
            break;
        case(IR_LEFT):
            Serial.println("Turning Left");
            turnLeft(currentSpeed);
            currentMovement = LEFT;
            break;
        case(IR_DOWN):
            if (!block_back) { // Allow reverse only if back is not blocked
                reverse(currentSpeed);
                currentMovement = BACKWARD;
            } else {
                Serial.println("Cannot reverse! Backward path is blocked.");
            }
            break;
        case(IR_RIGHT):
            Serial.println("Turning Right");
            turnRight(currentSpeed);
            currentMovement = RIGHT;
            break;
    }
    Serial.println("\n");
    last_code = code;
}