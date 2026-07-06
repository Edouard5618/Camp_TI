// Ajout des bibliothèques de code nécessaire
#include <Arduino.h>  // Bibliothèque de base Arduino/ESP32
#include <ESP32Servo.h> // Bibliothèque pour le contrôle des moteurs

// Déclaration des PINs utilisées (voir schéma électrique)
#define POT_BASE_PIN 0
#define SERVO_BASE_PIN 5

// Définition de l'objet Servo pour la base
Servo BaseServo;

void setup() {
  // Initialise la communication USB avec l'ordinateur
  Serial.begin(115200);
  delay(1000); // Delai d'une seconde
 
  // Initialise l'entrée (INPUT) pour lire la valeur du potentiomètre
  pinMode(POT_BASE_PIN, INPUT);
  
  // Initialise le moteur de la pince
  BaseServo.attach(SERVO_BASE_PIN);
}

void loop() {
  // Variable entre 2 lectures du capteur
  static int tAdc = 0;

  // Variable de commande moteur
  static int pot1_cmd = 0;
  
  // Régulation du temps entre 2 lectures / actions
  if (millis() - tAdc >= 50) {
    tAdc = millis(); // Assignation du temps de la dernière lecture

    // Lecture de la valeure du capteur
    int pot1Value = analogRead(POT_BASE_PIN);
   
    // Limiter l'action entre 50 et 180 degrés du moteur
    pot1_cmd = map(pot1Value, 0, 4095, 0, 180);

    Serial.print("Potentiometre: ");
    Serial.print(pot1Value);
    Serial.print(", Angle: ");
    Serial.println(pot1_cmd);s
  }

  // Envoie de la commande moteur
  BaseServo.write(pot1_cmd);
  delay(10);
}
