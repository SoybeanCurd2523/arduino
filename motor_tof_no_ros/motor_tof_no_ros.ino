#define PI 3.141592
#define deg2rad PI/180
#define T 10

int i = 0;

const int trigPin = 42;
const int echoPin = 44;

// motor control pin
const int ENABLE = 3;
const int motorDirPin = 8; // L298 Input 1
const int motorPWMPin = 9; // L298 Input 2

const int ENABLE_2 = 4;
const int motorDirPin_2 = 10; // L298 Input 3
const int motorPWMPin_2 = 11; // L298 Input 4

int left_rpm = 255; // 0~255
int right_rpm = 255;

// defines ToF's variables
long duration;
float distance;

void setup() {
 
  pinMode(motorDirPin, OUTPUT);
  pinMode(motorPWMPin, OUTPUT);
  pinMode(ENABLE, OUTPUT);
  
  pinMode(motorDirPin_2, OUTPUT);
  pinMode(motorPWMPin_2, OUTPUT);
  pinMode(ENABLE_2, OUTPUT);

  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 

  Serial.begin(57600);
}

void loop() {


//  Serial.print("left_rpm : ");
//  Serial.println(left_rpm); 



  right_rpm = 215 * ( ( 1+cos(i*deg2rad * 2*PI / T) ) /2) + 40 ;

  Serial.print("right_rpm : ");
  Serial.println(right_rpm);
  Serial.println("=======================");
  
  move(left_rpm, right_rpm);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  
//  Serial.print("distance : ");
//  Serial.print(distance);
//  Serial.println("cm");

  i+=5;
//  delayMicroseconds(10);
}

void move(int left_rpm, int right_rpm){
// right motor
  digitalWrite(motorDirPin, HIGH);
  digitalWrite(motorPWMPin, LOW);
  analogWrite(ENABLE, right_rpm);

// left motor
  digitalWrite(motorDirPin_2, HIGH);
  digitalWrite(motorPWMPin_2, LOW);
  analogWrite(ENABLE_2, left_rpm);
}
