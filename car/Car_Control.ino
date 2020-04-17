
const int SPEED = 40; //Speed is 40% of capacity
const int TURNING_SPEED = 40;
const int STEERING_OFFSET = -11.5; //Steering angle is -11.5° to make the car drive straight

//Method for driving (straight) forward
 void driveForward(){
  car.setAngle(STEERING_OFFSET);
  car.setSpeed(SPEED);
 }

//Method for stopping the car
void stop() {
  car.setAngle(0);
  car.setSpeed(0); 
 }
   
void turnLeft(int angle){
 car.setSpeed(TURNING_SPEED);
 car.setAngle(STEERING_OFFSET - angle);
}

void turnRight(int angle) {
  car.setSpeed(TURNING_SPEED);
  car.setAngle(STEERING_OFFSET + angle);
}

//make car reverse
void reverse(int speed){
   car.setAngle(STEERING_OFFSET);
   car.setSpeed(-speed);
  }

void limitSpeed(int speed){
   car.setAngle(STEERING_OFFSET);
   car.setSpeed(speed);
}

void ledBlink(){
  while (true){
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);                       // wait for a second
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
