#include <ros.h>
#include <std_msgs/Float64.h>

ros::NodeHandle  nh;

int left_rpm = 0; // 0~255
int echo = 6;
int trig = 7;
void left_callback( const std_msgs::Float64& msg){

  left_rpm = (int)msg.data;
 
}
ros::Subscriber<std_msgs::Float64> left_sub("left_data", left_callback);

void setup() {
  // put your setup code here, to run once:
  nh.initNode();
  
  
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  Serial.begin(57600);
  nh.subscribe(left_sub);
}

void loop() {
  // put your main code here, to run repeatedly:
  nh.spinOnce();
  
  digitalWrite(trig, LOW);
  digitalWrite(echo, LOW);
  delayMicroseconds(1000);
  digitalWrite(trig, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig, LOW);

  unsigned long duration = pulseIn(echo, HIGH);
  float distance = ((float)(340*duration)/10000)/2;

  Serial.print(distance);
  Serial.println("cm");
  Serial.print("left_rpm : ");
  Serial.println(left_rpm);
  delay(100);
}
