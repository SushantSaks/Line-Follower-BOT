//Both libraries has to be installed
#include <QTRSensors.h> 
#include <SparkFun_TB6612.h>

QTRSensors qtr;
const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];

float Kp = 0.07; //proportional control term (ex: 0.07); 

float Ki = 0.0008; //related to the integral control term (ex: 0.0008); 

float Kd = 0.6; //related to the derivative control term (ex: 0.6); 

int P;
int I;
int D;

int lastError = 0;
boolean onoff = false;

const uint8_t maxspeeda = 150;
const uint8_t maxspeedb = 150;
const uint8_t basespeeda = 75;
const uint8_t basespeedb = 75;

#define AIN1 3
#define BIN1 7
#define AIN2 4
#define BIN2 8
#define PWMA 5
#define PWMB 6
#define STBY 9

int buttoncalibrate = 11;
int buttonstart = 10;

const int offsetA = 1;
const int offsetB = 1;

// Initializing motors.
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

void setup() {
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5, A6, A7}, SensorCount);
  qtr.setEmitterPin(2);//LEDON PIN

  
  delay(500);
  pinMode(LED_BUILTIN, OUTPUT);

  boolean Ok = false;
  while (Ok == false) { // the main function won't start until the robot is calibrated
    if(digitalRead(buttoncalibrate) == HIGH) {
      calibration(); //calibrate the robot for 10 seconds
      Ok = true;
    }
  }
  brake(motor1, motor2);
}

// Fuction for calibrating the QTR Array
void calibration() {
  digitalWrite(LED_BUILTIN, HIGH);
  for (uint16_t i = 0; i < 400; i++)
  {
    qtr.calibrate();
  }
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  if(digitalRead(buttonstart) == HIGH) {
    onoff =! onoff;
    if(onoff = true) {
      delay(1000);//a delay when the robot starts
    }
    else {
      delay(50);
    }
  }
  if (onoff == true) {
    PID_control();
  }
  else {
    brake(motor1, motor2);
  }
}

// To control the speed of the two motors individually

void motor_drive(int posa, int posb) {
  brake(motor1, motor2);
  motor1.drive(posa);
  motor2.drive(posb);
}

// PID control system
void PID_control() {
  uint16_t position = qtr.readLineBlack(sensorValues); //read the current position
  int error = position-3500; //3500 is the ideal position (the centre)

  P = error;
  I = I + error;
  D = error - lastError;
  lastError = error;
  int motorspeed = P*Kp + I*Ki + D*Kd; //calculate the correction factor
  
  int motorspeeda = basespeeda + motorspeed;
  int motorspeedb = basespeedb - motorspeed;
  
  if (motorspeeda > maxspeeda) {
    motorspeeda = maxspeeda;
  }
  if (motorspeedb > maxspeedb) {
    motorspeedb = maxspeedb;
  }
  if (motorspeeda < 0) {
    motorspeeda = 0;
  }
  if (motorspeedb < 0) {
    motorspeedb = 0;
  } 
  motor_drive(motorspeeda, motorspeedb);
}