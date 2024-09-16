#include <Servo.h>
// Definir los pines de los servomotores
int servoFemur1 = 5;
int servoFemur2 = 6;
int servoFemur3 = 7;
int servoFemur4 = 8;
int servoAbajo1 = 9;
int servoAbajo2 = 10;
int servoAbajo3 = 11;
int servoAbajo4 = 12;

// Crear objetos Servo
Servo servoF1, servoF2, servoF3, servoF4;
Servo servoA1, servoA2, servoA3, servoA4;

void setup() {
  // Inicializar los servomotores
  servoF1.attach(servoFemur1);
  servoF2.attach(servoFemur2);
  servoF3.attach(servoFemur3);
  servoF4.attach(servoFemur4);
  servoA1.attach(servoAbajo1);
  servoA2.attach(servoAbajo2);
  servoA3.attach(servoAbajo3);
  servoA4.attach(servoAbajo4);
}

void loop() {
  // Mueve la pata hacia adelante
  moveForward();
  delay(1000);

  // Mueve la pata hacia atrás
  moveBackward();
  delay(1000);
}

void moveForward() {
  // Mueve los servos del fémur hacia arriba
  servoF1.write(35);
  servoF2.write(35);
  servoF3.write(35);
  servoF4.write(35);

  // Mueve los servos de la parte inferior hacia abajo
  servoA1.write(0);
  servoA2.write(0);
  servoA3.write(0);
  servoA4.write(0);
}

void moveBackward() {
  // Mueve los servos del fémur hacia abajo
  servoF1.write(0);
  servoF2.write(0);
  servoF3.write(0);
  servoF4.write(0);

  // Mueve los servos de la parte inferior hacia arriba
  servoA1.write(35);
  servoA2.write(35);
  servoA3.write(35);
  servoA4.write(35);
}
