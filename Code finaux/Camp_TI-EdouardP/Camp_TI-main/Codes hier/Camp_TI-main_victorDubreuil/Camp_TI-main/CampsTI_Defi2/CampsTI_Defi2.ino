// Ajout des bibliothèques de code nécessaire
#include <Arduino.h>
#include <ESP32Servo.h>

// Déclaration des PINs utilisées (voir schéma électrique)
#define ECG_PIN 4

/* ---------------- À FAIRE ----------------
      Défini l'object servo pour la PINCE
      Voir schéma électrique pour la PIN
--------------------------------------------
*/

void setup()
{
    // Initialise la communication USB avec l'ordinateur
    Serial.begin(115200);
    delay(1000);

    /* ---------------- À FAIRE ----------------
        Initialise la PIN ECG_PIN comme INPUT et le MOTEUR
    --------------------------------------------
    */
}

void loop()
{

    // Variable de commande moteur
    int ecg_cmd = 0;

    // Lecture de la valeur du capteur
    int ecgValue = analogRead(ECG_PIN);

    Serial.print("Initial ecgValue: " + String(ecgValue));

    // Décision de la pince ouverte ou fermee
    if (ecgValue > 2048)
    {
        ecgValue = 1;
    }
    else
    {
        ecgValue = 0;
    }

    Serial.println("    Decision de l'action: " + String(ecgValue));

    /* ---------------- À FAIRE ----------------
          Envoie la commande ecg_cmd au MOTEUR
    --------------------------------------------
    */

    delay(50);
}

/*
Dans ce défi, tu n’as pas tout le code ! Cherche les zones encadrées par 
–- À FAIRE –- et complète les instructions manquantes en t’aidant de ce que tu as appris au
Défi 1. L’objectif est d’utiliser les signaux électrique de tes propres muscles pour contrôler
la pince du robot!
*/
