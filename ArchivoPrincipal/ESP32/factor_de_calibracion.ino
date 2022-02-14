#include <HX711.h> 

const byte PIN_DATOS = 2;  //D1 //amarillo
const byte PIN_RELOJ = 27;  //D2 //verde

HX711 hx711(PIN_DATOS,PIN_RELOJ);

//Cambiar el factor de calibración para mi celda de carga
float Factor_De_Calibracion = 945853; // celda negra de 3kg = 945853
float Peso_Conocido = 640.0;
//=============================================================================================
//                         SETUP
//=============================================================================================
void setup() {
  Serial.begin(115200);
  Serial.println("Calibración del HX711");
  Serial.println("Elimine el peso de la escala");
  Serial.println("Cuando empiezen las medidas añada el peso colocido");
  Serial.println("Pulsa A(+10), S(+100), D(+1000), F(+10000) para aumentar el factor de calibración ");
  Serial.println("Pulsa Z(-10), X(-100), C(-1000), V(-10000) para disminuir el factor de calibración");
  Serial.println("Pulsa T para tarar a 0");
  hx711.set_scale();
  hx711.tare(); //Resetea la escala a 0

  long Factor_Cero = hx711.read_average(); //Get a baseline reading
  Serial.print("Factor cero: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(Factor_Cero);
}
//=============================================================================================
//                         LOOP
//=============================================================================================
void loop() {
  hx711.set_scale(Factor_De_Calibracion);// aquí ajustamos el factor de calibración

  Serial.print("Leyendo: ");
  Serial.print(hx711.get_units(), 3);
  Serial.print(" kg"); //Change this to kg and re-adjust the calibration factor if you follow SI units like a sane person
  Serial.print(" Factor de calibración: ");
  Serial.print(Factor_De_Calibracion);
  Serial.println();

  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      Factor_De_Calibracion += 10;
    else if(temp == '-' || temp == 'z')
      Factor_De_Calibracion -= 10;
    else if(temp == 's')
      Factor_De_Calibracion += 100;  
    else if(temp == 'x')
      Factor_De_Calibracion -= 100;  
    else if(temp == 'd')
      Factor_De_Calibracion += 1000;  
    else if(temp == 'c')
      Factor_De_Calibracion -= 1000;
    else if(temp == 'f')
      Factor_De_Calibracion += 10000;  
    else if(temp == 'v')
      Factor_De_Calibracion -= 10000;  
    else if(temp == 't')
      hx711.tare();  //Reset the scale to zero
  }

}
