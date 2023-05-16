//#include <ros.h>
//#include <std_msgs/Float64.h>
//​
//ros::NodeHandle  nh;
​
int echo = 6;
​
int trig = 7;
​
void setup() {
//  nh.initNode();
  Serial.begin(9600);
  
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}
​
void loop() {
​
  
digitalWrite(trig, LOW);
digitalWrite(echo, LOW);
delayMicroseconds(2);
digitalWrite(trig, HIGH);
delayMicroseconds(10);
digitalWrite(trig, LOW);
​
unsigned long duration = pulseIn(echo, HIGH); 
  
float distance = ((float)(340 * duration) / 10000) / 2;  
  
  Serial.print(distance);
  Serial.println("cm");
  delay(500);
​
}
