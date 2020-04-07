#include <Smartcar.h>
BrushedMotor leftMotor(smartcarlib::pins::v2::leftMotorPins);
BrushedMotor rightMotor(smartcarlib::pins::v2::rightMotorPins);
DifferentialControl control(leftMotor, rightMotor);
const int TURNING_SPEED = 40;

SimpleCar car(control);
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  goForward(60);
  delay(1000);
  turnLeft(20);
 
}

void turnLeft (int angle){
  car.setSpeed(TURNING_SPEED);
  car.setAngle(-angle);
}

void goForward (int speed){
  car.setSpeed(speed);
  car.setAngle(0);
}
