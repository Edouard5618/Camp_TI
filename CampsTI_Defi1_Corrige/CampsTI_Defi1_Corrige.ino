// Ajout des bibliothèques de code nécessaire
#include <Arduino.h>    // Bibliothèque de base Arduino/ESP32
#include <ESP32Servo.h> // Bibliothèque pour le contrôle des moteurs

// Déclaration des PINs utilisées (voir schéma électrique)
#define POT_BASE_PIN 0
#define SERVO_BASE_PIN 6
#define POT_EPAULE_PIN 1
#define POT_COUDE_PIN 3
#define SERVO_EPAULE_PIN 7
#define SERVO_COUDE_PIN 8

// Définition de l'objet Servo pour la base
Servo BaseServo;
Servo EpauleServo;
Servo CoudeServo;

void setup()
{
  // Initialise la communication USB avec l'ordinateur
  Serial.begin(115200);
  delay(1000); // Delai d'une seconde

  // Initialise l'entrée (INPUT) pour lire la valeur du potentiomètre
  pinMode(POT_BASE_PIN, INPUT);
  pinMode(POT_EPAULE_PIN, INPUT);
  pinMode(POT_COUDE_PIN, INPUT);

  // Initialise le moteur de la pince
  BaseServo.attach(SERVO_BASE_PIN);
  EpauleServo.attach(SERVO_EPAULE_PIN);
  CoudeServo.attach(SERVO_COUDE_PIN);
}

void loop()
{
  // Variable de commande moteur
  int pot1_cmd = 0;

  // Lecture de la valeur du capteur
  int pot1Value = analogRead(POT_BASE_PIN);

  // Limiter l'action entre 0 et 180 degrés du moteur
  pot1_cmd = map(pot1Value, 0, 4095, 0, 180);

  // Afficher les valeurs sur le moniteur série
  Serial.println("Potentiometre: " + String(pot1Value) + ", Angle: " + String(pot1_cmd));

  // Envoie de la commande moteur
  BaseServo.write(pot1_cmd);

  int pot2Value = analogRead(POT_EPAULE_PIN);
  int pot2_cmd = map(pot2Value, 0, 4095, 0, 180);
  Serial.println("Potentiometre epaule: " + String(pot2Value) + ", Angle: " + String(pot2_cmd));
  EpauleServo.write(pot2_cmd);

  int pot3Value = analogRead(POT_COUDE_PIN);
  int pot3_cmd = map(pot3Value, 0, 4095, 0, 180);
  Serial.println("Potentiometre coude: " + String(pot3Value) + ", Angle: " + String(pot3_cmd));
  CoudeServo.write(pot3_cmd);

  delay(50);
}

