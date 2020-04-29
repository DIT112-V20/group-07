//Constants 
const int STEERING_OFFSET_FORWARD = -11.5; //Steering angle is -11.5° to make the car drive straight
const int STEERING_OFFSET_BAKWARDS = -6.7;
const int TURN_ANGLE = 90; //Turn degree for turning on the spot 
const int TURN_SPEED = 30; //Turn speed for turning on the spot 

//Method for driving (straight) forward
 void forward(int speed){
  car.setAngle(STEERING_OFFSET_FORWARD);
  car.setSpeed(speed); 
 }

//Method for stopping the car
void stop() {
  car.setAngle(0);
  car.setSpeed(0); 
 }

//Method for turning the car 
void turn(int angle){
 car.setAngle(STEERING_OFFSET_FORWARD + angle);
}

//Method for making the car reverse
void reverse(int speed){
   car.setAngle(STEERING_OFFSET_BAKWARDS);
   car.setSpeed(-speed);
}

//Makes the car travel a certain distance in centimeters. If centimeter is positive it goes forward, if centimeter is negative it oes backwards.
void goDistance(long centimeters, float speed)
{
    if (centimeters == 0)
    {
        return;
    }
    // Ensures the speed is towards the correct direction
    speed = smartcarlib::utils::getAbsolute(speed) * ((centimeters < 0) ? -1 : 1);
    car.setAngle(0);
    car.setSpeed(speed);

    long initialDistance = car.getDistance();
    bool hasReachedTargetDistance = false;
    while (!hasReachedTargetDistance)
    {
        car.update();
        auto currentDistance = car.getDistance();
        auto travelledDistance = initialDistance > currentDistance
                                     ? initialDistance - currentDistance
                                     : currentDistance - initialDistance;
        hasReachedTargetDistance = travelledDistance >= smartcarlib::utils::getAbsolute(centimeters);
    }
    car.setSpeed(0);
}

//Allows the car to turn on uts spot 
void turnInPlace(bool TURN) {
  int DEGREES;
  int SPEED;    
  if (TURN) {             //Turn right
    DEGREES = TURN_ANGLE; 
    SPEED = TURN_SPEED;
  } else {                //Turn left 
    DEGREES = -TURN_ANGLE; 
    SPEED = -TURN_SPEED;
  }   

  gyroscope.update(); //Get current heading and save it.   
  int CURRENT_POS = gyroscope.getHeading();
  int TARGET_POS;
  if (DEGREES + CURRENT_POS < 0) { // Calculate new heading and normalize it to [0-360).
    TARGET_POS = 360 + DEGREES + CURRENT_POS;
  } else {
    TARGET_POS = DEGREES + CURRENT_POS;
  }
  
  leftMotor.setSpeed(SPEED); //Invert motors to turn car in place. Right motors must turn
  rightMotor.setSpeed(-SPEED); //forward while left goes backward in order to turn left
  while (gyroscope.getHeading() < TARGET_POS - 3 || gyroscope.getHeading() > TARGET_POS + 3) {
    gyroscope.update();
  }
  
  stop();
  gyroscope.update();
}
