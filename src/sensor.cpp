#define trigPin 13
#define soundPin 12

void setup() {
    Serial.begin(9600);
    pinMode(trigPin, OUTPUT);
    pinMode(soundPin, INPUT);
}

void loop() {
    long duration, distance;

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(soundPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance <= 250) {
        tone(9, 400, 100);
    } else {
        noTone(9);
    }

    delay(50);
}
