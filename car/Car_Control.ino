#include <Smartcar.h>

BrushedMotor leftMotor(smartcarlib::pins::v2::leftMotorPins);
BrushedMotor rightMotor(smartcarlib::pins::v2::rightMotorPins);
DifferentialControl control (leftMotor, rightMotor);
SimpleCar car(control);

const int SPEED = 40; //Speed is 40% of capacity
const int STEERING_OFFSET = -11.5; //Steering angle is -11.5° to make the car drive straight

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
  car.setAngle(STEERING_OFFSET);
  car.setSpeed(SPEED);
}
