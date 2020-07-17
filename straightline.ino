#include <MPU6050_tockn.h>
#include <Wire.h>
#include <PID_v1.h>
bool rotationFlag=1;
double angle=0;
double lastAngle;
MPU6050 mpu6050(Wire);
double setAngle,angleSpeed,mappedSpeed;
double setAngle2,motorSpeed,mappedMotorSpeed;
PID myPID3(&angle, &motorSpeed, &setAngle2,20,10,5, DIRECT);

//Motor A(right)
const int motorPin1  = 3;  // Pin 14 of L293
const int motorPin2  = 4;  // Pin 10 of L293
//Motor B(left)
const int motorPin3  = 5; // Pin  7 of L293
const int motorPin4  = 6;  // Pin  2 of L293
PID myPID(&angle, &angleSpeed, &setAngle,15,2,2, DIRECT);
//distance constants
int trigPin = 11;    // Trigger
int echoPin = 12;    // Echo
double duration,distance,setDistance,lastDistance,mappedSpeed2;
bool distanceFlag;
double mySpeed=100;
PID myPID2(&distance, &mySpeed, &setDistance,25,0,0, DIRECT);
void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  setAngle=60;
  setAngle2=0;
  setDistance=20;
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(-255,255);
  myPID2.SetMode(AUTOMATIC);
  myPID2.SetOutputLimits(-255,255);
    myPID3.SetMode(AUTOMATIC);
  myPID3.SetOutputLimits(-255,255);
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(motorPin3, OUTPUT);
    pinMode(motorPin4, OUTPUT);
          pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
      //And this code will stop motors
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 0);
    analogWrite(motorPin3, 0);
    analogWrite(motorPin4, 0);
  
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
    pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // Convert the time into a distance
  lastDistance=distance;
  distance = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  Serial.print(distance);
  Serial.print("cm");
  
  // put your main code here, to run repeatedly:
mpu6050.update();
    angle=mpu6050.getAngleZ();
    Serial.print(angle);
    Serial.print("   ");
    myPID3.Compute();
    mappedMotorSpeed=map(motorSpeed,-255,255,90,110);

    analogWrite(motorPin1, 100);
    analogWrite(motorPin2, 0);
    analogWrite(motorPin3, mappedMotorSpeed);
    analogWrite(motorPin4, 0);
    Serial.print(mappedMotorSpeed );
    Serial.print("   " );
    Serial.println(motorSpeed );

    
    
    delay(100);
    
}
