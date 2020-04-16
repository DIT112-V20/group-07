
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
   car.setSpeed(-speed);
  }

void limitSpeed(int speed){
   car.setSpeed(speed);
}
