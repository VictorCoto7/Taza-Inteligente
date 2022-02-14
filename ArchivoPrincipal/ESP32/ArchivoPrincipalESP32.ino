    /////////////////////////////////////////////////////////////////
   //       ESP32 Deep Sleep Y memoria TTC Prueba v1.00           //
  //                 Víctor Coto Rodríguez                       //
 /////////////////////////////////////////////////////////////////

#define uS_TO_S_FACTOR 1000000  /* Conversion de microsegundos a segundos */
#define TIME_TO_SLEEP  10        /* Tiempo en segundos que el microcontrolador va a dormir */
#include <HX711.h>
RTC_DATA_ATTR int Contador = 0; /* Utilizamos la memoria TTR para guardar el número despues del sueño*/

const byte PIN_DATOS = 2;  //amarillo (señal a tratar)
const byte PIN_RELOJ = 27; //verde
int Pin_Azul = 25;         // Azul
int Pin_Rojo = 26;         // Rojo
//========================================================================
//                         SETUP
//========================================================================

void setup(){
gpio_hold_dis(GPIO_NUM_27);// desactiva el freezing despues del sueño profundo
Serial.begin(9600);
  pinMode(Pin_Azul,OUTPUT);
  pinMode(Pin_Rojo,OUTPUT);
  pinMode(PIN_RELOJ, OUTPUT);
  delay(500);
  //////////////////////////////////////////////////////

  if(Contador == 0) //Solo se ejecuta la primera vez
  {
      digitalWrite(Pin_Rojo,HIGH);
      Contador = Contador+1;
  }else
  {
      digitalWrite(Pin_Azul,HIGH);
      Contador = Contador+1;
  }
  delay(10000);
  digitalWrite(Pin_Azul,LOW);
  digitalWrite(Pin_Rojo,LOW);
  digitalWrite(PIN_RELOJ,HIGH);
  
  Serial.println(" ");
  Serial.println("Numerode ciclos: ");
  Serial.println(Contador);
  gpio_hold_en(GPIO_NUM_27);
  gpio_deep_sleep_hold_en();

  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  esp_deep_sleep_start();
}
void loop(){
  
}