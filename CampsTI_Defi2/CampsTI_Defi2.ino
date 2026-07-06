// Ajout des bibliothèques de code nécessaire
#include <Arduino.h>
#include <ESP32Servo.h> 

// Déclaration des PINs utilisées (voir schéma électrique)
#define ECG_PIN 4
#define BTN_PIN 9

/* ---------------- À FAIRE ----------------
      Définie l'object servo pour la PINCE
      Voir schéma électrique pour la PIN
--------------------------------------------
*/


void setup() {
  // Initialise la communication USB avec l'ordinateur
  Serial.begin(115200);
  delay(1000); 

/* ---------------- À FAIRE ----------------
    Initialise la PIN ECG_PIN comme INPUT et le MOTEUR
--------------------------------------------
*/
}

void loop() {
  // Variable entre 2 lectures du capteur
  static int tAdc = 0;

  // Variable de commande moteur
  static int ecg_cmd = 0;

  // Régulation du temps entre 2 lectures / actions
  if (millis() - tAdc >= 50) {
    tAdc = millis(); 

    // Lecture de la valeure du capteur
    int ecgValue =  analogRead(ECG_PIN) > 2048 ? 4095 : 0;
    
    // Décision de l'action
    if(digitalRead(BTN_PIN) == LOW) {
      ecgValue = 4095; // Simuler une valeur maximale pour le signal ECG
    } else {
      ecgValue = 0; // Simuler une valeur minimale pour le signal ECG
    }

    // Limiter l'action entre 50 et 180 degrés du moteur
    ecg_cmd = map(ecgValue, 0, 4095, 50, 180);
  }

/* ---------------- À FAIRE ----------------
      Envoie la commande ecg_cmd au MOTEUR
--------------------------------------------
*/
}
