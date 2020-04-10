#include <Smartcar.h>

BrushedMotor leftMotor(smartcarlib::pins::v2::leftMotorPins);
BrushedMotor rightMotor(smartcarlib::pins::v2::rightMotorPins);
DifferentialControl control (leftMotor, rightMotor);
SimpleCar car(control);

const int SPEED = 40; //Speed is 40% of capacity
const int TURNING_SPEED = 40;
const int STEERING_OFFSET = -11.5; //Steering angle is -11.5° to make the car drive straight


SmartCar car(control);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  driveForward();
  delay(1000);
  turnLeft(20);
  stop();
}

//Method for driving (straight) forward
 void driveForward(){
  car.setAngle(STEERING_OFFSET);
  car.setSpeed(SPEED);
 }

//Method for stopping the car
void stop() {
  car.setSpeed(0); 
 }
   
void turnLeft(int angle){
 car.setSpeed(TURNING_SPEED);
 car.setAngle(STEERING_OFFSET - angle);
}
