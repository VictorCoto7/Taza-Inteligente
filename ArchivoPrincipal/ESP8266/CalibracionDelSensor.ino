#include <HX711.h> 
const byte PIN_DATOS = 5;  //D1 //amarillo
const byte PIN_RELOJ = 4;  //D2 //verde
 
HX711 hx711(PIN_DATOS,PIN_RELOJ);
float factor_de_calibracion = 1030853; //Valor a variar 
float peso_conocido = 658.0;
//=============================================================================================
//                         SETUP
//=============================================================================================
void setup() {
  Serial.begin(9600);
  delay(5000);
  Serial.println("Proceso de calibracion del moduloHx711");
  Serial.println("No coloque ningun peso todavia");
  Serial.println("Por favor, retire todo el peso de la taza");
  Serial.println("Presione: (a=+10),(s=+100),(d=+1000),(f=+10000) ");
  Serial.println("Presione: (z=-10),(x=-100),(c=-1000),(v=-10000) ");
  hx711.set_scale();
  hx711.tare(); //Reset the scale to 0
  long zero_factor = hx711.read_average(); //Desviacion del cero
  Serial.print("Zero factor: "); //Apuntarlo para añadir al nuevo programa
  Serial.println(zero_factor);
  Serial.println("Ya puede colocar el peso conocido");
}
 
//=============================================================================================
//                         LOOP
//=============================================================================================
void loop() {
 
  hx711.set_scale(factor_de_calibracion); 
 
  Serial.print("Peso: ");
  Serial.print(hx711.get_units(), 3);
  Serial.print(" kg"); 
  Serial.print(" factor_de_calibracion: ");
  Serial.print(factor_de_calibracion);
  Serial.println();
 
  if(Serial.available())
  {
    char var = Serial.read();
    if(var == '+' || var == 'a')
      factor_de_calibracion += 10;
    else if(var == '-' || var == 'z')
      factor_de_calibracion -= 10;
    else if(var == 's')
      factor_de_calibracion += 100;  
    else if(var == 'x')
      factor_de_calibracion -= 100;  
    else if(var == 'd')
      factor_de_calibracion += 1000;  
    else if(var == 'c')
      factor_de_calibracion -= 1000;
    else if(var == 'f')
      factor_de_calibracion += 10000;  
    else if(var == 'v')
      factor_de_calibracion -= 10000;  
  }
}