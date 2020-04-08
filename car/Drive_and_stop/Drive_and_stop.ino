#include <Smartcar.h>

BrushedMotor leftMotor(smartcarlib::pins::v2::leftMotorPins);
BrushedMotor rightMotor(smartcarlib::pins::v2::rightMotorPins);
DifferentialControl control (leftMotor, rightMotor);
SimpleCar car(control);

const int SPEED = 40; //Speed is 40% of capacity
const int MOVE = 1;
const int STOP = 0; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  delay(500);
  drive(MOVE);
  delay(500);
  drive(STOP);

}

//Method for stopping the car
void drive(int TEMP) {
  if (TEMP = 1) {
    car.setSpeed(SPEED);
  } 
  
  if (TEMP = 0) {
    car.setSpeed(0);
  }
}
