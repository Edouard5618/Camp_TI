
// SAMUEL BÉRUBÉ

// Ajout des bibliothèques de code nécessaire
#include <Arduino.h>  // Bibliothèque de base Arduino/ESP32
#include <ESP32Servo.h> // Bibliothèque pour le contrôle des moteurs

// Déclaration des PINs utilisées (voir schéma électrique)
#define POT_BASE_PIN 0
#define POT_SHOULDER_PIN 1
#define POT_ARM_PIN 4
#define SERVO_BASE_PIN 6
#define SERVO_SHOULDER_PIN 7
#define SERVO_ARM_PIN 8


// Définition de l'objet Servo pour la base
Servo BaseServo;
Servo ShoulderServo;
Servo ArmServo;

void setup() {
  // Initialise la communication USB avec l'ordinateur
  Serial.begin(115200);
  delay(1000); // Delai d'une seconde
 
  // Initialise l'entrée (INPUT) pour lire la valeur du potentiomètre
  pinMode(POT_BASE_PIN, INPUT);
  pinMode(POT_SHOULDER_PIN, INPUT);
  pinMode(POT_ARM_PIN, INPUT);
  
  // Initialise le moteur de la pince
  BaseServo.attach(SERVO_BASE_PIN);
  ShoulderServo.attach(SERVO_SHOULDER_PIN);
  ArmServo.attach(SERVO_ARM_PIN);
}

void loop() {
  // Variable de commande moteur
  int pot1_cmd = 0;
  int pot2_cmd = 0;
  int pot3_cmd = 0;
  
  // Lecture de la valeur du capteur
    int pot1Value = analogRead(POT_BASE_PIN);
    int pot2Value = analogRead(POT_SHOULDER_PIN);
    int pot3Value = analogRead(POT_ARM_PIN);

  // Limiter l'action entre 0 et 180 degrés du moteur
  pot1_cmd = map(pot1Value, 0, 4095, 0, 180);
  pot2_cmd = map(pot2Value, 0, 4095, 0, 180);
  pot3_cmd = map(pot3Value, 0, 4095, 0, 180);

  // Afficher les valeurs sur le moniteur série
  Serial.println("Potentiometre1: " + String(pot1Value) + ", Angle: " + String(pot1_cmd));
  Serial.println("Potentiometre2: " + String(pot2Value) + ", Angle: " + String(pot2_cmd));
  Serial.println("Potentiometre3: " + String(pot3Value) + ", Angle: " + String(pot3_cmd));
   
  // Envoie de la commande moteur
  BaseServo.write(pot1_cmd);
  ShoulderServo.write(pot2_cmd);
  ArmServo.write(pot3_cmd);
  delay(50);
}


/*
Mission supplémentaire : Ajoute l'épaule et le coude !

Maintenant que tu as réussi à faire bouger la base, ton objectif est de modifier ce
code pour ajouter 2 autres potentiomètres (POT_EPAULE_PIN sur la broche
1, et POT_COUDE_PIN sur la broche 3). Sers-toi de l’exemple de la base pour
déclarer tes moteurs, les attacher dans le Setup, et lire leurs valeurs dans la Loop !
*/
