#include <Servo.h>
#include <HCSR04.h>

Servo servoLid;
UltraSonicDistanceSensor sensorOpen (12, 11);

void setup() {
  Serial.begin(9600);
  servoLid.attach(10);
  servoLid.write(90);
}

void loop() {
  double distance = sensorOpen.measureDistanceCm();

  if (distance < 10) { 
    servoLid.write(0);
    delay(10000);
    servoLid.write(90);
  }
}
