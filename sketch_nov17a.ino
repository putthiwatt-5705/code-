
#define TRIG 9
#define ECHO 10
#define BUZZER 8
#define RED_LED 7
#define GREEN_LED 6

// ความสูงของภาชนะ (เซนติเมตร)
const float tankHeight = 30.0;

// ระดับน้ำที่ต้องการให้แจ้งเตือน
const float warningLevel = 10.0;

void setup() {
  Serial.begin(9600);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
}

void loop() {

  // ส่งคลื่น Ultrasonic
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  // รับค่าระยะทาง
  long duration = pulseIn(ECHO, HIGH, 30000);

  if (duration == 0) {
    Serial.println("Sensor Error");
    delay(500);
    return;
  }

  float distance = duration * 0.0343 / 2;

  // คำนวณระดับน้ำ
  float waterLevel = tankHeight - distance;

  if (waterLevel < 0) {
    waterLevel = 0;
  }

  Serial.print("Water Level: ");
  Serial.print(waterLevel);
  Serial.println(" cm");

  // ตรวจสอบระดับน้ำ
  if (waterLevel >= warningLevel) {

    digitalWrite(BUZZER, HIGH);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);

    Serial.println("WARNING! WATER LEVEL HIGH!");

  } else {

    digitalWrite(BUZZER, LOW);
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);

    Serial.println("Water Level Normal");
  }

  delay(500);
}
