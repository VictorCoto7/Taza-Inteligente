// Potenciometro conectado a Gpio 35
const int portPin1 = 35;
const int portPin2 = 36;
// Almacenamiento del valor de puerto (rango de 0-4095)
double porValor1 = 0;
double porValor2 = 0;
void setup() {
  Serial.begin(9600);
  delay(500);

}

void loop() {
// Lectura del valor en cada vuelta de bucle
porValor1 = analogRead(portPin1);
porValor2 = analogRead(portPin2);
Serial.print("Este es el valor 1: ");
Serial.println(porValor1 ); // Envio del valor al puerto serie
Serial.print("Este es el valor 2: ");
Serial.println(porValor2 ); // Envio del valor al puerto serie
delay(1000);
}
