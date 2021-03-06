
#include <HX711.h>
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
extern "C" {
#include "user_interface.h" // this is for the RTC memory read/write functions
}

//conectarse a wifi y thingspeak
const char* ssid = "V_a90243";//nombre del wifi
const char* password = "123456789"; //contraseña del wifi
unsigned long channelID = *******; //canal de thingspeak
const char* WriteAPIKey = "***********"; //apiKey de thingspeak

WiFiClient cliente;
const byte PIN_VCCHX711= 13; //D7
const byte PIN_DATOS = 5;    //D1 //amarillo
const byte PIN_RELOJ = 4;    //D2 //verde
 
HX711 hx711(PIN_DATOS,PIN_RELOJ);

float valor;
float kilos;
float anterior ;


//float anterior = 0;
float calibration_factor = 947753; // for me this vlaue works just perfect more or less
float zero_factor = 242614; //164019
//float peso_conocido = 640.0;
//=============================================================================================
//                         SETUP
//=============================================================================================

void setup() 
{

  pinMode(PIN_VCCHX711, OUTPUT);

  Serial.begin(9600);  //preparar el puerto serie
  digitalWrite(PIN_VCCHX711, HIGH);
  delay(500);
  long zero_factorx = hx711.read_average(); //Obtener medicion
  hx711.set_offset(zero_factor);
  Serial.print("zero_factorx: ");
  Serial.println(zero_factorx);
  hx711.set_scale(calibration_factor); //Ajustar factor de calibración

 WiFi.begin(ssid, password);

 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.println("Conectandose al WIFI...");
 }
 Serial.println("Conectado a la red WIFI");
 ThingSpeak.begin(cliente);

 
  kilos = hx711.get_units(5); 
  valor = kilos*1000;

  

  if(valor<=5){
    if(valor<=-15){
      ESP.deepSleep(2e6);
    }
  valor = 0;
  }
  system_rtc_mem_read(64, &anterior, 4);


if ((anterior< valor)&&(valor-anterior)>=25){
  float diferencia = valor-anterior;
  ThingSpeak.setField (2,diferencia);
  ThingSpeak.writeFields(channelID,WriteAPIKey);
  Serial.println("añadido agua subido a thingspeak ");
  Serial.println(diferencia);

}


if((anterior-valor)<=-25 ||(anterior-valor)>=25){
  ThingSpeak.setField (1,valor);
  ThingSpeak.writeFields(channelID,WriteAPIKey);
  Serial.println("Datos enviados a ThingSpeak");

}
  anterior = valor;
  system_rtc_mem_write(64, &anterior, 4);
  

ESP.deepSleep(15e6);

}
void loop() {
 
}