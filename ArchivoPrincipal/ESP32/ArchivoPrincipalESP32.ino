    /////////////////////////////////////////////////////////////////
   //       ESP32 Deep Sleep Y memoria TTC Prueba v1.00           //
  //                 Víctor Coto Rodríguez                       //
 /////////////////////////////////////////////////////////////////

#define uS_TO_S_FACTOR 1000000  // Factor de conversion de microsegundos a segundos 
#define TIME_TO_SLEEP  10      // Tiempo que va a dormir el ESP32(en segundos) 

#include <HX711.h>
#include <WiFi.h>
#include <ThingSpeak.h>

RTC_DATA_ATTR int Veces_Ejecutado = 0;
////////////////////////////////////////////////////////
//conectarse a wifi y thingspeak
////////////////////////////////////////////////////////
const char* ssid = "Aquaris V_a90243";
const char* password = "123456789";
unsigned long channelID = 1315227;
const char* WriteAPIKey = "ZQK3B4XOCQKZG7TG";

WiFiClient cliente;

////////////////////////////////////////////////////////////////////////
const byte PIN_DATOS = 2;  //D1 //amarillo  OJO LO CAMBIO AL 4
const byte PIN_RELOJ = 27;  //D2 //verde

HX711 hx711(PIN_DATOS,PIN_RELOJ);

//Cambiar el factor de calibración para mi celda de carga
float Factor_De_Calibracion = 945853; // celda negra de 3kg = 945853
float Factor_Cero= 890;
float Peso_Conocido = 640.0;
float Anterior = 0;
float Valor;
float Kilos;
//=============================================================================================
//                         SETUP
//=============================================================================================
void setup() {
  
gpio_hold_dis(GPIO_NUM_27);// desactiva el freezing despues del sueño profundo
pinMode(PIN_RELOJ, OUTPUT);
delay(500);
Serial.begin(9600);  //preparar el puerto serie

long zero_factorx = hx711.read_average(); //Get a baseline reading
hx711.set_offset(Factor_Cero);
Serial.print("zero_factorx: ");
Serial.println(zero_factorx);
hx711.set_scale(Factor_De_Calibracion); //Adjust to this calibration factor

WiFi.begin(ssid, password);

 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.println("Conectandose al WIFI...");
 }
 Serial.println("Conectado a la red WIFI");
 ThingSpeak.begin(cliente);

  Kilos = hx711.get_units(5); 
  Valor = Kilos*1000;

   if(Valor<0)
  {
  Valor = 0;
  }

  Serial.print("Valor: ");
  Serial.print(Kilos);
  Serial.println(" KG");
  Serial.println();

  Serial.print("Valor: ");
  Serial.print(Valor);
  Serial.println(" g");
  Serial.println();

//if((anterior-valor)<=-25 ||(anterior-valor)>=25){
  ThingSpeak.setField (1,Valor);
  ThingSpeak.writeFields(channelID,WriteAPIKey);
  Serial.println("Datos enviados a ThingSpeak");
  Anterior = Valor;
//}
WiFi.disconnect();

Veces_Ejecutado= Veces_Ejecutado+1;
Serial.print("Veces Ejecutado: ");
Serial.println(Veces_Ejecutado);
delay(5000);
//hx711.power_down();  // put the HX711 in sleep mode
digitalWrite(PIN_RELOJ,HIGH);
gpio_hold_en(GPIO_NUM_27);
gpio_deep_sleep_hold_en();
esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
esp_deep_sleep_start();
}

void loop() {

}