// Ajout des bibliothèques de code nécessaire --------BENJAMIN ROY-------------
#include <Arduino.h>
#include <ESP32Servo.h>

// Déclaration des PINs utilisées (voir schéma électrique)
#define ECG_PIN 3
#define PINCE_PIN 8

Servo PinceServo;


void setup()
{
    // Initialise la communication USB avec l'ordinateur
    Serial.begin(115200);
    delay(1000);

    

    PinceServo.attach(PINCE_PIN);
}

void loop()
{

    // Variable de commande moteur
    int ecg_cmd = 0;

    // Lecture de la valeur du capteur
    static int ecgValue = 0;
    int ecgstate = analogRead(ECG_PIN);

    Serial.print("Initial ecgValue: " + String(ecgstate));

    // Décision de la pince ouverte ou fermee
    if (ecgstate > 3000)
    {
        if (ecgValue == 0)
        {
          ecgValue = 1;
        }
        else
        {
          ecgValue = 0;
        }
    }
    Serial.println("    Decision de l'action: " + String(ecgValue));

    if (ecgValue > 0)
    {
      PinceServo.write(90);
    }
    else
    {
      PinceServo.write(0);
    }
    delay(1000);

}
/*
Dans ce défi, tu n’as pas tout le code ! Cherche les zones encadrées par 
–- À FAIRE –- et complète les instructions manquantes en t’aidant de ce que tu as appris au
Défi 1. L’objectif est d’utiliser les signaux électrique de tes propres muscles pour contrôler
la pince du robot!
*/
