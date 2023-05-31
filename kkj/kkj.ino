#include <ros.h>
#include <std_msgs/Float64.h>

ros::NodeHandle  nh;

// motor control pin
const int ENABLE = 3;
const int motorDirPin = 8; // L298 Input 1
const int motorPWMPin = 9; // L298 Input 2

const int ENABLE_2 = 4;
const int motorDirPin_2 = 10; // L298 Input 3
const int motorPWMPin_2 = 11; // L298 Input 4

int left_rpm = 255; // 0~255
int right_rpm = 255;


const int encoderPinA_L = 21;
const int encoderPinB_L = 20;
const int encoderPinA_R = 19;
const int encoderPinB_R = 18;
int encoderPos_L = 0;
int encoderPos_R = 0;
float left_encoder=0;
float right_encoder=0;

const float distance_perse = 31.41592/180./52.; //cm



// defines ToF's variables
long duration;
float distance;
const int trigPin = 42;
const int echoPin = 44;



void left_callback( const std_msgs::Float64& msg){
  left_rpm = (int)msg.data;
}

void right_callback(const std_msgs::Float64& msg2){ // note : msg2 
  right_rpm = (int)msg2.data; // note : msg2 
}


ros::Subscriber<std_msgs::Float64> left_sub("left_data", left_callback);
ros::Subscriber<std_msgs::Float64> right_sub("right_data", right_callback);

std_msgs::Float64 msg3;
ros::Publisher tof_pub("tof_data",&msg3); 

std_msgs::Float64 msg4;
ros::Publisher left_encoder_diff_pub("left_encoder_diff_data",&msg4);
std_msgs::Float64 msg5;
ros::Publisher right_encoder_diff_pub("right_encoder_diff_data",&msg5);



void doEncoderA_L(){  // when pulse A changes
  int A_L = encoderPos_L;
  
  if(digitalRead(encoderPinA_L)==digitalRead(encoderPinB_L))
    encoderPos_L--; 
  else
    encoderPos_L++;
    
  if(A_L+1 == encoderPos_L){
    left_encoder = left_encoder + distance_perse;
    }
  else if(A_L-1 == encoderPos_L){
    left_encoder = left_encoder - distance_perse;
    }
  }
void doEncoderB_L(){  // when pulse B changes
  int B_L = encoderPos_L;
  
  if(digitalRead(encoderPinA_L)==digitalRead(encoderPinB_L))
    encoderPos_L++; 
  else
    encoderPos_L--;
    
  if(B_L+1 == encoderPos_L){
    left_encoder = left_encoder + distance_perse;
    }
  else if(B_L-1 == encoderPos_L){
    left_encoder = left_encoder - distance_perse;
    }
  }


void doEncoderA_R(){
//  Serial.println("aa");
  int A_R = encoderPos_R;
  
  encoderPos_R += (digitalRead(encoderPinA_R)==digitalRead(encoderPinB_R))?1:-1;
  
  if(A_R+1 == encoderPos_R){
    right_encoder = right_encoder + distance_perse;
    }
  else if(A_R-1 == encoderPos_R){
    right_encoder = right_encoder - distance_perse;
    }
  }

void doEncoderB_R(){
//  Serial.println("bb");
  int B_R = encoderPos_R;
  
  encoderPos_R += (digitalRead(encoderPinA_R)==digitalRead(encoderPinB_R))?-1:1;
  
  if(B_R+1 == encoderPos_R){
    right_encoder = right_encoder + distance_perse;
    }
  else if(B_R-1 == encoderPos_R){
    right_encoder = right_encoder - distance_perse;
    }
  }


void setup() {

  nh.initNode();
  pinMode(motorDirPin, OUTPUT);
  pinMode(motorPWMPin, OUTPUT);
  pinMode(ENABLE, OUTPUT);
  
  pinMode(motorDirPin_2, OUTPUT);
  pinMode(motorPWMPin_2, OUTPUT);
  pinMode(ENABLE_2, OUTPUT);


  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 


  pinMode(encoderPinA_L, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(21), doEncoderA_L, CHANGE);
  pinMode(encoderPinB_L, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(20), doEncoderB_L, CHANGE);

  pinMode(encoderPinA_R, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(19), doEncoderA_R, CHANGE);
  pinMode(encoderPinB_R, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(18), doEncoderB_R, CHANGE);


//  Serial.begin(115200);
  
  nh.subscribe(left_sub);
  nh.subscribe(right_sub);
  nh.advertise(tof_pub);
  nh.advertise(left_encoder_diff_pub);
  nh.advertise(right_encoder_diff_pub);
}

void loop() {
  

//  Serial.print("encoderPos_L : ");
//  Serial.println(encoderPos_L); 
//
//  Serial.print("encoderPos_R : ");
//  Serial.println(encoderPos_R);
//  Serial.println("=======================");

  move(left_rpm, right_rpm);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;

  msg3.data=distance;
  tof_pub.publish(&msg3);

  msg4.data=left_encoder;
  left_encoder_diff_pub.publish(&msg4);
  msg5.data=right_encoder;
  right_encoder_diff_pub.publish(&msg5);

//  Serial.print("left_encoder_diff : ");
//  Serial.print(left_encoder);
//  Serial.print("right_encoder_diff : ");
//  Serial.print(right_encoder);
//  
//  Serial.print("distance : ");
//  Serial.print(distance);
//  Serial.println("cm");

  nh.spinOnce();
  delayMicroseconds(50);
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
