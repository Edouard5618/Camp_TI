// Ajout des bibliothèques de code nécessaire
#include <Arduino.h>
#include <ESP32Servo.h>
#include <Wire.h> // Bibliothèque de communication avec le IMU
#include <Adafruit_BNO055.h> // Bibliothèque du IMU

/* ---------------- À FAIRE ----------------
 *    Déclare la PIN pour le Servo BASE
--------------------------------------------
*/

// PINs de communication I2C
#define SDA_PIN 20 
#define SCL_PIN 21

// Déclaration du capteur IMU
Adafruit_BNO055 bno(0, 0x28);

/* ---------------- À FAIRE ----------------
 *  Déclare le moteur BASE
--------------------------------------------
*/

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

/* ---------------- À FAIRE ----------------
 *  Il manque une ligne de code dans la fonction
 *  Trouve laquelle et ajoute la
--------------------------------------------
*/
}

void loop() {
  static uint32_t tImu = 0;
  static int base_imu_cmd = 0;

  // Régulation du temps pour le IMU
  if(millis() - tImu >= 100) {
    tImu = millis();

    // Lecture de l'angle
    imu::Quaternion quat = bno.getQuat();
    float thz = quat.toEuler().z() / PI * 180.0;

    // Assignation de la commande
    base_imu_cmf = thz;
  }
  
/* ---------------- À FAIRE ----------------
 *  Envoie la commande au moteur
--------------------------------------------
*/
}
