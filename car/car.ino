#include <Smartcar.h>
#include <BluetoothSerial.h>
#include <SoftwareSerial.h>
#include <VL53L0X.h>
#include <Wire.h>


int trigPinFront = 19; //D19
int echoPinFront = 5; //D5
int MAX_DISTANCE = 300;

int trigPinRight = 33; //D33
int echoPinRight = 18; //D18

const auto pulsesPerMeter = 600;
const int TURN_ANGLE = 80;
const int REVERS_SPEED = 40;
const int GYRO_OFFSET = 22;

const int STOP_DIST = 15; //this distance is in centimiters for the front sensor
const int RIGHT_DIST = 30; // this distance is in cm and are for the sensor on the right side
const int LEFT_DIST = 300; //this distance is in millimiters for the right side sensors

const int RXPin = 17, TXPin = 16;
const uint32_t GPSBaud = 9600;

BrushedMotor leftMotor(smartcarlib::pins::v2::leftMotorPins);
BrushedMotor rightMotor(smartcarlib::pins::v2::rightMotorPins);
DifferentialControl control (leftMotor, rightMotor);

GY50 gyroscope(GYRO_OFFSET);
SR04 front(trigPinFront, echoPinFront, MAX_DISTANCE);
SR04 right(trigPinRight, echoPinRight, MAX_DISTANCE);

VL53L0X sensor;

BluetoothSerial SerialBT;//for the BT
SoftwareSerial SerialGPS(RXPin, TXPin);

DirectionlessOdometer leftOdometer(
  smartcarlib::pins::v2::leftOdometerPin,
[]() {
  leftOdometer.update();
},
pulsesPerMeter);
DirectionlessOdometer rightOdometer(
  smartcarlib::pins::v2::rightOdometerPin,
[]() {
  rightOdometer.update();
},
pulsesPerMeter);

SmartCar car(control, gyroscope, leftOdometer, rightOdometer);


//-------------------------------Set Up and Loop----------------------------------------------------//

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("## Connection to computer established ## \n");
  SerialBT.begin("Smartcar");//Name of the BT in the car
  SerialGPS.begin(GPSBaud);//for communication between GPS module and esp32
  pinMode(LED_BUILTIN, OUTPUT);
  SerialBT.register_callback(callback);
  Wire.begin();

  sensor.setTimeout(500);
  if (!sensor.init()){        //This checks if micro Lidar sensor is initialized and keeps in this state til it is.
    while(1){}
    }
  sensor.startContinuous(); 
}

void loop() {  
  // put your main code here, to run repeatedly:
  obstacleAvoidance();
  printToApp();
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
  int leftDistance = sensor.readRangeContinuousMillimeters();
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
