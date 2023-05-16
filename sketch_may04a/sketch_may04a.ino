// motor control pin
const int motorDirPin = 8; // L298 Input 1
const int motorPWMPin = 9; // L298 Input 2

// encoder pin
const int encoderPinA = 2;
const int encoderPinB = 3;

float encoderPos = 0; // 0~4680
const float ratio = 360./180./52.; // 360/4680 //0.07degree
bool dir_flag = HIGH;

float targetDeg = 360; // goal angle

/* 
digitalRead(pin)  input : pin number , return : HIGH or LOW 
digitalWrite(pin, value)  input : pin number, HIGH or LOW, return : nothing
analogWrite(pin, value) input : pin number, duty cycle(int)(0~255), return : nothing

*/
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
  digitalWrite(motorDirPin, dir); // decide motor rotate direction 
  analogWrite(motorPWMPin, 255); // drive a motor at various speeds
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
  // motorDeg : 0~360 degree

  if(motorDeg > 360){
    Serial.println("reached 360 degree");
    dir_flag = LOW;
    motorDeg = 0;
    delayMicroseconds(2000);
  }

  if(motorDeg < 0){
    Serial.println("reached 0 degree");
    dir_flag = HIGH;
    motorDeg = 360;
    delayMicroseconds(2000);
  }
  
  doMotor(dir_flag, 255);


  Serial.print("encoderPos : ");
  Serial.println(encoderPos);
  
  Serial.print("   motorDeg : ");
  Serial.println(motorDeg);
}
