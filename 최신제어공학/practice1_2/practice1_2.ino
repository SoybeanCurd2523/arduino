void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  
}

int s=0;
void loop() {

  if(Serial.available() > 0){ 
    s = Serial.parseInt();

    if(s == 1){
      digitalWrite(13, HIGH);
      Serial.println("On");
    }
    else if(s == 2){
      digitalWrite(13, LOW);
      Serial.println("Off");      
    }
  }
}
