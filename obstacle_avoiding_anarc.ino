#include <BluetoothSerial.h>
#include <Servo.h>

#define TRIG_PIN 23
#define ECHO_PIN 22
#define SERVO_PIN 19

BluetoothSerial SerialBT;
Servo myServo;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ObstacleAvoidingBot");
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  myServo.attach(SERVO_PIN);
  myServo.write(90);
}

void loop() {
  long duration, distance;

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 20) {
    Serial.println("Obstacle detected! Rotating sensor.");
    myServo.write(45);
    delay(500);
    distance = getDistance();
    if (distance < 20) {
      myServo.write(135);
      delay(500);
    }
    myServo.write(90);
  } else {
    Serial.println("Moving forward");
  }

  delay(100);
}

long getDistance() {
  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}
