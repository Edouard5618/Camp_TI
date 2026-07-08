//Alfred Lajeunesse

// Ajout des bibliothèques de code nécessaire
#include <Arduino.h>  // Bibliothèque de base Arduino/ESP32
#include <ESP32Servo.h> // Bibliothèque pour le contrôle des moteurs
#include <Wire.h> // Bibliothèque de communication avec le IMU
#include <Adafruit_BNO055.h> // Bibliothèque du IMU

// Déclaration des PINs utilisées (voir schéma électrique)
#define POT_PINCE_PIN 4
#define POT_BRAS1_PIN 1
#define POT_BRAS2_PIN 0

#define SERVO_PINCE_PIN 3
#define SERVO_JOINTPINCE_PIN 7
#define SERVO_BASE_PIN 8
#define SERVO_BRAS1_PIN 6
#define SERVO_BRAS2_PIN 10

// PINs de communication I2C
#define SDA_PIN 20 
#define SCL_PIN 21

// Déclaration du capteur IMU
Adafruit_BNO055 bno(0, 0x28);

// Définition de l'objet Servo pour la base
Servo PinceServo;
Servo JointPinceServo;
Servo BaseServo;
Servo Bras1Servo;
Servo Bras2Servo;

void setup() {
  // Initialise la communication USB avec l'ordinateur
  Serial.begin(115200);
  delay(1000); // Delai d'une seconde
 
  // Initialise l'entrée (INPUT) pour lire la valeur du potentiomètre
  pinMode(POT_PINCE_PIN, INPUT);
  pinMode(POT_BRAS1_PIN, INPUT);
  pinMode(POT_BRAS2_PIN, INPUT);
  
  
  // Initialise le moteur de la pince
  BaseServo.attach(SERVO_PINCE_PIN);
  Bras1Servo.attach(SERVO_BRAS1_PIN);
  Bras2Servo.attach(SERVO_BRAS2_PIN);
  JointPinceServo.attach(SERVO_JOINTPINCE_PIN);
  PinceServo.attach(SERVO_PINCE_PIN);

  // Initialisation de la communication avec le IMU
  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(50000);
  delay(1000);

  // Démarer le capteur IMU
  bno.begin();
  delay(500);
  bno.setExtCrystalUse(true);
}

void loop() {
  // Variable de commande moteur
  int pot1_cmd = 0;
  int pot2_cmd = 0;
  int pot3_cmd = 0;
  
  // Lecture de la valeur du capteur
  int pot1Value = analogRead(POT_PINCE_PIN);
  int pot2Value = analogRead(POT_BRAS1_PIN);
  int pot3Value = analogRead(POT_BRAS2_PIN);
 
  // Limiter l'action entre 0 et 180 degrés du moteur
  pot1_cmd = map(pot1Value, 0, 4095, 0, 180);
  pot2_cmd = map(pot2Value, 0, 4095, 0, 180);
  pot3_cmd = map(pot3Value, 0, 4095, 0, 180);

  // Afficher les valeurs sur le moniteur série
  Serial.println("Potentiometre 1: " + String(pot1Value) + ", Angle: " + String(pot1_cmd));
  Serial.println("Potentiometre 2: " + String(pot2Value) + ", Angle: " + String(pot2_cmd));
  Serial.println("Potentiometre 3: " + String(pot3Value) + ", Angle: " + String(pot3_cmd));

  // Envoie de la commande moteur
  PinceServo.write(pot1_cmd);
  Bras1Servo.write(pot2_cmd);
  Bras2Servo.write(pot3_cmd);

  static uint32_t tImu = 0;
  int base_imu_cmd = 0;
  int jointpince_imu_cmd = 0;

  // Régulation du temps pour le IMU
  if(millis() - tImu >= 100) {
    tImu = millis();

    // Lecture de l'angle
    imu::Quaternion quat = bno.getQuat();
    float angleY = quat.toEuler().y() / PI * 180.0;
    float angleX = quat.toEuler().x() / PI * 180.0;

    // Assignation de la commande
    base_imu_cmd = map(angleY, -180, 180, 0, 180);
    jointpince_imu_cmd = map(angleX, -180, 180, 0, 180);

    Serial.print("Angle Y: " + String(angleY));
    Serial.println(", base_imu_cmd: " + String(base_imu_cmd));
    Serial.print("Angle X: " + String(angleX));
    Serial.println(", jointpince_imu_cmd: " + String(jointpince_imu_cmd));
  }
  BaseServo.write(base_imu_cmd);
  JointPinceServo.write(jointpince_imu_cmd);
  
  
  
  delay(50);
}
