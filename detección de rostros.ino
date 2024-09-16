#include <HUSKYLENS.h> // Incluye la biblioteca de HuskyLens
#include <SoftwareSerial.h> // Para la comunicación serial con HuskyLens

//  se configura los pines para la comunicación serial con HuskyLens
SoftwareSerial mySerial(10, 11); // RX, TX
HUSKYLENS huskylens;

void setup() {
  Serial.begin(9600);  // Comunicación serial con el PC
  mySerial.begin(9600);  // Comunicación serial con HuskyLens
  huskylens.begin(mySerial);
  
  // Configuramos la HuskyLens para detectar rostros
  huskylens.writeAlgorithm(HUSKYLENSAlgorithmFaceRecognition);
  
  Serial.println("HuskyLens está configurado para la detección de rostros.");
}

void loop() {
  // Solicita datos a HuskyLens
  if (huskylens.request()) {
    if (huskylens.isFaceDetected()) {
      Serial.println("¡Rostro detectado!");
      
      // Obtiene la cantidad de rostros detectados
      int faceCount = huskylens.getObjectNumber();
      Serial.print("Número de rostros detectados: ");
      Serial.println(faceCount);
      
      for (int i = 0; i < faceCount; i++) {
        // Obtiene la posición (X, Y) y el tamaño (W, H) del rostro detectado
        int x = huskylens.getX(i);
        int y = huskylens.getY(i);
        int w = huskylens.getWidth(i);
        int h = huskylens.getHeight(i);
        
        // Muestra la información del rostro detectado
        Serial.print("Rostro ");
        Serial.print(i + 1);
        Serial.print(": X=");
        Serial.print(x);
        Serial.print(", Y=");
        Serial.print(y);
        Serial.print(", Ancho=");
        Serial.print(w);
        Serial.print(", Alto=");
        Serial.println(h);
      }
    } else {
      Serial.println("No se detectaron rostros.");
    }
  } else {
    Serial.println("No se pudo solicitar datos a HuskyLens.");
  }

  delay(500); // Retraso para evitar una lectura demasiado rápida
}

