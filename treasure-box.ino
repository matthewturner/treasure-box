#include <Servo.h>
#include <HCSR04.h>

Servo servoLid;
UltraSonicDistanceSensor sensorOpen (11, 10);
bool isOpen;

void setup() {
  Serial.begin(57600);
  Serial.println("Starting up...");
  servoLid.attach(12);
  closeLid();
}

void loop() {
  Serial.println("Checking distance...");
  double distance = sensorOpen.measureDistanceCm();
  if (distance == -1) {
    return;
  }
  
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > 10) {
    delay(500);
    return;
  }
      
  if (isOpen) {
    closeLid();
  } else {
    openLid();
  }

  delay(750);
}

void openLid() {
  Serial.println("Opening lid...");
  servoLid.write(0);
  isOpen = true;
}

void closeLid() {
  Serial.println("Closing lid...");
  servoLid.write(107);
  isOpen = false;
}
