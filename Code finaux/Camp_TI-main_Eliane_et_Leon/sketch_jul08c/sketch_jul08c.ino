// Ajout des bibliothèques de code nécessaire
#include <Arduino.h>
#include <ESP32Servo.h>
#include <Wire.h> // Bibliothèque de communication avec le IMU
#include <Adafruit_BNO055.h> // Bibliothèque du IMU
#define POT_BASE_PIN 0
#define POT_BRAS_PIN 1
#define POT_PINCE_PIN 4

#define SERVO_BASE_PIN 8
#define SERVO_BRAS_PIN 6
#define SERVO_PINCE_PIN 10

#define SERVO_X_PIN 7

// PINs de communication I2C
#define SDA_PIN 20 
#define SCL_PIN 21

// Déclaration du capteur IMU
Adafruit_BNO055 bno(0, 0x28);

Servo XServo;
Servo BaseServo;
Servo BrasServo;
Servo PinceServo;

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Initialisation de la communication avec le IMU
  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(50000);
  delay(1000);

  // Démarer le capteur IMU
  bno.begin();
  delay(500);
  bno.setExtCrystalUse(true);

  pinMode(POT_BASE_PIN, INPUT);
  pinMode(POT_BRAS_PIN, INPUT);
  pinMode(POT_PINCE_PIN, INPUT);
  
  BaseServo.attach(SERVO_BASE_PIN);
  BrasServo.attach(SERVO_BRAS_PIN);
  PinceServo.attach(SERVO_PINCE_PIN);
  XServo.attach(SERVO_X_PIN);
}

void loop() {
  static uint32_t tImu = 0;
  int base_imu_cmd = 0;
  int pot1_cmd = 0;
  int pot2_cmd = 0;
  int pot3_cmd = 0;
  
  // Lecture de la valeur du capteur
  int pot1Value = analogRead(POT_BASE_PIN);
  int pot2Value = analogRead(POT_BRAS_PIN);
  int pot3Value = analogRead(POT_PINCE_PIN);



  // Régulation du temps pour le IMU
  if(millis() - tImu >= 100) {
    tImu = millis();

    // Lecture de l'angle
    imu::Quaternion quat = bno.getQuat();
    float angleZ = quat.toEuler().z() / PI * 180.0;

    // Assignation de la commande
    base_imu_cmd = map(angleZ, -180, 180, 0, 180);

    Serial.print("Angle Z: " + String(angleZ));
    Serial.println(", base_imu_cmd: " + String(base_imu_cmd));
    XServo.write(base_imu_cmd);

      pot1_cmd = map(pot1Value, 0, 4095, 0, 180);
  pot2_cmd = map(pot2Value, 0, 4095, 0, 180);
  pot3_cmd = map(pot3Value, 0, 4095, 0, 180);

  Serial.println("Potentiometre: " + String(pot1Value) + ", Angle: " + String(pot1_cmd));

  // Envoie de la commande moteur
  BaseServo.write(pot1_cmd);
  BrasServo.write(pot2_cmd);
  PinceServo.write(pot3_cmd);
  delay(50);
  }
  

  
 
}



/*
Mission supplémentaire : Contrôle complet avec l’IMU

Tu peux maintenant contrôler la base avec l’axe Z (droite-gauche) de l’IMU, mais
pourquoi s’arrêter là ? Ton objectif ultime est de remplacer les potentiomètres
de l’épaule et du coude par les angles X et Y de l’IMU (d’avant en arrière
ou sur le côté) !

Pour ce faire, tu devras :
1. Déclarer et attacher les moteurs de l’épaule et du coude (comme au Défi 1).
2. Extraire les angles ‘x‘ et ‘y‘ de l’IMU de la même manière que ‘z‘ (ex :
float angleX = quat.toEuler().x() / PI * 180.0;).
3. Envoyer ces angles à tes nouveaux moteurs !
*/
