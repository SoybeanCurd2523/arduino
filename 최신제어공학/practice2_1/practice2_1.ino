int led = 13;
double t_prev;
double t_now;
double dt;
int CNT = 0;


/////////////////

void setup() {
  pinMode(13, OUTPUT);

  noInterrupts(); 
  TIME_INTERRUPT_REGISTER();

  interrupts();
  
  Serial.begin(9600);

  t_prev = micros();
}

void loop() {

  Serial.print(dt);
  Serial.println("[us]");
}

// timer interrupts in every cycle setting in register(1ms)
ISR(TIMER1_COMPA_vect){
  t_now = micros();
  dt = (t_now - t_prev); 
  t_prev = t_now;

  if(CNT % 1000 < 500)
    digitalWrite(led, HIGH);
  else
    digitalWrite(led, LOW);

  CNT++;
}

// register setting
void TIME_INTERRUPT_REGISTER(){
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= (1<< WGM12);
  TCCR1B |= (0 << CS12) | (0 << CS11) | (1<< CS10);
  TCNT1 = 0;
  OCR1A = 16000-1;
  TIMSK1 |= (1 << OCIE1A);
}
