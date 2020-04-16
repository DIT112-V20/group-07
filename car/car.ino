#include <Smartcar.h>
#include <BluetoothSerial.h>

int trigPin = 19; //D19
int echoPin = 5; //D5
int MAX_DISTANCE = 300;
const auto pulsesPerMeter = 600;

BrushedMotor leftMotor(smartcarlib::pins::v2::leftMotorPins);
BrushedMotor rightMotor(smartcarlib::pins::v2::rightMotorPins);
DifferentialControl control (leftMotor, rightMotor);

GY50 gyroscope(37);
SR04 front(trigPin, echoPin, MAX_DISTANCE);

BluetoothSerial SerialBT;//fot the BT

DirectionlessOdometer leftOdometer(
    smartcarlib::pins::v2::leftOdometerPin,
    []() { leftOdometer.update(); },
    pulsesPerMeter);
DirectionlessOdometer rightOdometer(
    smartcarlib::pins::v2::rightOdometerPin,
    []() { rightOdometer.update(); },
    pulsesPerMeter);

SmartCar car(control, gyroscope, leftOdometer, rightOdometer);

void setup() {
    // put your setup code here, to run once:
  Serial.begin(9600);
  SerialBT.begin("Smartcar"); //Name of the BT in the car
 }

void loop() {
     // put your main code here, to run repeatedly:
  driveForward();
  delay(2000);
  stop();
  
  turnLeft(90);
  delay(1000);
  turnRight(90);
  delay(1000);
  driveForward();
  stop();
  reverse(40);
  delay(2000);
  car.enableCruiseControl();
  limitSpeed(0.05);
  delay(2000);
  
}
