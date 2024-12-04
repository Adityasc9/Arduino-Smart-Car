#include <Arduino.h>
#include "movement.h"
#include <IRremote.h>
#include "sensor.h"

void obstacleDetectionOverrideTest() { // test obstacle detection
    Serial.println("Running Obstacle Detection Override Test...");

    forward(255);
    float front_distance = measureFrontDistance();

    if (front_distance < 25) {
        reset(); 
        Serial.println("Obstacle detected while moving backward. Test Passed.");
    } else {
        Serial.println("No obstacle detected while moving backward. Test Failed.");
    }

    reverse(255);

    float back_distance = measureBackDistance();

    if (back_distance < 25) {
        reset(); 
        Serial.println("Obstacle detected while moving backward. Test Passed.");
    } else {
        Serial.println("No obstacle detected while moving backward. Test Failed.");
    }


}

void speedControlTest() { // test for speed control
    Serial.println("Running Speed Control Test...");

    // Set initial speed
    int initialSpeed = 160; // Default speed
    forward(initialSpeed); // Move forward

    delay(1000); // Wait for a moment

    // Change speed
    initialSpeed += 15; // Increase speed
    initialSpeed = constrain(initialSpeed, 60, 255); // Ensure speed is within limits
    forward(initialSpeed); // Set new speed

    delay(1000);
    reset();

        // check if speed is faster visually.


    initialSpeed -= 15; // Increase speed
    initialSpeed = constrain(initialSpeed, 60, 255); // Ensure speed is within limits
    reverse(initialSpeed); // Set new speed

    delay(2000); // return to start location
    reset();

        // check if speed is slower (same as start) visually.



}

// Define IR hex codes to car functionality
int UP = 0xEA15FF00;
int LEFT = 0xE916FF00;
int DOWN = 0xE718FF00;
int RIGHT = 0xF20DFF00;
int RESET = 0xE619FF00;
int SPEED_UP = 0xF609FF00;
int SPEED_DOWN = 0xF807FF00;


// Function to test IR command recognition
void irCommandRecognitionTest(int code) {
    Serial.println("Running IR Command Recognition Test...");

    if (code == UP) {
        Serial.println("forward");
    } 
    else if (code == LEFT) {
        Serial.println("Turning Left");
    } 
    else if (code == DOWN) {
        Serial.println("reverse");
    } 
    else if (code == RIGHT) {
        Serial.println("Turning Right");
    } 
    else if (code == SPEED_DOWN) {
        Serial.println("speed lower");
    } 
    else if (code == SPEED_UP) {
        Serial.println("speed higher");
    } 
    else {
        Serial.println("Unknown command");
    }

    Serial.println("\n");
}