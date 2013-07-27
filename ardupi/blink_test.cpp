//Include ArduPi library
#include "arduPi.h"

//Needed for Serial communication
SerialPi Serial;

//Needed for accessing GPIO (pinMode, digitalWrite, digitalRead,I2C functions)
WirePi Wire;

//Needed for SPI
SPIPi SPI;

int main (){
	setup();
	while(1){
		loop();
	}
	return (0);
}

void setup(){
  pinMode(2,OUTPUT); //set pin 2 on the shield as an output
}

//This function will run in an infinite loop
void loop(){
	digitalWrite(2,HIGH); //turn the LED on
	delay(1000); //wait a second
	digitalWrite(2,LOW); // dim the LED
	delay(1000); //wait another second
}
