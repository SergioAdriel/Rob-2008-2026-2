// Practica 1 - Ejercicio 3
// Control de lavado de autos

const int LED0 = 10; // Movimiento
const int LED1 = 2;  // Inicio
const int LED2 = 3;  // Regadera
const int LED3 = 4;  // Enjabonado
const int LED4 = 5;  // Enjuagado
const int LED5 = 6;  // Secado

void setup() {
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
}

void moverAuto() {
  digitalWrite(LED0, HIGH); // Movimiento
  delay(1000);
  digitalWrite(LED0, LOW);
}

void estacion(int ledEstacion) {
  for(int i = 0; i < 2; i++) {  // Parpadeo medio segundo ON/OFF
    digitalWrite(ledEstacion, HIGH);
    delay(500);
    digitalWrite(ledEstacion, LOW);
    delay(500);
  }
}

void loop() {

  // Inicio
  estacion(LED1);
  moverAuto();

  // Regadera
  estacion(LED2);
  moverAuto();

  // Enjabonado
  estacion(LED3);
  moverAuto();

  // Enjuagado
  estacion(LED4);
  moverAuto();

  // Secado
  estacion(LED5);

  delay(2000); // Espera antes de repetir ciclo
}
