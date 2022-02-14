



#include <HX711.h>
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

//conectarse a wifi y thingspeak
const char* ssid = "V_a90243";//nombre del wifi
const char* password = "123456789"; //contraseña del wifi
unsigned long channelID = *******; //canal de thingspeak
const char* WriteAPIKey = "***********"; //apiKey de thingspeak

WiFiClient cliente;

const byte PIN_DATOS = 5;  //D1 //amarillo
const byte PIN_RELOJ = 4;  //D2 //verde
 
HX711 hx711(PIN_DATOS,PIN_RELOJ);
float valor;
float kilos;
float anterior = 0;
float calibration_factor = 1030853; 
float zero_factor = 154619;
//float peso_conocido = 658.0;
//=============================================================================================
//                         SETUP
//=============================================================================================

void setup() 
{





  Serial.begin(9600);  //preparar el puerto serie

  long zero_factorx = hx711.read_average(); //Get a baseline reading
  hx711.set_offset(zero_factor);
  Serial.print("zero_factorx: ");
  Serial.println(zero_factorx);
  hx711.set_scale(calibration_factor); //Adjust to this calibration factor


 WiFi.begin(ssid, password);

 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.println("Conectandose al WIFI...");
 }
 Serial.println("Conectado a la red WIFI");
 ThingSpeak.begin(cliente);

 
  kilos = hx711.get_units(5); 
  valor = kilos*1000;

  if(valor<0)
  {
  valor = 0;
  }
  Serial.print("Valor: ");
  Serial.print(kilos);
  Serial.println(" KG");
  Serial.println();

  Serial.print("Valor: ");
  Serial.print(valor);
  Serial.println(" g");
  Serial.println();
  
//if((anterior-valor)<=-25 ||(anterior-valor)>=25){
  ThingSpeak.setField (1,valor);
  ThingSpeak.writeFields(channelID,WriteAPIKey);
  Serial.println("Datos enviados a ThingSpeak");
  anterior = valor;
  delay(14000);
//}


ESP.deepSleep(15e6);

}
 
void loop() 
{
 
}