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

// Define IR hex codes to car functionality
#define IR_UP 0xEA15FF00
#define IR_LEFT 0xE916FF00
#define IR_DOWN 0xE718FF00
#define IR_RIGHT 0xF20DFF00
#define IR_REPEAT 0x0 // when holding down a button, 0x0 is constantly printed
#define IR_RESET 0xE619FF00
#define IR_SPEED_UP 0xF609FF00
#define IR_SPEED_DOWN 0xF807FF00


void handleIRCode(uint32_t code); 


uint32_t lastCode = 0; // Store the last received IR code

enum MovementState { NONE, FORWARD, BACKWARD, LEFT, RIGHT }; // to keep track of current state of car
MovementState currentMovement = NONE; // Initialize as no movement

void setup() {
    Serial.begin(9600); // serial baud rate
    IrReceiver.begin(IR, DISABLE_LED_FEEDBACK); // Start the receiver

    // Configure ultrasonic pins
    pinMode(Trig_back, OUTPUT);
    pinMode(Echo_back,INPUT);
    pinMode(Trig_front, OUTPUT);
    pinMode(Echo_front,INPUT);
    // Configure motor control pins
    pinMode(left, OUTPUT);
    pinMode(lf, OUTPUT);
    pinMode(lb, OUTPUT);
    pinMode(right, OUTPUT);
    pinMode(rf, OUTPUT);
    pinMode(rb, OUTPUT);
    pinMode(stby, OUTPUT);
    digitalWrite(stby, HIGH); // turn on the motor driver
}
bool block_back = false; // blocking movement if close to collision
bool block_front = false;

unsigned long lastDistanceMeasurement = 0; // Track last distance measurement time
const unsigned long measurementInterval = 250; // do it every 500ms


void loop() {
    
    unsigned long currentMillis = millis(); // Get the current time
    if (currentMillis - lastDistanceMeasurement >= measurementInterval) { 
        lastDistanceMeasurement = currentMillis; // Update last measurement time
        float back_distance = measureBackDistance(); // Measure distance front
        float front_distance = measureFrontDistance();  // measure distance back
        
        // Obstacle detection logic
        if (back_distance < 25 && currentMovement == BACKWARD) {
            reset();
            currentMovement = NONE;
            Serial.println("Obstacle detected! Stopping...");
            Serial.println(back_distance);
            block_back = true;
        }  else if (back_distance >= 25){
            block_back = false; // Clear the flag if no obstacle is detected
        }

        if (front_distance < 25 && currentMovement == FORWARD) {
            reset();
            currentMovement = NONE;
            Serial.println("Obstacle detected! Stopping...");
            Serial.println(front_distance);
            block_front = true;
        }  else if (front_distance >= 25){
            block_front = false; // Clear the flag if no obstacle is detected
        }

    }

    
    
    if (IrReceiver.decode()) { // 
        uint32_t receivedCode = IrReceiver.decodedIRData.decodedRawData; // current hex code

        if (receivedCode == IR_RESET) { // reset the car
            reset();
            currentMovement = NONE;
            IrReceiver.resume();
            return;
        }

        if (receivedCode != IR_REPEAT) { // only if not a repeat then execute new code
            handleIRCode(receivedCode); // handles all IR codes
        }

        Serial.println(receivedCode, HEX);

        IrReceiver.resume(); // wait for next signal
    }
    
}

int currentSpeed = 160; // Starting speed
uint32_t last_code = 0;
void handleIRCode(uint32_t code) {

    
    if (code == IR_SPEED_UP) {
        currentSpeed = constrain(currentSpeed + 25, 75, 255);
    } else if (code == IR_SPEED_DOWN) {
        currentSpeed = constrain(currentSpeed - 25, 75, 255);
    } 

    if (code == IR_SPEED_DOWN || code == IR_SPEED_UP){ // after changing speed, the car should continue doing previous movemen
        switch(last_code){
            case IR_UP:
                if (block_front == false) { // Allow reverse only if back is not blocked
                    forward(currentSpeed);
                    currentMovement = FORWARD;
                    Serial.print("block:");
                } else {
                    Serial.println("Cannot go forward! Path is blocked.");
                }
                break;
            case IR_DOWN:
                if (block_back == false) { // Allow reverse only if back is not blocked
                    reverse(currentSpeed);
                    currentMovement = BACKWARD;
                    Serial.print("block:");
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
        //last_code = code;
        return;
    }
    
    switch(code){
        case IR_UP:
            if (block_front == false) { // Allow reverse only if back is not blocked
                    forward(currentSpeed);
                    currentMovement = FORWARD;
                    Serial.print("block:");
                    Serial.println(block_front);
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
            if (block_back == false) { // Allow reverse only if back is not blocked
                reverse(currentSpeed);
                currentMovement = BACKWARD;
                Serial.print("block:");
                Serial.println(block_back);
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