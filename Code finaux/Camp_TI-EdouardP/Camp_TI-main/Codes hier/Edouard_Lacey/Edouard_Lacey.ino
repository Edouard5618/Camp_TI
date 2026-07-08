// Édouard Lacey

#include <Arduino.h>  
#include <ESP32Servo.h> 

                                                                                                                                                                                     
#define POT_Pivot_PIN 1
#define POT_BASE_PIN 0
#define SERVO_BASE_PIN 8
#define SERVO_Pivot_PIN 10


Servo BaseServo;
Servo PivotServo;

void setup() {

  Serial.begin(115200);
  delay(1000); 
 

  pinMode(POT_BASE_PIN, INPUT);
  pinMode(POT_Pivot_PIN, INPUT);
  
  BaseServo.attach(SERVO_BASE_PIN);
  PivotServo.attach(SERVO_Pivot_PIN);
}

void loop() {
 
  int pot1_cmd = 0;
  int pot2_cmd = 0;
  
 
  int pot1Value = analogRead(POT_BASE_PIN);
  int pot2Value = analogRead(POT_Pivot_PIN);
  
  pot1_cmd = map(pot1Value, 0, 4095, 0, 180);
  pot2_cmd = map(pot2Value, 0, 4095, 0, 180);

  Serial.println("Potentiometre: " + String(pot1Value) + ", Angle: " + String(pot1_cmd));
  Serial.println("Potentiometre: " + String(pot2Value) + ", Angle: " + String(pot2_cmd));

  BaseServo.write(pot1_cmd);
  PivotServo.write(pot2_cmd);
  delay(50);
}


/*
Mission supplémentaire : Ajoute l'épaule et le coude !

Maintenant que tu as réussi à faire bouger la base, ton objectif est de modifier ce
code pour ajouter 2 autres potentiomètres (POT_EPAULE_PIN sur la broche
1, et POT_COUDE_PIN sur la broche 3). Sers-toi de l’exemple de la base pour
déclarer tes moteurs, les attacher dans le Setup, et lire leurs valeurs dans la Loop !
*/
