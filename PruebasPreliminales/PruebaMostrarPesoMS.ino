
#include <ESP8266WiFi.h>
#include "HX711.h"

HX711 scale(D5, D6);
float Peso;
float factor_de_calibracion = 10000; // Modificar este valor para cada bascula
 
void setup() {
  Serial.begin(115200); 
  scale.set_scale();
  scale.tare(); //Resetea la escala a 0
  long zero_factor = scale.read_average(); //Aplica un offset a la señal
  delay(2000);
}
 
void loop() {
  scale.set_scale(factor_de_calibracion); //Se ajusta al factor de calibración dado
  Peso = scale.get_units(5); //Hace una media de 5 valores 
  
  Serial.print("Peso: ");
  Serial.print(Peso);
  Serial.println(" KG");
  Serial.println();
}