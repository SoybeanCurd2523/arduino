///////////////////////////// 선언 및초기화
#define PI 3.141592

int led = 13;
double t_prev;
double t_now;
double dt;
int CNT = 0;

int inputDeg = 0;

int inputDeg2 = 0;

double th_init = 0;
double final = 0;
double th_ref = 0;
double t = 0;


///////////////////////// 타이머 사용을 위한 레지스터 선언 및 기타

void setup() {
  pinMode(led, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  
  Serial.begin(9600);
  
  noInterrupts(); 
  TIME_INTERRUPT_REGISTER();
  interrupts();
  
  Timer3_init(); // setup timer 3
  Timer4_init(); // setup timer 4
  
  t_prev = micros();
}

void loop() {
  if(Serial.available() > 0) // 시리얼 모니터에서 new line 이면 문자열을 보내고 줄바꿈을 보낸다. no line ending으로
  {
    inputDeg = Serial.parseInt(); // 문자열을 정수로 변환
//    inputDeg2 = Serial.parseInt(); 
  t = 0;
  th_init = inputDeg;

  
  }
    
//    Serial.println(inputDeg);
//    Serial.println(inputDeg2);
}

/////////////////// 레지스터에서 설정한 주기마다(1ms) 타이머 인터럽트 실행
ISR(TIMER1_COMPA_vect){
  t_now = micros();
  dt = (t_now - t_prev); 
  t_prev = t_now;

  if(CNT % 1000 < 500)
    digitalWrite(led, HIGH);
  else
    digitalWrite(led, LOW);

  CNT++;
  t+=0.001;
  
  
  if(t<10){ th_ref = func_1_cos(t, th_init, inputDeg, 10); servoOut1(th_ref); }
  
//  servoOut1(inputDeg);
//  servoOut2(inputDeg2);
}

///////////////////////////////// 레지스터 설정
void TIME_INTERRUPT_REGISTER(){
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= (1<< WGM12);
  TCCR1B |= (0 << CS12) | (0 << CS11) | (1<< CS10);
  TCNT1 = 0;
  OCR1A = 16000-1;
  TIMSK1 |= (1 << OCIE1A);
}

void Timer3_init()
{
 DDRB |= 0b01100000; 
 TCCR3A = 0b10100010; 
 TCCR3B = 0b00011010; 
 ICR3 = 39999;
 OCR3A = 999;// 999가 0도, 2999가 90도, 4999가 180도, 그 이상은 안돌아감.
}

void Timer4_init()
{
 DDRB |= 0b01100000; 
 TCCR4A = 0b10100010; 
 TCCR4B = 0b00011010; 
 ICR4 = 39999;
 OCR4A = 999;// 999가 0도, 2999가 90도, 4999가 180도, 그 이상은 안돌아감.
}

void servoOut1(int deg) // 첫 번째 모터를 돌리는 함수.
{
  int duty;

  if(deg>180) deg=180;
  else if(deg<0) deg = 0;

  duty = (int)(999. + (4999.-999.)/180.*deg);
  OCR3A = duty;
}

void servoOut2(int deg) // 두 번째 모터를 돌리는 함수.
{
  int duty;

  if(deg>180) deg=180;
  else if(deg<0) deg = 0;

  duty = (int)(999. + (4999.-999.)/180.*deg);
  OCR4A = duty;
}

double func_1_cos(double t, double init, double final, double T)
{
  double ref, f;
  f = 1/(2*T);
  ref = (final - init) * 0.5 * (1-cos(2*PI*f*t) ) + init;
  return ref;
}
