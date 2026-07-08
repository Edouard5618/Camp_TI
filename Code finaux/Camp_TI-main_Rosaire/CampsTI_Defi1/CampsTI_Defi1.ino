// Rosaire
// Ajout des bibliothèques de code nécessaire
#include <Arduino.h>  // Bibliothèque de base Arduino/ESP32
#include <ESP32Servo.h> // Bibliothèque pour le contrôle des moteurs

// Déclaration des PINs utilisées (voir schéma électrique)
#define POT_BASE_PIN 0
#define POT_Epaule_PIN 1
#define SERVO_BASE_PIN 6
#define POT_3_PIN 4
#define SERVO_2 7
#define SERVO_3 8
#define SERVO_4

// Définition de l'objet Servo pour la base
Servo BaseServo;
Servo Servo2;
Servo Servo3;

void setup() {
  // Initialise la communication USB avec l'ordinateur
  Serial.begin(115200);
  delay(1000); // Delai d'une seconde
 
  // Initialise l'entrée (INPUT) pour lire la valeur du potentiomètre
  pinMode(POT_BASE_PIN, INPUT);
  pinMode(POT_Epaule_PIN, INPUT);
  pinMode(POT_3_PIN, INPUT);
  
  // Initialise le moteur de la pince
  BaseServo.attach(SERVO_BASE_PIN);
  Servo2.attach(SERVO_2);
  Servo3.attach(SERVO_3);
}

void loop() {
  // Variable de commande moteur
  int pot1_cmd = 0;
  int pot2_cmd = 0;
  int pot3_cmd = 0;
  
  // Lecture de la valeur du capteur
  int pot1Value = analogRead(POT_BASE_PIN);
  int pot2Value= analogRead(POT_Epaule_PIN);
  int pot3Value= analogRead(POT_3_PIN);
  // Limiter l'action entre 0 et 180 degrés du moteur
  pot1_cmd = map(pot1Value, 0, 4095, 0, 180);
  pot2_cmd = map(pot2Value, 0, 4095, 0,180);
  pot3_cmd = map(pot3Value, 0, 4095, 0,180);

  // Afficher les valeurs sur le moniteur série
  Serial.println("Potentiometre: " + String(pot1Value) + ", Angle: " + String(pot1_cmd));
  Serial.println("Potentiometre: " + String(pot1Value) + ", Angle: " + String(pot1_cmd));
  
  // Envoie de la commande moteur
  BaseServo.write(pot1_cmd);
  Servo2.write(pot2_cmd);
  Servo3.write(pot3_cmd);
  delay(50);
}


/*
Mission supplémentaire : Ajoute l'épaule et le coude !

Maintenant que tu as réussi à faire bouger la base, ton objectif est de modifier ce
code pour ajouter 2 autres potentiomètres (POT_EPAULE_PIN sur la broche
1, et POT_COUDE_PIN sur la broche 3). Sers-toi de l’exemple de la base pour
déclarer tes moteurs, les attacher dans le Setup, et lire leurs valeurs dans la Loop !
*/
