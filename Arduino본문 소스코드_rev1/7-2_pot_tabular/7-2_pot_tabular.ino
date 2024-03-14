// 가변저항 값을 표 형식으로 시리얼 터미널로 출력
const int POT = 0;     // 가변저항을 아날로그 0번 핀에 연결

void setup()
{
  Serial.begin(9600);     // 9600 보율로 시리얼 포트 통신 속도 설정
}

void loop()
{
  Serial.println("\nAnalog Pin\tRaw Value\tPercentage");
  Serial.println("------------------------------------------");
  for (int i = 0; i < 10; i++)
  {
    int val = analogRead(POT);    // 가변저항 값 읽기
    int per = map(val, 0, 1023, 0, 100);  // 백분율로 변환

    Serial.print("A0\t\t");
    Serial.print(val);      // 변환 전 원시 데이터 출력
    Serial.print("\t\t");
    Serial.print(per);      // 백분율로 변환한 아날로그 값 출력
    Serial.println("%");      // % 기호 출력 후 줄 바꿈
    delay(1000);        // 1초 대기 후 반복
  }
}
