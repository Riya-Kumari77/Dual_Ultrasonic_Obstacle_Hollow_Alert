// Sensor 1: Obstacle
#define trig1 5
#define echo1 4

// Sensor 2: Ground / Hollow
#define trig2 9
#define echo2 8

// Buzzer
#define buzzer 7

long d1, d2;

void setup() {
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);

  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);

  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
}

long readUltrasonic(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // 30 ms timeout
  if (duration == 0) return -1;  // invalid reading
  return duration * 0.034 / 2;
}

void loop() {

  // Read obstacle sensor
  d1 = readUltrasonic(trig1, echo1);
  delay(60);   // IMPORTANT to avoid cross-talk

  // Read ground sensor
  d2 = readUltrasonic(trig2, echo2);
  delay(60);

  Serial.print("Obstacle: ");
  Serial.print(d1);
  Serial.print(" cm | Ground: ");
  Serial.print(d2);
  Serial.println(" cm");

  // -------- BUZZER LOGIC --------
  if (d1 > 0 && d1 <= 20) {
    // Obstacle detected
    digitalWrite(buzzer, HIGH);
    delay(200);
    digitalWrite(buzzer, LOW);
    delay(200);
  }
  else if (d2 > 5) {
    // Hollow detected
    digitalWrite(buzzer, HIGH);
    delay(600);
    digitalWrite(buzzer, LOW);
    delay(600);
  }
  else {
    digitalWrite(buzzer, LOW);
  }
}