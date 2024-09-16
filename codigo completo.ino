#include <Servo.h>   // Incluye la biblioteca Servo si estás utilizando servos estándar
#include <HUSKYLENS.h> // Incluye la biblioteca de HuskyLens
#include <SoftwareSerial.h> // Para la comunicación serial con HuskyLens

// Configura los pines para los servos
int servoFemur1 = 5;
int servoFemur2 = 6;
int servoFemur3 = 7;
int servoFemur4 = 8;
int servoAbajo1 = 9;
int servoAbajo2 = 10;
int servoAbajo3 = 11;
int servoAbajo4 = 12;

// Configura los pines para los sensores ultrasónicos
const int trigPin1 = 2;
const int echoPin1 = 3;
const int trigPin2 = 4;
const int echoPin2 = 5;

// Configura el pin para el sensor MQ-2
const int mq2Pin = A0;  // Conectar la salida analógica del MQ-2 al pin analógico A0

// Configura la comunicación serial con HuskyLens
SoftwareSerial mySerial(10, 11); // RX, TX
HUSKYLENS huskylens;

#define OBSTACLE_DISTANCE 15  // Distancia en cm para detectar obstáculos
#define GAS_DETECTION_THRESHOLD 300  // Umbral de detección de gas

Servo servos[12];

// Inicializa el HuskyLens
void setup() {
  Serial.begin(9600);  // Comunicación serial con el PC
  mySerial.begin(9600);  // Comunicación serial con HuskyLens
  huskylens.begin(mySerial);
  
  // Configura los pines de los servos
  servos[0].attach(servoFemur1);
  servos[1].attach(servoFemur2);
  servos[2].attach(servoFemur3);
  servos[3].attach(servoFemur4);
  servos[4].attach(servoAbajo1);
  servos[5].attach(servoAbajo2);
  servos[6].attach(servoAbajo3);
  servos[7].attach(servoAbajo4);
  
  // Configura los pines de los sensores ultrasónicos
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  
  // Configura el pin del sensor MQ-2
  pinMode(mq2Pin, INPUT);

  // Configura HuskyLens para detectar rostros
  huskylens.writeAlgorithm(HUSKYLENSAlgorithmFaceRecognition);
}

void loop() {
  // Lee los sensores ultrasónicos
  int distance1 = measureDistance(trigPin1, echoPin1);
  int distance2 = measureDistance(trigPin2, echoPin2);
  
  // Lee el sensor MQ-2
  int gasLevel = analogRead(mq2Pin);
  
  if (distance1 < OBSTACLE_DISTANCE || distance2 < OBSTACLE_DISTANCE) {
    stopMovement();  // Detiene el movimiento si se detecta un obstáculo
  } else if (gasLevel > GAS_DETECTION_THRESHOLD) {
    stopMovement();  // Detiene el movimiento si se detecta gas
    Serial.println("¡Gas detectado!");
  } else {
    performNormalMovement();  // Realiza movimientos normales si no hay obstáculos ni gas
  }
  
  // Lee la HuskyLens para detección de rostros
  if (huskylens.request()) {
    if (huskylens.isFaceDetected()) {
      Serial.println("¡Rostro detectado!");
      moveToFace();  // Función para moverse hacia el rostro detectado
    }
  }
}

int measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.0344 / 2;  // Convertir el tiempo a distancia en cm
  return distance;
}

void stopMovement() {
  // Detiene todos los servos
  for (int i = 0; i < 12; i++) {
    servos[i].write(90);  // Ajusta a la posición neutral (o detén el movimiento)
  }
}

void performNormalMovement() {
  // Ejemplo de patrones de movimiento
  
  // Movimiento de avance
  for (int i = 0; i < 3; i++) {
    servos[0].write(45);
    servos[1].write(45);
    servos[2].write(135);
    servos[3].write(135);
    servos[4].write(45);
    servos[5].write(45);
    servos[6].write(135);
    servos[7].write(135);
    delay(500);
    
    // Movimiento de giro
    servos[0].write(30);
    servos[1].write(30);
    servos[2].write(150);
    servos[3].write(150);
    servos[4].write(30);
    servos[5].write(30);
    servos[6].write(150);
    servos[7].write(150);
    delay(500);
  }
  
  // Movimiento de retroceso
  servos[0].write(135);
  servos[1].write(135);
  servos[2].write(45);
  servos[3].write(45);
  servos[4].write(135);
  servos[5].write(135);
  servos[6].write(45);
  servos[7].write(45);
  delay(500);

  // Movimiento de giro en sentido contrario
  servos[0].write(150);
  servos[1].write(150);
  servos[2].write(30);
  servos[3].write(30);
  servos[4].write(150);
  servos[5].write(150);
  servos[6].write(30);
  servos[7].write(30);
  delay(500);
}

void moveToFace() {
  // Obtén la posición del rostro detectado desde HuskyLens
  int x = huskylens.getX(); // Posición X del rostro detectado
  int y = huskylens.getY(); // Posición Y del rostro detectado

  // Ajusta el movimiento basado en la posición X
  if (x < 150) { // Si el rostro está a la izquierda
    servos[0].write(60); // Gira hacia la izquierda
    servos[1].write(60);
    servos[2].write(120); // Ajusta según el ángulo deseado
    servos[3].write(120);
  } else if (x > 170) { // Si el rostro está a la derecha
    servos[0].write(120); // Gira hacia la derecha
    servos[1].write(120);
    servos[2].write(60); // Ajusta según el ángulo deseado
    servos[3].write(60);
  } else { // Si el rostro está en el centro
    servos[0].write(90); // Ajusta para avanzar
    servos[1].write(90);
    servos[2].write(90);
    servos[3].write(90);
  }

  // Ajusta el movimiento basado en la posición Y
  if (y < 120) { // Si el rostro está en la parte superior
    servos[4].write(90); // Mueve hacia adelante
    servos[5].write(90);
    servos[6].write(90); // Ajusta según el ángulo deseado
    servos[7].write(90);
  } else if (y > 140) { // Si el rostro está en la parte inferior
    servos[4].write(60); // Mueve hacia atrás
    servos[5].write(60);
    servos[6].write(60); // Ajusta según el ángulo deseado
    servos[7].write(60);
  }
  
  delay(500);
}
