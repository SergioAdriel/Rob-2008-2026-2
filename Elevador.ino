// Botones
const int botonSubir = 2;
const int botonBajar = 3;

// Relevadores
const int releSubir = 8;
const int releBajar = 9;

// Display
const int segmentos[7] = {4,5,6,7,10,11,12};

// Estado
int pisoActual = 0;

// Control de botones (estado anterior)
bool estadoAnteriorSubir = HIGH;
bool estadoAnteriorBajar = HIGH;

// Tiempo de movimiento
const int tiempoMovimiento = 3000;

void setup() {
  pinMode(botonSubir, INPUT_PULLUP);
  pinMode(botonBajar, INPUT_PULLUP);

  pinMode(releSubir, OUTPUT);
  pinMode(releBajar, OUTPUT);

  for(int i=0; i<7; i++){
    pinMode(segmentos[i], OUTPUT);
  }

  mostrarPiso(pisoActual);
}

void loop() {
  bool lecturaSubir = digitalRead(botonSubir);
  bool lecturaBajar = digitalRead(botonBajar);

  // Detectar FLANCO (cuando se presiona)
  if (estadoAnteriorSubir == HIGH && lecturaSubir == LOW) {
    if (pisoActual < 2) {
      moverArriba();
      pisoActual++;
      mostrarPiso(pisoActual);
    }
  }

  if (estadoAnteriorBajar == HIGH && lecturaBajar == LOW) {
    if (pisoActual > 0) {
      moverAbajo();
      pisoActual--;
      mostrarPiso(pisoActual);
    }
  }

  // Guardar estado actual
  estadoAnteriorSubir = lecturaSubir;
  estadoAnteriorBajar = lecturaBajar;
}

// -------- FUNCIONES --------

void moverArriba() {
  digitalWrite(releSubir, HIGH);
  digitalWrite(releBajar, LOW);

  delay(tiempoMovimiento);

  detenerMotor();
}

void moverAbajo() {
  digitalWrite(releSubir, LOW);
  digitalWrite(releBajar, HIGH);

  delay(tiempoMovimiento);

  detenerMotor();
}

void detenerMotor() {
  digitalWrite(releSubir, LOW);
  digitalWrite(releBajar, LOW);
}

void mostrarPiso(int piso) {

  for(int i=0; i<7; i++){
    digitalWrite(segmentos[i], LOW);
  }

  if (piso == 0) { // P
    digitalWrite(segmentos[0], HIGH);
    digitalWrite(segmentos[1], HIGH);
    digitalWrite(segmentos[4], HIGH);
    digitalWrite(segmentos[5], HIGH);
    digitalWrite(segmentos[6], HIGH);
  }

  if (piso == 1) {
    digitalWrite(segmentos[1], HIGH);
    digitalWrite(segmentos[2], HIGH);
  }

  if (piso == 2) {
    digitalWrite(segmentos[0], HIGH);
    digitalWrite(segmentos[1], HIGH);
    digitalWrite(segmentos[6], HIGH);
    digitalWrite(segmentos[4], HIGH);
    digitalWrite(segmentos[3], HIGH);
  }
}