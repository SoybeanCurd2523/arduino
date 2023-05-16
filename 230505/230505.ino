

// motor control pin
const int motorDirPin = 8; // L298 Input 1
const int motorPWMPin = 9; // L298 Input 2

// encoder pin
const int encoderPinA = 2;
const int encoderPinB = 3;

float encoderPos = 0; // 0~4680
const float ratio = 360.0/180.0/52.0; // 360/4680 //0.07degree
bool dir_flag = HIGH;

float motorDeg = 0.0;






// digitalRead : HIGH or LOW return
void doEncoderA(){  // when pulse A changes
  if(digitalRead(encoderPinA)==digitalRead(encoderPinB))
    encoderPos++; 
  else
    encoderPos--; 
}

void doEncoderB(){  // when pulse B changes
  if(digitalRead(encoderPinA)==digitalRead(encoderPinB))
    encoderPos--; 
  else
    encoderPos++;
}

void doMotor(bool dir, int vel){
  digitalWrite(motorDirPin, dir);
  analogWrite(motorPWMPin, vel);
}

void setup() {
  
  pinMode(encoderPinA, INPUT_PULLUP);
  attachInterrupt(0, doEncoderA, CHANGE); 
 
  pinMode(encoderPinB, INPUT_PULLUP);
  attachInterrupt(1, doEncoderB, CHANGE);
 
  pinMode(motorDirPin, OUTPUT);

  
  Serial.begin(250000);
}

void loop() {
  
  motorDeg = (float)(encoderPos * ratio); 
  // motorDeg : 0~360 degree


  if(motorDeg > 360.0){
    Serial.println("reached 360 degree");
    dir_flag = LOW;
    motorDeg = 0.0;
  }

  if(motorDeg < 0.0){
    Serial.println("reached 0 degree");
    dir_flag = HIGH;
    motorDeg = 360.0;
  }
  
  doMotor(dir_flag, 100);

//
//  Serial.print("encoderPos : ");
//  Serial.println(encoderPos);
//  
//  Serial.print("motorDeg : ");
//  Serial.println(motorDeg);

  delayMicroseconds(50);
}
