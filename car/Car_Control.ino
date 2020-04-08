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

  stop();

}

//Method for stopping the car
void stop() {
   car.setSpeed(0); 
   
 }

//Method for driving (straight) forward
 void driveForward (){
  car.setSpeed(SPEED);
  car.setAngle(0);
}
