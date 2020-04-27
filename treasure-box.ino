#include <Servo.h>
#include <HCSR04.h>

Servo servoLid;
UltraSonicDistanceSensor sensorOpen (11, 10);
bool isOpen;

void setup() {
  Serial.begin(9600);
  servoLid.attach(12);
  servoLid.write(90);
  isOpen = false;
}

void loop() {
  double distance = sensorOpen.measureDistanceCm();
  if (distance == -1) {
    return;
  }
  
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance < 10) {    
    if (isOpen) {
      servoLid.write(90);
    } else {
      servoLid.write(0);
    }

    isOpen = !isOpen;
    delay(500);
  }
}
