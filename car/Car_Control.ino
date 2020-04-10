
#include <Smartcar.h>

int trigPin = 19; //D19
int echoPin = 5; //D5
int MAX_DISTANCE = 300;
const int STEERING_OFFSET = -11.5;

SR04 front(trigPin, echoPin, MAX_DISTANCE);
BrushedMotor leftMotor(smartcarlib::pins::v2::leftMotorPins);
BrushedMotor rightMotor(smartcarlib::pins::v2::rightMotorPins);
DifferentialControl control(leftMotor, rightMotor);

SimpleCar car(control);

void setup()
{

  Serial.begin(9600);
  
}

void loop() {
  
  int distance = front.getDistance();

  if (distance <= 15 && distance > 0){ //stop when distance is less than 15 cm.
  car.setSpeed(0);
  }
  else{
    // Move forward in speed of 40% of the capacaty 
    car.setSpeed(40);
  }
  
}

void turnRight(int angle) {
  car.setSpeed(TURNING_SPEED);
  car.setAngle(STEERING_OFFSET + angle);
}
