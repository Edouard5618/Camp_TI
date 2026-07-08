// Ajout des bibliothèques de code nécessaire
#include <Arduino.h>  // Bibliothèque de base Arduino/ESP32
#include <ESP32Servo.h> // Bibliothèque pour le contrôle des moteurs

// Déclaration des PINs utilisées (voir schéma électrique)
#define POT_Coude_PIN 4
#define POT_Base_PIN 1
#define POT_Epaule_PIN 0
#define SERVO_Base_PIN 6
#define SERVO_Epaule_PIN 7 
#define SERVO_Coude_PIN 8

// Définition de l'objet Servo pour la base
Servo BaseServo;
Servo EpauleServo;
Servo CoudeServo;

void setup() {
  // Initialise la communication USB avec l'ordinateur
  Serial.begin(115200);
  delay(1000); // Delai d'une seconde
 
  // Initialise l'entrée (INPUT) pour lire la valeur du potentiomètre
  pinMode(POT_Epaule_PIN, INPUT);
 
    // Initialise l'entrée (INPUT) pour lire la valeur du potentiomètre
  pinMode(POT_Base_PIN, INPUT);
  
  // Initialise l'entrée (INPUT) pour lire la valeur du potentiomètre
  pinMode(POT_Coude_PIN, INPUT); 
  
  // Initialise le moteur de la pince
  BaseServo.attach(SERVO_Base_PIN);

 // Initialise le moteur de la pince
  EpauleServo.attach(SERVO_Epaule_PIN);

 // Initialise le moteur de la pince
  CoudeServo.attach(SERVO_Coude_PIN);
  }

void loop() {
  // Variable de commande moteur
  int pot1_cmd = 0;
  
  // Lecture de la valeur du capteur
  int pot1Value = analogRead(POT_Epaule_PIN);
  
  // Limiter l'action entre 0 et 180 degrés du moteur
  pot1_cmd = map(pot1Value, 0, 4095, 0, 180);

  // Afficher les valeurs sur le moniteur série
  Serial.println("Potentiometre: " + String(pot1Value) + ", Angle: " + String(pot1_cmd));

  // Envoie de la commande moteur
  EpauleServo.write(pot1_cmd);
  delay(50);


  // Variable de commande moteur
  int pot2_cmd = 0;
  
  // Lecture de la valeur du capteur
  int pot2Value = analogRead(POT_Base_PIN);
  
  // Limiter l'action entre 0 et 180 degrés du moteur
  pot2_cmd = map(pot2Value, 0, 4095, 0, 180);

  // Afficher les valeurs sur le moniteur série
  Serial.println("Potentiometre: " + String(pot2Value) + ", Angle: " + String(pot2_cmd));

  // Envoie de la commande moteur
  BaseServo.write(pot2_cmd);
  delay(50);
  
  // Variable de commande moteur
  int pot3_cmd = 0;
  
  // Lecture de la valeur du capteur
  int pot3Value = analogRead(POT_Coude_PIN);
  
  // Limiter l'action entre 0 et 180 degrés du moteur
  pot3_cmd = map(pot3Value, 0, 4095, 0, 180);

  // Afficher les valeurs sur le moniteur série
  Serial.println("Potentiometre: " + String(pot3Value) + ", Angle: " + String(pot3_cmd));

  // Envoie de la commande moteur
  CoudeServo.write(pot3_cmd);
  delay(50);
}
/*
Mission supplémentaire : Ajoute l'épaule et le coude !

Maintenant que tu as réussi à faire bouger la base, ton objectif est de modifier ce
code pour ajouter 2 autres potentiomètres (POT_EPAULE_PIN sur la broche
1, et POT_COUDE_PIN sur la broche 3). Sers-toi de l’exemple de la base pour
déclarer tes moteurs, les attacher dans le Setup, et lire leurs valeurs dans la Loop !
*/
