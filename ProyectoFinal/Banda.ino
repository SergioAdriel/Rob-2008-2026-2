// ===============================
// Banda transportadora con HC-SR04
// Arduino UNO + L298N
// ===============================

// -------- Sensor ultrasónico --------
const int trigPin = 9;
const int echoPin = 10;

// -------- Puente H L298N --------
const int motorPin1 = 12; // IN1
const int motorPin2 = 11; // IN2

// -------- Variables --------
long duration;
int distance;

void setup() {

  Serial.begin(9600);

  // Sensor ultrasónico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Motor
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);

  // Motor apagado
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
}

void loop() {

  // ---------- Medir distancia ----------
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");

  // ======================================
  // SOLO detectar MUY CERCA (2 cm)
  // ======================================
  if (distance > 0 && distance <= 4) {

    Serial.println("Barril detectado");

    // Espera 7 segundo
    delay(7000);

    // Encender banda
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);

    Serial.println("Banda encendida");

    // Menos tiempo porque va rápido
    delay(2000);

    // Apagar banda
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);

    Serial.println("Banda apagada");

    // Evita múltiples detecciones
    delay(1500);
  }

  delay(50);
}