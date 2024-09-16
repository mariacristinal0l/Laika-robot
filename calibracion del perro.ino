#include <Servo.h>

// Definiciones de servos
#define RFC 0
#define RFF 1
#define RFT 2
#define LFC 3
#define LFF 4
#define LFT 5
#define RRC 6
#define RRF 7
#define RRT 8
#define LRC 9
#define LRF 10
#define LRT 11

// Parámetros de longitud de los segmentos de la pata (en mm)
const int tibiaLength = 132;   // Longitud del tibia
const int femurLength = 105;   // Longitud del femur
const int coxaLength = 90;     // Longitud del coxa

// Definición de servos
Servo servos[12];

void setup() {
  // Inicializar servos
  for (int i = 0; i < 12; i++) {
    servos[i].attach(i + 2);  // Los servos están conectados a los pines 2 a 13
  }
  
  Serial.begin(9600);
}

void loop() {
  // Ejemplo de posición deseada (x, y, z) en mm
  float targetX = 100; // Posición deseada en X
  float targetY = 50;  // Posición deseada en Y
  float targetZ = -50; // Posición deseada en Z

  // Calcular los ángulos de los servos usando cinemática inversa
  float angles[3];
  calculateInverseKinematics(targetX, targetY, targetZ, angles);

  // Mover servos a las posiciones calculadas
  for (int i = 0; i < 3; i++) {
    servos[i].write(map(angles[i], 0, 180, 0, 180));  // Mapeo simple, ajustar según necesidad
  }
  
  delay(1000); // Esperar un segundo antes de la próxima iteración
}

// Función para calcular los ángulos de los servos usando cinemática inversa
void calculateInverseKinematics(float x, float y, float z, float angles[]) {
  // La cinemática inversa puede ser compleja dependiendo del robot
  // Este es un ejemplo simplificado
  
  float l = sqrt(x * x + y * y); // Distancia en el plano XY
  float d = sqrt(l * l + z * z); // Distancia desde el origen hasta el punto objetivo
  
  // Cálculo de ángulos, simplificado para el ejemplo
  angles[0] = atan2(y, x) * 180 / PI; // Ángulo de la base
  angles[1] = acos((l * l + d * d - tibiaLength * tibiaLength - femurLength * femurLength) / (2 * tibiaLength * femurLength)) * 180 / PI; // Ángulo del femur
  angles[2] = atan2(z, l) * 180 / PI; // Ángulo del tibia
}

