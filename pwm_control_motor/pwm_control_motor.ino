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

void left_callback( const std_msgs::Float64& msg){

  left_rpm = (int)msg.data;
 
}

void right_callback(const std_msgs::Float64& msg2){ // note : msg2 

  right_rpm = (int)msg2.data; // note : msg2 
  
}

ros::Subscriber<std_msgs::Float64> left_sub("left_data", left_callback);

ros::Subscriber<std_msgs::Float64> right_sub("right_data", right_callback);

void setup() {
  nh.initNode();
  pinMode(motorDirPin, OUTPUT);
  pinMode(motorPWMPin, OUTPUT);
  pinMode(ENABLE, OUTPUT);
  
  pinMode(motorDirPin_2, OUTPUT);
  pinMode(motorPWMPin_2, OUTPUT);
  pinMode(ENABLE_2, OUTPUT);
  Serial.begin(57600);

  nh.subscribe(left_sub);
  nh.subscribe(right_sub);
}

void loop() {
  nh.spinOnce();

//  Serial.print("left_rpm : ");
//  Serial.println(left_rpm); 

  Serial.print("right_rpm : ");
  Serial.println(right_rpm);
  Serial.println("=======================");

  move(left_rpm, right_rpm);
  
  delayMicroseconds(10);
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
