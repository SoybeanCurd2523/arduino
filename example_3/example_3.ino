//// motor control pin
//const int motorDirPin = 8; // L298 Input 1
//const int motorPWMPin = 9; // L298 Input 2
//
//const int motorDirPin_2 = 10; // L298 Input 3
//const int motorPWMPin_2 = 11; // L298 Input 4
//
//// encoder pin
//const int encoderPinA = 2;
//const int encoderPinB = 3;
//
//const int encoderPinA_2 = 20;
//const int encoderPinB_2 = 21;
//
//int encoderPos = 0;
//int encoderPos_2 = 0;
//const float ratio = 360./180./52.;
//
//// P control
//float Kp = 30;
//float targetDeg = 360;
//
//void doEncoderA(){  // when pulse A changes
//  Serial.println("doEncoderA()");
//  if(digitalRead(encoderPinA)==digitalRead(encoderPinB))
//    encoderPos++; 
//  else
//    encoderPos--; 
//}
//
//void doEncoderB(){  // when pulse B changes
//  Serial.println("doEncoderB()");
//  if(digitalRead(encoderPinA)==digitalRead(encoderPinB))
//    encoderPos--; 
//  else
//    encoderPos++;
//}
//
//
//void doEncoderA_2(){  // when pulse A changes
//  if(digitalRead(encoderPinA_2)==digitalRead(encoderPinB_2))
//    encoderPos_2++; 
//  else
//    encoderPos_2--; 
//}
//
//void doEncoderB_2(){  // when pulse B changes
//  if(digitalRead(encoderPinA_2)==digitalRead(encoderPinB_2))
//    encoderPos_2--; 
//  else
//    encoderPos_2++;
//}
//
//void doMotor(bool dir, int vel){
//  digitalWrite(motorDirPin, dir);
//  analogWrite(motorPWMPin, dir?(255 - vel):vel);
//}
//
//void doMotor_2(bool dir, int vel){
//  digitalWrite(motorDirPin_2, dir);
//  analogWrite(motorPWMPin_2, dir?(255 - vel):vel);
//}
//
//
//void setup() {
//  pinMode(encoderPinA, INPUT_PULLUP);
//  attachInterrupt(4, doEncoderA, CHANGE);
// 
//  pinMode(encoderPinB, INPUT_PULLUP);
//  attachInterrupt(5, doEncoderB, CHANGE);
// 
//  pinMode(motorDirPin, OUTPUT);
//
//  pinMode(encoderPinA_2, INPUT_PULLUP);
//  attachInterrupt(1, doEncoderA_2, CHANGE);
// 
//  pinMode(encoderPinB_2, INPUT_PULLUP);
//  attachInterrupt(0, doEncoderB_2, CHANGE);
// 
//  pinMode(motorDirPin_2, OUTPUT);
//  
//  Serial.begin(115200);
//}
//
//void loop() {
//  float motorDeg = float(encoderPos)*ratio;
//  float motorDeg_2 = float(encoderPos_2)*ratio;
// 
//  float error = targetDeg - motorDeg;
//  float error_2 = targetDeg - motorDeg_2;
//  
//  float control = Kp*error;
//  float control_2 = Kp*error_2;
//
//  doMotor( (control>=0)?HIGH:LOW, min(abs(control), 255));
//  doMotor_2( (control_2>=0)?HIGH:LOW, min(abs(control_2), 255));
//  
//  Serial.print("encoderPos : ");
//  Serial.println(encoderPos);
//  Serial.print("   motorDeg : ");
//  Serial.println(float(encoderPos)*ratio);
//  Serial.println("======================");
//
////  Serial.print("encoderPos_2 : ");
////  Serial.println(encoderPos_2);
////  Serial.print("   motorDeg_2 : ");
////  Serial.println(float(encoderPos_2)*ratio);
////  Serial.print("======================");
//
////  delayMicroseconds(100);
//}











////////////////////////


//
////// motor control pin
const int motorDirPin = 10; // L298 Input 1
const int motorPWMPin = 11; // L298 Input 2

// encoder pin
const int encoderPinA = 20;
const int encoderPinB = 21;

int encoderPos = 0;
const float ratio = 360./180./52.;

// P control
float Kp = 30;
float targetDeg = 360;

void doEncoderA(){  encoderPos += (digitalRead(encoderPinA)==digitalRead(encoderPinB))?1:-1;}
void doEncoderB(){  encoderPos += (digitalRead(encoderPinA)==digitalRead(encoderPinB))?-1:1;}

void doMotor(bool dir, int vel){
  digitalWrite(motorDirPin, dir);
  analogWrite(motorPWMPin, dir?(255 - vel):vel);
}

void setup() {
  pinMode(encoderPinA, INPUT_PULLUP);
  attachInterrupt(0, doEncoderA, CHANGE);
 
  pinMode(encoderPinB, INPUT_PULLUP);
  attachInterrupt(1, doEncoderB, CHANGE);
 
  pinMode(motorDirPin, OUTPUT);

  Serial.begin(115200);
}

void loop() {
  float motorDeg = float(encoderPos)*ratio;
 
  float error = targetDeg - motorDeg;
  float control = Kp*error;

  doMotor( (control>=0)?HIGH:LOW, min(abs(control), 255));

//  doMotor(HIGH, 255);

  Serial.print("encoderPos : ");
  Serial.print(encoderPos);
  Serial.print("   motorDeg : ");
  Serial.print(float(encoderPos)*ratio);
  Serial.print("   error : ");
    Serial.print(error);
  Serial.print("    control : ");
  Serial.print(control);
  Serial.print("    motorVel : ");
  Serial.println(min(abs(control), 255));
    delayMicroseconds(100);
}
