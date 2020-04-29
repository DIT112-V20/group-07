#include <Smartcar.h>
#include <BluetoothSerial.h>
#include <VL53L0X.h>
#include <Wire.h>

//Ultrasonic sensors 
const int MAX_DISTANCE = 300;
const int trigPinFront = 19; //D19
const int echoPinFront = 5; //D5
const int trigPinRight = 33; //D33
const int echoPinRight = 18; //D18

//Constants 
const int STOP_DIST = 15; //this distance is in centimiters for the front sensor
const int RIGHT_DIST = 30; // this distance is in cm and are for the sensor on the right side
const int LEFT_DIST = 300; //this distance is in millimiters for the right side sensors
const int TURN_ANGLE = 90; //Turn degree for turning on the spot 
const int TURN_SPEED = 30; //Turn speed for turning on the spot 

//Constructors to control the motors  
BrushedMotor leftMotor(smartcarlib::pins::v2::leftMotorPins);
BrushedMotor rightMotor(smartcarlib::pins::v2::rightMotorPins);
DifferentialControl control (leftMotor, rightMotor);

//Gyroscope 
const int GYRO_OFFSET = 22;
GY50 gyroscope(GYRO_OFFSET);

//Sensors 
SR04 front(trigPinFront, echoPinFront, MAX_DISTANCE);
SR04 right(trigPinRight, echoPinRight, MAX_DISTANCE);
VL53L0X left;

//Bluetooth
BluetoothSerial SerialBT;

//Odometer 
const auto pulsesPerMeter = 600;
DirectionlessOdometer leftOdometer( smartcarlib::pins::v2::leftOdometerPin, []() { leftOdometer.update(); }, pulsesPerMeter);
DirectionlessOdometer rightOdometer( smartcarlib::pins::v2::rightOdometerPin, []() {rightOdometer.update(); },pulsesPerMeter);

//Smartcar constructor 
SmartCar car(control, gyroscope, leftOdometer, rightOdometer);


//-------------------------------Set Up and Loop----------------------------------------------------//

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SerialBT.begin("Smartcar"); //Name of the BT in the car
  pinMode(LED_BUILTIN, OUTPUT);
  SerialBT.register_callback(callback);
  Wire.begin();

  left.setTimeout(500);
  if (!left.init()){        //This checks if micro Lidar sensor is initialized and keeps in this state til it is.
    while(1){}
    }
  left.startContinuous(); 
}

void loop() {  
  // put your main code here, to run repeatedly:
  obstacleAvoidance();
}

//-------------------------------Set Up and Loop----------------------------------------------------//

//Method that detects if the smartcar is connected to bluetooth
void callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
  if (event == ESP_SPP_SRV_OPEN_EVT) { //If the smartcar has a bluetooth connection
    digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
  }

  if (event == ESP_SPP_CLOSE_EVT ) { //If the smartcar does not have a bluetooth connection
    stop();    
    
    while (true){
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(1000);                       // wait for a second
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      delay(1000);                       // wait for a second
    }
  }
}

void obstacleAvoidance() {
  int frontDistance = front.getDistance();
  int leftDistance = left.readRangeContinuousMillimeters();
  int rightDistance = right.getDistance();

  if (frontDistance <= STOP_DIST && frontDistance > 0){ //stop when distance is less than 15 cm.
    stop();
  }
  else if(leftDistance <= LEFT_DIST && leftDistance > 0 || rightDistance <= RIGHT_DIST && rightDistance > 0){
    stop();
  }
  else{
    handleInput();
  }
}

void handleInput() { //handle serial input (String!!)
  if (SerialBT.available()) { 
    String input;
    while (SerialBT.available()) { 
      input = SerialBT.readStringUntil('\n');   
    }; //read till last character
    
    if (input.startsWith("v")) {
      int throttle = input.substring(1).toInt();
      forward(throttle);
    }

    if (input.startsWith("b")) {
      int throttle = input.substring(1).toInt();
      reverse(throttle);
    }

    if (input.startsWith("t")) {
      int throttle = input.substring(1).toInt();
      turn(throttle);
    }  
  }
}

void turnInPlace(bool TURN) {
  int DEGREES;
  int CURRENT_POS;
  int TARGET_POS;
  int SPEED;
    
  if (TURN) {             //Turn right
    DEGREES = TURN_ANGLE; 
    SPEED = TURN_SPEED;
  } else {                //Turn left 
    DEGREES = -TURN_ANGLE; 
    SPEED = -TURN_SPEED;
  }   
  
  gyroscope.update(); //Get current heading and save it.   
  CURRENT_POS = gyroscope.getHeading();
  
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
