#define ENA 3
#define IN1 4
#define IN2 5
#define ENB 6
#define IN3 8
#define IN4 7

#define L2IR A6
#define L1IR A3
#define CIR A2
#define R1IR A1
#define R2IR A0

#define LedR  9
#define LedG  10
#define LedB  11

#define TachBtn 12

bool sensors[3];
int sensorsV = 0;
bool flag = 0;

void setColor(int red, int green, int blue) {
  analogWrite(LedR, red);
  analogWrite(LedG, green);
  analogWrite(LedB, blue);
}

void SENSORS() {
  sensors[0] = digitalRead(L1IR) || digitalRead(L2IR);
  sensors[1] = digitalRead(CIR);
  sensors[2] = digitalRead(R2IR) || digitalRead(R1IR);
  sensorsV = (sensors[0] << 2) | (sensors[1] << 1) | sensors[2];
}
void FORWARD() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, 65);
  analogWrite(ENB, 65); 

  setColor(0, 255, 0);
}
void BACKWARD() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 80);
  analogWrite(ENB, 80);

  setColor(255, 0, 0);
}

void RIGHT() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 78);
  analogWrite(ENB, 85);

  setColor(0, 0, 255);
}

void LEFT() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, 85);
  analogWrite(ENB, 78);

  setColor(247, 219, 7);
}

void STOP() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(LedR, OUTPUT);
  pinMode(LedG, OUTPUT);
  pinMode(LedB, OUTPUT);

  pinMode(L2IR, INPUT);
  pinMode(L1IR, INPUT);
  pinMode(CIR, INPUT);
  pinMode(R1IR, INPUT);
  pinMode(R2IR, INPUT);

  pinMode(TachBtn, INPUT);

  while(true){
    setColor(255, 255, 255);
    delay(500);
    setColor(0, 0, 0);
    delay(500);
    if(digitalRead(TachBtn) == HIGH) break;
  }
    setColor(0, 0, 0);
    delay(500);
    setColor(255, 0, 0);
    delay(1000);
    setColor(247, 219, 7);
    delay(1000);
    setColor(0, 255, 0);
    delay(1000);
}

void loop() {
  SENSORS();
  switch (sensorsV) {
    case 0b010:
      FORWARD();
      break;

    case 0b110:
      STOP();
      delay(50);
      FORWARD();
      delay(150); 
      while (true) {
        LEFT();
        SENSORS();
        if (sensors[0] == 0 && sensors[1] == 1) break;
      }
      break;

    case 0b100:
      STOP();
      delay(20);
      BACKWARD();
      delay(60);
      while (true) {
        LEFT();
        SENSORS();
        if (sensors[0] == 0 && sensors[1] == 1) break;
      }
      break;

    case 0b011:

      while (true) {
        STOP();
        delay(40);
        BACKWARD();
        delay(50);
        RIGHT();
        delay(60);
        FORWARD();
        delay(60);
        SENSORS();
        if ((sensors[2] == 0 && sensors[1] == 1) || sensors[0] == 0) break;
      }
      break;

    case 0b000:
      flag = false;
      for (int i = 0; i < 90; i++) {
          SENSORS();
          if (sensors[0] == 1 || sensors[1] == 1 || sensors[2] == 1) {
              flag = true;
               break;
          }
          FORWARD();
          delay(10);
      }

      if (flag) {
          while (true) {
              FORWARD();
              SENSORS();
              if (sensors[0] == 1 || sensors[1] == 1 || sensors[2] == 1){ break;}
          }
      } 
      else {
        STOP();
        delay(70);
        flag = false;
        while (true) {
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, LOW);
          analogWrite(ENA, 80);
          analogWrite(ENB, 80);
          setColor(255, 255, 255);
          SENSORS();
          if (sensors[0] == 1 || sensors[1] == 1 || sensors[2] == 1) {
            BACKWARD();
            delay(70);
            break;
            }
        }
      }
    break;

    case 0b001:
      STOP();
      delay(20);
      BACKWARD();
      delay(60);
      while (true) {
        RIGHT();
        SENSORS();
        if (sensors[2] == 0 && sensors[1] == 1) break;
      }
      break;

    case 0b111:
      STOP();
      delay(20);
      BACKWARD();
      delay(20);
      while (true) {
        BACKWARD();
        SENSORS();
        if (sensors[0] == 0 || sensors[1] == 0 || sensors[2] == 0) break;
      }
      break;

    case 0b101:
      STOP();
      delay(20);
      BACKWARD();
      delay(20);
      while (true) {
        RIGHT();
        SENSORS();
        if (sensors[1] == 1 && sensors[1] == 1) break;
      }
      break;
  }
}
