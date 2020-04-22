const int STEERING_OFFSET_FORWARD = -11.5; //Steering angle is -11.5° to make the car drive straight
const int STEERING_OFFSET_BAKWARDS = -6.7;

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
   
void turn(int angle){
 car.setAngle(STEERING_OFFSET_FORWARD + angle);
}

//make car reverse
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
