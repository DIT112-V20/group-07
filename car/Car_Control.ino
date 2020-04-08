#include <Smartcar.h>

BrushedMotor leftMotor(smartcarlib::pins::v2::leftMotorPins);
BrushedMotor rightMotor(smartcarlib::pins::v2::rightMotorPins);
DifferentialControl control (leftMotor, rightMotor);
SimpleCar car(control);

const int SPEED = 40; //Speed is 40% of capacity

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  delay(500);
  drive(true);
  delay(500);
  drive(false);

}

//Method for stopping the car
void drive(bool MOVE) {
   if (MOVE == true) {
     car.setSpeed(SPEED);

   } else if (MOVE == false) {
     car.setSpeed(0);

   }
 }
