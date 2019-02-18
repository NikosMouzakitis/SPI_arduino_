#include <SPI.h>
char buff [10];
volatile byte indx;
volatile boolean process;
int counter;
int rec;
char *v;
int pinLED = A0;

void setup() {
  Serial.begin (115200);
  pinMode(MISO, OUTPUT); // have to send on master in so it set as output
  pinMode(pinLED, OUTPUT);
  SPCR |= _BV(SPE); // turn on SPI in slave mode
  indx = 0; // buffer empty
  process = false;
  SPI.attachInterrupt(); // turn on interrupt
  counter = 0;
  Serial.println("Initialized");
  analogWrite(pinLED, 0);
}

ISR (SPI_STC_vect) {// SPI interrupt routine 
  //Serial.println("interrupt");
  char c = SPDR; // read byte from SPI Data Register
 
  v = (char *) &rec;
    
  if (indx < sizeof buff) {
    buff [indx++] = c; // save data in the next index in the array buff
    counter++;
    process = true;
  }
}

void loop(){
 
  if (process) {
    //Serial.println("SPI reception ");
    process = false; //reset the process
    if(counter == 2) {
      *(v) = buff[0];
      *(v+1) = buff[1];
      counter = 0;
      Serial.print("Received: ");
      Serial.println(rec); //print the array on serial monitor
      analogWrite(pinLED, rec);
      indx= 0; //reset button to zero
    }
  }
 
}
