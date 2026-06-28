// Anuncio luminoso HOLA

// Pines LEDs
const int H = 6;
const int O = 7;
const int L = 8;
const int A = 9;

void setup() {
  // Configuración de los pines como salidas
  pinMode(H, OUTPUT);
  pinMode(O, OUTPUT);
  pinMode(L, OUTPUT);
  pinMode(A, OUTPUT);
}

void loop() {

  // Enciende la letra H durante 1 segundo
  digitalWrite(H, HIGH);
  delay(1000);
  digitalWrite(H, LOW);

  // Enciende la letra O durante 1 segundo
  digitalWrite(O, HIGH);
  delay(1000);
  digitalWrite(O, LOW);

  // Enciende la letra L durante 1 segundo
  digitalWrite(L, HIGH);
  delay(1000);
  digitalWrite(L, LOW);

  // Enciende la letra A durante 1 segundo
  digitalWrite(A, HIGH);
  delay(1000);
  digitalWrite(A, LOW);
}
