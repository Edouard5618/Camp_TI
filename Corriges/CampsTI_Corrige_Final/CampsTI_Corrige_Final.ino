// Ajout des bibliothèques de code nécessaire
#include <Arduino.h>
#include <ESP32Servo.h>
#include <Wire.h>            // Bibliothèque de communication avec le IMU
#include <Adafruit_BNO055.h> // Bibliothèque du IMU

// Déclaration des PINs utilisées (voir schéma électrique)
#define POT_EPAULE_PIN 0
#define POT_COUDE_PIN 1
#define ECG_PIN 3
#define SERVO_BASE_PIN 6
#define SERVO_EPAULE_PIN 7
#define SERVO_COUDE_PIN 8
#define SERVO_PINCE_PIN 10

// PINs de communication I2C
#define SDA_PIN 20
#define SCL_PIN 21

// Déclaration du capteur IMU
Adafruit_BNO055 bno(0, 0x28);

// Déclaration des moteurs
Servo BaseServo;
Servo EpauleServo;
Servo CoudeServo;
Servo PinceServo;

void setup()
{
    Serial.begin(115200);
    delay(1000);

    // Initialisation de la communication avec le IMU
    Wire.begin(SDA_PIN, SCL_PIN);
    Wire.setClock(50000);
    delay(1000);

    // Démarer le capteur IMU
    bno.begin();
    delay(500);
    bno.setExtCrystalUse(true);

    // Initialisation des entrées et des moteurs
    pinMode(POT_EPAULE_PIN, INPUT);
    pinMode(POT_COUDE_PIN, INPUT);
    pinMode(ECG_PIN, INPUT);

    BaseServo.attach(SERVO_BASE_PIN);
    EpauleServo.attach(SERVO_EPAULE_PIN);
    CoudeServo.attach(SERVO_COUDE_PIN);
    PinceServo.attach(SERVO_PINCE_PIN);
}

void loop()
{
    static uint32_t tImu = 0;
    int base_imu_cmd = 0;

    // Régulation du temps pour le IMU
    if (millis() - tImu >= 100)
    {
        tImu = millis();

        // Lecture de l'angle
        imu::Quaternion quat = bno.getQuat();
        float angleZ = quat.toEuler().z() / PI * 180.0;

        // Assignation de la commande
        base_imu_cmd = map(angleZ, -180, 180, 0, 180);

        Serial.print("Angle Z: " + String(angleZ));
        Serial.println(", base_imu_cmd: " + String(base_imu_cmd));

        BaseServo.write(base_imu_cmd);
    }

    // Contrôle de l'épaule avec le potentiomètre 1
    int potEpauleValue = analogRead(POT_EPAULE_PIN);
    int potEpauleCmd = map(potEpauleValue, 0, 4095, 0, 180);
    Serial.println("Potentiometre epaule: " + String(potEpauleValue) + ", Angle: " + String(potEpauleCmd));
    EpauleServo.write(potEpauleCmd);

    // Contrôle du coude avec le potentiomètre 2
    int potCoudeValue = analogRead(POT_COUDE_PIN);
    int potCoudeCmd = map(potCoudeValue, 0, 4095, 0, 180);
    Serial.println("Potentiometre coude: " + String(potCoudeValue) + ", Angle: " + String(potCoudeCmd));
    CoudeServo.write(potCoudeCmd);

    // Contrôle de la pince avec l'EMG
    int ecgValue = analogRead(ECG_PIN);
    int ecgCmd = 0;

    Serial.print("Initial ecgValue: " + String(ecgValue));

    if (ecgValue > 2048)
    {
        ecgValue = 1;
    }
    else
    {
        ecgValue = 0;
    }

    Serial.println("    Decision de l'action: " + String(ecgValue));

    ecgCmd = map(ecgValue, 0, 1, 0, 180);
    PinceServo.write(ecgCmd);

    delay(50);
}
