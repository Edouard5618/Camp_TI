// charlotte
#include <Arduino.h>  // Bibliothèque de base Arduino/ESP32
#include <ESP32Servo.h> // Bibliothèque pour le contrôle des moteurs

// Déclaration des PINs utilisées (voir schéma électrique)
#define POT_BASE_PIN 0
#define POT_SHOULDER_PIN 1
#define POT_ELBOW_PIN 4
#define SERVO_BASE_PIN 6
#define SERVO_SHOULDER_PIN 7
#define SERVO_ELBOW_PIN 8
#define SERVO_PINCE_PIN 10
#define SERVO_2 
#define SERVO_3
#define SERVO_4

// Définition de l'objet Servo pour la base
Servo BaseServo;
Servo ShoulderServo;
Servo ElbowServo;
Servo PinceServo;

void setup() {
  // Initialise la communication USB avec l'ordinateur
  Serial.begin(115200);
  delay(1000); // Delai d'une seconde
 
  // Initialise l'entrée (INPUT) pour lire la valeur du potentiomètre
  pinMode(POT_BASE_PIN, INPUT);
  pinMode (POT_SHOULDER_PIN, INPUT);
  pinMode (POT_ELBOW_PIN, INPUT);
  pinMode (POT_PINCE_PIN, INPUT);
  
  // Initialise le moteur de la pince
  BaseServo.attach(SERVO_BASE_PIN);
  ShoulderServo.attach(SERVO_SHOULDER_PIN);
  ElbowServo.attach(SERVO_ELBOW_PIN);
  PinceServo.attach(SERVO_PINCE_PIN);
}

void loop() {
  // Variable de commande moteur
  int pot1_cmd = 0;
  int pot2_cmd = 1;
  int pot3_cmd = 2; 
  int pot4_cmd = 3;
  
  // Lecture de la valeur du capteur
  int pot1Value = analogRead(POT_BASE_PIN);
  int pot2Value = analogRead(POT_SHOULDER_PIN);
  int pot3Value = analogRead(POT_ELBOW_PIN);
  int pot4Value = analogRead(POT_PINCE_PIN);
  
  // Limiter l'action entre 0 et 180 degrés du moteur
  pot1_cmd = map(pot1Value, 0, 4095, 0, 180);
  pot2_cmd = map(pot2Value, 0, 4095, 0, 180);
  pot3_cmd = map(pot3Value, 0, 4095, 0, 180); 
  pot4_cmd = map(pot4Value, 0, 4095, 0, 180); 
  // Afficher les valeurs sur le moniteur série
  Serial.println("Potentiometre: " + String(pot1Value) + ", Angle: " + String(pot1_cmd));
  Serial.println("Potentiometre: " + String(pot2Value) + ", Angle: " + String(pot2_cmd));
  Serial.println("Potentiometre: " + String(pot3Value) + ", Angle: " + String(pot3_cmd));
  Serial.println("Potentiometre: " + String(pot4Value) + ", Angle: " + String(pot4_cmd));
  // Envoie de la commande moteur
  BaseServo.write(pot1_cmd);
  ShoulderServo.write(pot2_cmd);
  ElbowServo.write(pot3_cmd);
  PinceServo.write(pot4_cmd);
  delay(50);
}


/*
Mission supplémentaire : Ajoute l'épaule et le coude !

Maintenant que tu as réussi à faire bouger la base, ton objectif est de modifier ce
code pour ajouter 2 autres potentiomètres (POT_EPAULE_PIN sur la broche
1, et POT_COUDE_PIN sur la broche 3). Sers-toi de l’exemple de la base pour
déclarer tes moteurs, les attacher dans le Setup, et lire leurs valeurs dans la Loop !
*/
