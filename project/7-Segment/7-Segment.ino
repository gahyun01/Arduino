int position_pin[] = {13, 12, 11, 10};  // 4자리 결정 핀
int segment_pin[] = {2, 3, 4, 5, 6, 7, 8, 9};  // 세그먼트 제어 핀
const int delayTime = 1000;  // 일시정지 시간

// 0 ~ 9를 표현하는 세그먼트 값
byte data[] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE4, 0xFE, 0xE6};

void setup() {
  // 4자리 결정 핀을 출력으로 설정
  for (int i = 0; i < 4; i++) {
    pinMode(position_pin[i], OUTPUT);
  }
  // 세그먼트 제어 핀을 출력으로 설정
  for (int i = 0; i < 8; i++) {
    pinMode(segment_pin[i], OUTPUT);
  }
}

void loop() {
  int nu = 0;
  for (int j = 0; j < 9; j++) {
    int i = 0;
    // delayTime 동안 2ms마다 세그먼트 표시를 변경
    while (i < delayTime) {
      show_digit((nu) % 3 + 1, nu % 10);
      delay(1);
      show_digit((nu) % 3 + 2, (nu + 1) % 10);
      delay(1);
      i += 2;
    }
    nu++;
  }
}

void show_digit(int pos, int number) {
  // 해당 자리 선택
  for (int i = 0; i < 4; i++) {
    digitalWrite(position_pin[i], (i + 1 == pos) ? LOW : HIGH);
  }
  
  // 세그먼트 제어
  for (int i = 0; i < 8; i++) {
    byte segment_data = (data[number] & (0x01 << i)) >> i;
    digitalWrite(segment_pin[7 - i], segment_data == 1 ? HIGH : LOW);
  }
}
