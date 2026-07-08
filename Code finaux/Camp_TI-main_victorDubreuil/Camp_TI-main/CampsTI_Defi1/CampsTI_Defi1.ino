///////////////////////////////////////
//         VICTOR DUBREUIL           //
///////////////////////////////////////




// Ajout des bibliothèques de code nécessaire


#include <Arduino.h>  // Bibliothèque de base Arduino/ESP32
#include <ESP32Servo.h> // Bibliothèque pour le contrôle des moteurs
#include <Wire.h>
#include <Adafruit_BNO055.h>

#define SDA_PIN 20
#define SCL_PIN 21

Adafruit_BNO055 bno(0, 0x28);

#define ECG_PIN 3 // contraction musculaire
#define SERVO_PINCE_PIN 7

// Déclaration des PINs utilisées (voir schéma électrique)
#define POT_BASE_PIN 0
#define SERVO_BASE_PIN 8 

#define POT_EPAULE_PIN 1
#define SERVO_EPAULE_PIN 6

#define POT_COUDE_PIN 4
#define SERVO_COUDE_PIN 10 




// Définition de l'objet Servo pour la base
Servo BaseServo;
Servo EpauleServo;
Servo CoudeServo;
Servo PinceServo;

void setup() {
  // Initialise la communication USB avec l'ordinateur
  Serial.begin(115200);
  delay(1000); // Delai d'une seconde

  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(50000);
  delay(1000);

  bno.begin();
  delay(500);
  bno.setExtCrystalUse(true);
  
 
  // Initialise l'entrée (INPUT) pour lire la valeur du potentiomètre
  

  // Initialise le moteur de la pince
  BaseServo.attach(SERVO_BASE_PIN);

  pinMode(POT_EPAULE_PIN, INPUT);
  EpauleServo.attach(SERVO_EPAULE_PIN);

  pinMode(POT_COUDE_PIN, INPUT);
  CoudeServo.attach(SERVO_COUDE_PIN);

  pinMode(ECG_PIN, INPUT);
  PinceServo.attach(SERVO_PINCE_PIN);

  
}





void loop() {
  
  // Variable de commande moteur
  int pot1_cmd = 0;

  int pot2_cmd = 0;
  int pot3_cmd = 0;
  
  // Lecture de la valeur du capteur
  //int pot1Value = analogRead(POT_BASE_PIN);

  int pot2Value = analogRead(POT_EPAULE_PIN);
  int pot3Value = analogRead(POT_COUDE_PIN);
  
  // Limiter l'action entre 0 et 180 degrés du moteur
  //pot1_cmd = map(pot1Value, 0, 4095, 0, 180);

  pot2_cmd = map(pot2Value, 0, 4095, 0, 180);
  pot3_cmd = map(pot3Value, 0, 4095, 0, 180);

  // Afficher les valeurs sur le moniteur série
  //Serial.println("Potentiometre: " + String(pot1Value) + ", Angle: " + String(pot1_cmd));

  // Envoie de la commande moteur
  //BaseServo.write(pot1_cmd);
  
  EpauleServo.write(pot2_cmd);
  CoudeServo.write(pot3_cmd);



  int ecg_cmd = 100;
  int ecgValue = analogRead(ECG_PIN); 
 
  //Serial.println(String(ecgValue));
  
  if (ecgValue > 3700){
    ecg_cmd = 100;
  }else{
    ecg_cmd = 180;
  }
  
  PinceServo.write(ecg_cmd);



  static uint32_t tImu = 0;
  int base_imu_cmd = 0;
  
  if(millis() - tImu >= 100){
    tImu = millis();

    imu::Quaternion quat = bno.getQuat();
    float angleZ = quat.toEuler().z() / PI * 180.0;

    base_imu_cmd = map(angleZ, -180, 180, 0, 180);
  }
  Serial.println(String(tImu));
  BaseServo.write(base_imu_cmd);
  
  delay(50);
}


/*
Mission supplémentaire : Ajoute l'épaule et le coude !

Maintenant que tu as réussi à faire bouger la base, ton objectif est de modifier ce
code pour ajouter 2 autres potentiomètres (POT_EPAULE_PIN sur la broche
1, et POT_COUDE_PIN sur la broche 3). Sers-toi de l’exemple de la base pour
déclarer tes moteurs, les attacher dans le Setup, et lire leurs valeurs dans la Loop !
*/
