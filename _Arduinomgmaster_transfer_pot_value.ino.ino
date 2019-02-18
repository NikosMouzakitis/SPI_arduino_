#include <SPI.h>

int pinPot = A0;
int transmission_light = 7;
int val;
void setup() {
  pinMode(pinPot, INPUT);
  
  pinMode(transmission_light, OUTPUT);
  Serial.begin(115200); //set baud rate to 115200 for usart
  digitalWrite(SS, HIGH); // disable Slave Select
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);//divide the clock by 8
  Serial.println("Master node controlled by the potentiometer");
}

void loop() {
 
  char *c;
  c = (char*)&val;
  val = analogRead(pinPot);
  Serial.print("Transmission: ");
  Serial.println(val);
  digitalWrite(transmission_light, HIGH);
  digitalWrite(SS, LOW); // enable Slave Select
  SPI.transfer (*c);
  delay(60);
  digitalWrite(transmission_light, LOW);
  SPI.transfer (*(c+1));
  digitalWrite(SS, HIGH); // disable Slave Select
  delay(1000); //delay between each transmission.
  
}
