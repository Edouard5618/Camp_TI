// Ajout des bibliothèques de code nécessaire
#include <Arduino.h>
#include <ESP32Servo.h>

// Déclaration des PINs utilisées (voir schéma électrique)
#define ECG_PIN 3
#define SERVO_PINCE_PIN 10

Servo PinceServo;

void setup()
{
    // Initialise la communication USB avec l'ordinateur
    Serial.begin(115200);
    delay(1000);

    pinMode(ECG_PIN, INPUT);
    PinceServo.attach(SERVO_PINCE_PIN);
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

    ecg_cmd = map(ecgValue, 0, 1, 0, 180);
    PinceServo.write(ecg_cmd);

    delay(50);
}


// C'est normal que juste la pince bouge avec ce code. Si tu veux ajouter les potentiomètres pour les autres servos, tu peux aller voir CampsTI_Corrige_Final
