// Control de direccionales izquierda, derecha y luces de STOP con buzzer

// Pines de las entradas (botones)
const int izq = 8;
const int der = 9;
const int stopBtn = 10;

// Pin del buzzer
const int buzzer = 11;

// Pines de las luces direccionales izquierdas
int lucesIzq[] = {2, 3, 4};

// Pines de las luces direccionales derechas
int lucesDer[] = {5, 6, 7};

// Pines de las luces de STOP
int stopLeds[] = {12, 13};

void setup() {

  // Configuración de las entradas
  pinMode(izq, INPUT);
  pinMode(der, INPUT);
  pinMode(stopBtn, INPUT);

  // Configuración del buzzer
  pinMode(buzzer, OUTPUT);

  // Configuración de las luces direccionales como salidas
  for (int i = 0; i < 3; i++) {
    pinMode(lucesIzq[i], OUTPUT);
    pinMode(lucesDer[i], OUTPUT);
  }

  // Configuración de las luces de STOP como salidas
  for (int i = 0; i < 2; i++) {
    pinMode(stopLeds[i], OUTPUT);
  }
}

void loop() {

  // Si se presiona la direccional izquierda
  if (digitalRead(izq) == HIGH) {

    // Suena el buzzer una vez
    tone(buzzer, 1000);
    delay(200);
    noTone(buzzer);

    // Enciende la secuencia de derecha a izquierda
    for (int i = 2; i >= 0; i--) {
      digitalWrite(lucesIzq[i], HIGH);
      delay(300);
      digitalWrite(lucesIzq[i], LOW);
    }

  }

  // Si se presiona la direccional derecha
  if (digitalRead(der) == HIGH) {

    // Suena el buzzer una vez
    tone(buzzer, 1000);
    delay(200);
    noTone(buzzer);

    // Enciende la secuencia de izquierda a derecha
    for (int i = 0; i < 3; i++) {
      digitalWrite(lucesDer[i], HIGH);
      delay(300);
      digitalWrite(lucesDer[i], LOW);
    }

  }

  // Si se presiona el botón de STOP
  if (digitalRead(stopBtn) == HIGH) {

    // El buzzer suena tres veces
    for (int i = 0; i < 3; i++) {
      tone(buzzer, 1000);
      delay(200);
      noTone(buzzer);
      delay(200);
    }

    // Enciende las luces de STOP
    for (int i = 0; i < 2; i++) {
      digitalWrite(stopLeds[i], HIGH);
    }

    // Mantiene las luces encendidas por un segundo
    delay(1000);

    // Apaga las luces de STOP
    for (int i = 0; i < 2; i++) {
      digitalWrite(stopLeds[i], LOW);
    }

  }

}
