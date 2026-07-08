// Ajout des bibliothèques de code nécessaire
#include <Arduino.h>
#include <ESP32Servo.h>
#include <Wire.h>            // Bibliothèque de communication avec le IMU
#include <Adafruit_BNO055.h> // Bibliothèque du IMU

#define SERVO_BASE_PIN 6

// PINs de communication I2C
#define SDA_PIN 20
#define SCL_PIN 21

// Déclaration du capteur IMU
Adafruit_BNO055 bno(0, 0x28);

Servo BaseServo;

void setup()
{
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
  BaseServo.attach(SERVO_BASE_PIN);
}

void loop()
{
  static uint32_t tImu = 0;
  int base_imu_cmd = 0;

  // Régulation du temps pour le IMU
  if (millis() - tImu >= 100)
  {
    tImu = millis();

    // Lecture de l'angle
    imu::Quaternion quat = bno.getQuat();
    float angleZ = quat.toEuler().z() / PI * 180.0;

    // Assignation de la commande
    base_imu_cmd = map(angleZ, -180, 180, 0, 180);

    Serial.print("Angle Z: " + String(angleZ));
    Serial.println(", base_imu_cmd: " + String(base_imu_cmd));
  }

  BaseServo.write(base_imu_cmd);
}

/*
Mission supplémentaire : Contrôle complet avec l’IMU

Tu peux maintenant contrôler la base avec l’axe Z (droite-gauche) de l’IMU, mais
pourquoi s'arrêter là ? Ton objectif ultime est de remplacer les potentiomètres
de l’épaule et du coude par les angles X et Y de l’IMU (d’avant en arrière
ou sur le côté) !

Pour ce faire, tu devras :
1. Déclarer et attacher les moteurs de l’épaule et du coude (comme au Défi 1).
2. Extraire les angles ‘x‘ et ‘y‘ de l’IMU de la même manière que ‘z‘ (ex :
float angleX = quat.toEuler().x() / PI * 180.0;).
3. Envoyer ces angles à tes nouveaux moteurs !
*/