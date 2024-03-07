// H-브리지를 사용한 모터 제어
const int EN = 9;   // H-브리지 1 활성화 핀
const int MC1 = 3;  // 모터 제어 1
const int MC2 = 2;  // 모터 제어 2
const int BUTTON1 = 4;   // 버튼 1 4번 핀에 연결
const int BUTTON2 = 7;   // 버튼 2 7번 핀에 연결
boolean lastButton1 = LOW;   // 버튼1의 이전 상태 저장
boolean currentButton1 = LOW;  // 버튼1의 현재 상태 저장
boolean lastButton2 = LOW;   // 버튼2의 이전 상태 저장
boolean currentButton2 = LOW;  // 버튼2의 현재 상태 저장
boolean MotorOn = false;  // 모터의 현재 상태 ( on / off)
const int POT = 0;  // 아날로그 0번 핀에 가변저항 연결

int val = 0;  // 가변저항 값 ( 0~1023 ) 저장
int velocity = 0;   // 모터 회전 속도 ( 0~255 ) 저장

void setup() {
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(EN, OUTPUT);
  pinMode(MC1, OUTPUT);
  pinMode(MC2, OUTPUT);
  brake();  // 모터를 정지한 상태로 초기화
}

boolean debounce(boolean last, int buttonPin) {
  boolean current = digitalRead(buttonPin);  // 버튼 상태 읽기
  if (last != current)      // 이전 상태와 현재 상태가 다르면...
  {
    delay(5);         // 5ms 대기
    current = digitalRead(buttonPin);  // 버튼 상태 다시 읽기
  }
  return current;       // 버튼의 현재 상태 반환
}

void loop() {
  val = analogRead(POT);

  currentButton1 = debounce(lastButton1, BUTTON1);  // 디바운싱된 버튼1 상태 읽기
  currentButton2 = debounce(lastButton2, BUTTON2);  // 디바운싱된 버튼2 상태 읽기

  if (lastButton1 == LOW && currentButton1 == HIGH) {
    if (MotorOn) {
      brake();  // 버튼1을 다시 누르면 모터를 정지
    } else {
      velocity = map(val, 563, 1023, 0, 255);
      forward(velocity); // 버튼1을 처음 누르면 모터를 정방향 회전
    }
    MotorOn = !MotorOn;  // 모터 상태를 반전
  }

  if (lastButton2 == LOW && currentButton2 == HIGH) {
    if (MotorOn) {
      brake();  // 버튼2를 누르면 모터를 정지
      MotorOn = false;  // 모터 상태를 OFF로 설정
    } else {
      velocity = map(val, 563, 1023, 0, 255);
      reverse(velocity); // 버튼2를 처음 누르면 모터를 역방향 회전
      MotorOn = true;  // 모터 상태를 ON으로 설정
    }
  }

  lastButton1 = currentButton1; // 이전 버튼 상태를 현재 버튼 상태로 설정
  lastButton2 = currentButton2; // 이전 버튼 상태를 현재 버튼 상태로 설정
}

// 모터를 주어진 속도 ( 0~255 )로 정방향으로 회전
void forward(int rate) {
  digitalWrite(EN, LOW);
  digitalWrite(MC1, HIGH);
  digitalWrite(MC2, LOW);
  analogWrite(EN, rate);
}

// 모터를 주어진 속도 ( 0~255 )로 역방향으로 회전
void reverse(int rate) {
  digitalWrite(EN, LOW);
  digitalWrite(MC1, LOW);
  digitalWrite(MC2, HIGH);
  analogWrite(EN, rate);
}

// 모터 정지
void brake() {
  digitalWrite(EN, LOW);
  digitalWrite(MC1, LOW);
  digitalWrite(MC2, LOW);
  digitalWrite(EN, HIGH);
}
