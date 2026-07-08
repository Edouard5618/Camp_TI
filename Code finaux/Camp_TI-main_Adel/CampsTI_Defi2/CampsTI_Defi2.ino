// Ajout des bibliothèques de code nécessaire
#include <Arduino.h>
#include <ESP32Servo.h>
// Adel Soltani

// Déclaration des PINs utilisées (voir schéma électrique)
#define ECG_PIN 0

#define POT_PIN_1 5
#define POT_PIN_2 4
#define POT_PIN_3 1

#define SERVO_PIN_1 6             
#define SERVO_PIN_2 7
#define SERVO_PIN_3 8
#define SERVO_PIN_4 10

/* ---------------- À FAIRE ----------------
      Défini l'object servo pour la PINCE
      Voir schéma électrique pour la PIN
--------------------------------------------
*/
Servo Servo_1;
Servo Servo_2;
Servo Servo_3;
Servo Servo_4;

float ecgValue = 0.0;

void setup()
{
    // Initialise la communication USB avec l'ordinateur
    Serial.begin(115200);
    delay(1000);
    

    /* ---------------- À FAIRE ----------------
        Initialise la PIN ECG_PIN comme INPUT et le MOTEUR
    --------------------------------------------
    */
    pinMode(ECG_PIN, INPUT);
    pinMode(POT_PIN_1, INPUT);
    pinMode(POT_PIN_2, INPUT);
    pinMode(POT_PIN_3, INPUT);
    Servo_1.attach(SERVO_PIN_1);
    Servo_2.attach(SERVO_PIN_2);
    Servo_3.attach(SERVO_PIN_3);
    Servo_4.attach(SERVO_PIN_4);
}

void loop()
{

    // Variable de commande moteur
    // int ecg_cmd = 0;

    // Lecture de la valeur du capteur
    ecgValue = 0.8*ecgValue + 0.2*analogRead(ECG_PIN);

    Serial.print("Initial ecgValue: " + String(ecgValue));

    int ecgFLAG = 0;
    // Décision de la pince ouverte ou fermee
    if (2048 > ecgValue)
    {
        ecgFLAG = 1;
    }
    else
    {
        ecgFLAG = 0;
    }

    Serial.println("    Decision de l'action: " + String(ecgFLAG));

    /* ---------------- À FAIRE ----------------
          Envoie la commande ecg_cmd au MOTEUR
    --------------------------------------------
    */
    if (ecgFLAG == 1)
    {
        Servo_4.write(180);
    }
    else
    {
        Servo_4.write(0);
    }

    int pot1_cmd = 0;
    int pot2_cmd = 0;
    int pot3_cmd = 0;

    int pot1Value = analogRead(POT_PIN_1);
    int pot2Value = analogRead(POT_PIN_2);
    int pot3Value = analogRead(POT_PIN_3);

    pot1_cmd = map(pot1Value, 0, 4095, 0, 180);
    pot2_cmd = map(pot2Value, 0, 4095, 0, 180);
    pot3_cmd = map(pot3Value, 0, 4095, 0, 180);

    Serial.println("Potentiometre 1: " + String(pot1Value) + ", Angle: " + String(pot1_cmd));
    Serial.println("Potentiometre 2: " + String(pot2Value) + ", Angle: " + String(pot2_cmd));
    Serial.println("Potentiometre 3: " + String(pot3Value) + ", Angle: " + String(pot3_cmd));

    Servo_1.write(pot1_cmd);
    Servo_2.write(pot2_cmd);
    Servo_3.write(pot3_cmd);
    
    delay(50);
}

/*
Dans ce défi, tu n’as pas tout le code ! Cherche les zones encadrées par 
–- À FAIRE –- et complète les instructions manquantes en t’aidant de ce que tu as appris au
Défi 1. L’objectif est d’utiliser les signaux électrique de tes propres muscles pour contrôler
la pince du robot!
*/
