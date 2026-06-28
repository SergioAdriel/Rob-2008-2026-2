// Control de 4 caminadoras con START y STOP

// Pines de las caminadoras (LEDs)
const int led1 = 8;
const int led2 = 9;
const int led3 = 10;
const int led4 = 11;

// Pines de los botones
const int startBtn = 2;
const int stopBtn  = 3;

// Variable para guardar el estado
bool sistemaEncendido = false;

void setup() {
  // Configuración de salidas
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  // Configuración de botones
  pinMode(startBtn, INPUT_PULLUP);
  pinMode(stopBtn, INPUT_PULLUP);

  // Todo apagado al iniciar
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
}

void loop() {

  // Si se presiona START
  if (digitalRead(startBtn) == LOW) {
    sistemaEncendido = true;
    delay(200); // Antirrebote
  }

  // Si se presiona STOP
  if (digitalRead(stopBtn) == LOW) {
    sistemaEncendido = false;
    delay(200); // Antirrebote
  }

  // Encender o apagar las caminadoras
  digitalWrite(led1, sistemaEncendido);
  digitalWrite(led2, sistemaEncendido);
  digitalWrite(led3, sistemaEncendido);
  digitalWrite(led4, sistemaEncendido);
}
