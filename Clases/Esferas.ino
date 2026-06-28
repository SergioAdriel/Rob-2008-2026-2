// Encendido alternado de 4 esferas

// Pines esferas (LEDs)
const int esfera1 = 2;
const int esfera2 = 3;
const int esfera3 = 4;
const int esfera4 = 5;

void setup() {
  // Configuración de los pines como salidas
  pinMode(esfera1, OUTPUT);
  pinMode(esfera2, OUTPUT);
  pinMode(esfera3, OUTPUT);
  pinMode(esfera4, OUTPUT);
}

void loop() {

  // Encienden la Esfera 1 y la Esfera 3
  digitalWrite(esfera1, HIGH);
  digitalWrite(esfera3, HIGH);
  digitalWrite(esfera2, LOW);
  digitalWrite(esfera4, LOW);
  delay(1000);

  // Encienden la Esfera 2 y la Esfera 4
  digitalWrite(esfera1, LOW);
  digitalWrite(esfera3, LOW);
  digitalWrite(esfera2, HIGH);
  digitalWrite(esfera4, HIGH);
  delay(1000);
}
