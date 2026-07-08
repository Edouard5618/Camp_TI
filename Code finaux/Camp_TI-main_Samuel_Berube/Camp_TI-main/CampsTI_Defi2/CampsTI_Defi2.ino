
// SAMUEL_BÉRUBÉ


// Ajout des bibliothèques de code nécessaire
#include <Arduino.h>
#include <ESP32Servo.h>

// Déclaration des PINs utilisées (voir schéma électrique)
#define ECG_CLAW_PIN 3
#define SERVO_CLAW_PIN 10

Servo ClawServo;


void setup()
{
    // Initialise la communication USB avec l'ordinateur
    Serial.begin(115200);
    delay(1000);

    pinMode(ECG_CLAW_PIN, INPUT);

    ClawServo.attach(SERVO_CLAW_PIN);
    int ecg_cmd = 0;
}

void loop()
{
    int ecg_cmd = 0;
    // Variable de commande moteur


    // Lecture de la valeur du capteur
    int ecgValue = analogRead(ECG_CLAW_PIN);

    Serial.print("Initial ecgValue: " + String(ecgValue));

    // Décision de la pince ouverte ou fermee
    if (ecgValue > 3000)
    {
        ecg_cmd = 180;
    }
    else
    {
        ecg_cmd = 0;
    }

    Serial.println("    Decision de l'action: " + String(ecgValue));

    ClawServo.write(ecg_cmd);

    delay(50);
}

/*
Dans ce défi, tu n’as pas tout le code ! Cherche les zones encadrées par 
–- À FAIRE –- et complète les instructions manquantes en t’aidant de ce que tu as appris au
Défi 1. L’objectif est d’utiliser les signaux électrique de tes propres muscles pour contrôler
la pince du robot!
*/
