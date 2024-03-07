#include <SoftwareSerial.h>

// 블루투스 연결
SoftwareSerial BTSerial(4, 5);  

// RED LED와 디지털 11 핀 연결
const int RED_PIN = 11;    
// GREEN LED와 디지털 10 핀 연결
const int GREEN_PIN = 10;  
// BLUE LED와 디지털 9 핀 연결
const int BLUE_PIN = 9;    

// 임시 변수들
int redTemp = 0;
int blueTemp = 0;
int greenTemp = 0;

// setup 함수는 스케치가 시작될 때 한 번만 실행
void setup() {
  // 11번 핀을 출력으로 설정
  pinMode(RED_PIN, OUTPUT);    
  // 10번 핀을 출력으로 설정
  pinMode(GREEN_PIN, OUTPUT);  
  // 9번 핀을 출력으로 설정
  pinMode(BLUE_PIN, OUTPUT);   
  
  // 시리얼 통신 시작
  Serial.begin(9600);
  BTSerial.begin(9600);
}

// loop 함수는 전원이 꺼질 때까지 반복 실행
void loop() {
  // 블루투스 모듈에서 데이터를 받았을 때 실행
  if (BTSerial.available()) {
    // RGB 값을 입력받음
    String inputString = BTSerial.readStringUntil('\n');
    
    // R, G, B 값의 위치 찾기
    int rIndex = inputString.indexOf('R');
    int gIndex = inputString.indexOf('G');
    int bIndex = inputString.indexOf('B');
    
    // R, G, B 값이 모두 존재하는지 확인
    if (rIndex != -1 && gIndex != -1 && bIndex != -1) {
      // 각 색상의 값을 문자열에서 추출하고 정수로 변환
      redTemp = inputString.substring(rIndex + 1, gIndex).toInt();
      greenTemp = inputString.substring(gIndex + 1, bIndex).toInt();
      blueTemp = inputString.substring(bIndex + 1).toInt();
    }
    
    // 입력받은 RGB 값을 시리얼 모니터로 출력
    Serial.print("R : ");
    Serial.println(redTemp);
    Serial.print("G : ");
    Serial.println(greenTemp);
    Serial.print("B : ");
    Serial.println(blueTemp); 
    
    // 각 색깔별로 입력받은 값만큼 LED 밝기 조절
    analogWrite(RED_PIN, redTemp);
    analogWrite(GREEN_PIN, greenTemp);
    analogWrite(BLUE_PIN, blueTemp);
    
    // 입력이 완료되면 temp 값을 초기화
    if (BTSerial.read() == 13) {
      redTemp = 0;
      greenTemp = 0;
      blueTemp = 0;
      Serial.println("Reset");
    }
  }
}
