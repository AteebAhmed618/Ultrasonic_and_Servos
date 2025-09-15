// Define the pins for the ultrasonic sensor.
// trigPin sends the ultrasonic pulse.
// echoPin receives the reflected pulse.
#include <Servo.h>

const int servoPin = 9;
const int trigPin = 10;
const int echoPin = 11;


// Variables to store the duration of the pulse and the calculated distance.
long duration;
int distanceCm;
Servo myServo;

void setup() {
  // Configure the trigPin as an OUTPUT.
  pinMode(trigPin, OUTPUT);
  // Configure the echoPin as an INPUT.
  pinMode(echoPin, INPUT);

  // Initialize the Serial Monitor for communication with the computer.
  Serial.begin(9600);
  myServo.attach(servoPin);
}

void loop() {
  // The trigPin sends a high pulse to start the measurement.
  // First, we ensure the pin is low for a clean signal.
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send a 10-microsecond high pulse to the sensor.
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // The `pulseIn()` function waits for the echo pin to go HIGH,
  // then measures the duration of that HIGH signal in microseconds.
  // This duration is the time it took for the sound wave to travel to the object and back.
  duration = pulseIn(echoPin, HIGH);

  // Convert the time to distance.
  // Speed of sound is 343 m/s, or 0.0343 cm/µs.
  // The sound travels there and back, so we divide the total distance by 2.
  // Distance = (Duration * Speed of Sound) / 2
  distanceCm = duration * 0.0343 / 2;

  if (0 <= distanceCm && distanceCm <= 10) {
    myServo.write(90);
    delay(15);
  } else {
    myServo.write(180);
  }

  // Print the calculated distance to the Serial Monitor.
  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.println(" cm");

  // A small delay to prevent the Serial Monitor from being overwhelmed.
  delay(100);
}
