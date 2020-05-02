#include <Servo.h>
#include <HCSR04.h>

Servo servoLid;
Servo servoLatch;
UltraSonicDistanceSensor sensorOpen (11, 10);
bool isOpen;

void setup() {
  Serial.begin(57600);
  Serial.println("Starting up...");
  servoLid.attach(12);
  servoLatch.attach(9);
  closeLid();
  lock();
  sensorOpen.measureDistanceCm();
}

void loop() {
  Serial.println("Checking distance...");
  double distance = sensorOpen.measureDistanceCm();
  if (distance == -1) {
    return;
  }
  
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > 5) {
    delay(500);
    return;
  }
      
  if (isOpen) {
    closeLid();
    lock();
  } else {
    unlock();
    openLid();
  }

  delay(750);
}

void openLid() {
  Serial.println("Opening lid...");
  servoLid.write(0);
  awaitReposition();
  isOpen = true;
}

void closeLid() {
  Serial.println("Closing lid...");
  servoLid.write(107);
  awaitReposition();
  isOpen = false;
}

void lock() {
  Serial.println("Locking lid...");
  servoLatch.write(140);
  awaitReposition();
}

void unlock() {
  Serial.println("Unlocking lid...");
  servoLatch.write(70);
  awaitReposition();
}

void awaitReposition() {
  delay(300);
}
