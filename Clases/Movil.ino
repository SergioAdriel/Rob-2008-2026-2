#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//================ LCD =================
LiquidCrystal_I2C lcd(0x27, 16, 2);

//================ MOTORES =================
int IN1 = 9;
int IN2 = 10;
int IN3 = 11;
int IN4 = 12;

//================ BOTONES =================
int btn1 = A0;
int btn2 = A1;
int btn3 = A2;
int btn4 = A3;

//================ LIMITES =================
int LIM1 = 7;
int LIM2 = 8;

//================ LINEA =================
int S5 = 2;
int S4 = 3;
int S3 = 4;
int S2 = 5;
int S1 = 6;

//================ ULTRASONIDO =================
int TRIG = 13;
int ECHO = 0;

//================ VARIABLES =================
bool modoLinea = false;
bool modoUltra = false;

bool antBtn3 = LOW;
bool antBtn4 = LOW;

//================================================
// LCD
//================================================
void mensajeLCD(String a, String b) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(a);
  lcd.setCursor(0, 1);
  lcd.print(b);
}

//================================================
// MOVIMIENTO
//================================================
void avanzar() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void retroceder() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void detener() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// Giro suave derecha
void derecha() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// Giro suave izquierda
void izquierda() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

//================================================
// DISTANCIA
//================================================
long medirDistancia() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duracion = pulseIn(ECHO, HIGH, 30000);
  if (duracion == 0) return 999;
  return duracion * 0.034 / 2;
}

//================================================
// SETUP
//================================================
void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
  pinMode(btn4, INPUT);

  // LIMITES NC
  pinMode(LIM1, INPUT_PULLUP);
  pinMode(LIM2, INPUT_PULLUP);

  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  lcd.init();
  lcd.backlight();

  mensajeLCD("Hola, soy", "ROBOTINA");
  delay(2000);
}

//================================================
// LOOP
//================================================
void loop() {

  //================ MENU =================
  if (!modoLinea && !modoUltra) {
    mensajeLCD("B1 B2 B3 B4", "Selecciona");
  }

  //================ BOTON 1 =================
  if (digitalRead(btn1) == HIGH) {
    while (digitalRead(btn1) == HIGH);

    mensajeLCD("Modo 1", "Demo");

    avanzar();
    delay(2000);

    detener();
    delay(500);

    retroceder();
    delay(2000);

    detener();
  }

  //================ BOTON 2 =================
  else if (digitalRead(btn2) == HIGH) {
    while (digitalRead(btn2) == HIGH);

    mensajeLCD("Modo 2", "Hasta choque");

    while (true) {

      // choque en limites NC
      if (digitalRead(LIM1) == HIGH || digitalRead(LIM2) == HIGH) {
        detener();
        mensajeLCD("CHOQUE!", "Retrocediendo");
        delay(500);

        retroceder();
        delay(1000);

        detener();
        break;
      }

      if (digitalRead(btn2) == HIGH) {
        while (digitalRead(btn2) == HIGH);
        detener();
        mensajeLCD("Modo 2", "Cancelado");
        break;
      }

      avanzar();
    }
  }

  //================ BOTON 3 =================
  bool estBtn3 = digitalRead(btn3);

  if (estBtn3 == HIGH && antBtn3 == LOW) {
    modoLinea = !modoLinea;
    modoUltra = false;

    if (modoLinea) {
      mensajeLCD("Modo Linea", "ACTIVADO");
    } else {
      detener();
      mensajeLCD("Modo Linea", "CANCELADO");
    }

    delay(300);
    while (digitalRead(btn3) == HIGH);
  }

  antBtn3 = digitalRead(btn3);

  //================ BOTON 4 =================
  bool estBtn4 = digitalRead(btn4);

  if (estBtn4 == HIGH && antBtn4 == LOW) {
    modoUltra = !modoUltra;
    modoLinea = false;

    if (modoUltra) {
      mensajeLCD("Modo Ultra", "ACTIVADO");
    } else {
      detener();
      mensajeLCD("Modo Ultra", "CANCELADO");
    }

    delay(300);
    while (digitalRead(btn4) == HIGH);
  }

  antBtn4 = digitalRead(btn4);

  //================ LINEA =================
  if (modoLinea) {

    // choque en linea
    if (digitalRead(LIM1) == HIGH || digitalRead(LIM2) == HIGH) {
      detener();
      mensajeLCD("CHOQUE!", "Detenido");
      modoLinea = false;
    }

    int v1 = digitalRead(S1);
    int v2 = digitalRead(S2);
    int v3 = digitalRead(S3);
    int v4 = digitalRead(S4);
    int v5 = digitalRead(S5);

    if (v3 == HIGH) {
      avanzar();
      mensajeLCD("LINEA", "FRENTE");
    }
    else if (v4 == HIGH || v5 == HIGH) {
      derecha();
      mensajeLCD("LINEA", "DERECHA");
      delay(50);
    }
    else if (v1 == HIGH || v2 == HIGH) {
      izquierda();
      mensajeLCD("LINEA", "IZQUIERDA");
      delay(50);
    }
    else {
      detener();
      mensajeLCD("LINEA", "BUSCANDO");
    }
  }

  //================ ULTRA =================
  if (modoUltra) {
    long d = medirDistancia();

    lcd.setCursor(0, 0);
    lcd.print("Dist:");
    lcd.print(d);
    lcd.print("cm   ");

    if (d < 10) {
      lcd.setCursor(0, 1);
      lcd.print("OBSTACULO!");

      detener();
      delay(200);

      retroceder();
      delay(500);

      derecha();
      delay(500);
    } else {
      lcd.setCursor(0, 1);
      lcd.print("AVANZANDO ");
      avanzar();
    }
  }
}