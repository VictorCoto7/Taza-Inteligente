void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.setTimeout(2000);

//wait for serial to initialize
while(!Serial){}

//deep sleep mode for 30 seconds, the esp8266 wake up by itself when gpio (d0) is conectec to RESET pin
Serial.println(" ");
Serial.println("5 segundos");
ESP.deepSleep(5e6);
}

void loop() {
  // put your main code here, to run repeatedly:

}