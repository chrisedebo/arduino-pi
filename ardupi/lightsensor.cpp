//Include ArduPi library
#include "arduPi.h"

//Include the Math library
#include <math.h>

//Needed for Serial communication
SerialPi Serial;

//Needed for accessing GPIO (pinMode, digitalWrite, digitalRead,
//I2C functions)
WirePi Wire;

//Needed for SPI
SPIPi SPI;


#define RESISTOR 20000 //our 20K resistor
#define LDR 20000 // The resistance of LDR

// Number of readings to take
// these will be averaged out to
// get a more accurate reading
// You can increase/decrease this as needed
#define READINGS 7

/*********************************************************
* IF YOUR ARDUINO CODE HAS OTHER FUNCTIONS APART FROM *
* setup() AND loop() YOU MUST DECLARE THEM HERE *
* *******************************************************/

/**************************
* YOUR ARDUINO CODE HERE *
* ************************/

int main (){
	setup();
	while(1){
		loop();
	}
	return (0);
}

void setup(void) {
	printf("Starting up lightsensor \n");
	Wire.begin();
}

void loop(void) {
	float avResistance;
	float resistance;
	int combinedReadings[READINGS];
	byte val0;
	byte val1;

	// Our temperature variables

	int channelReading;
	float analogReadingArduino;

	/*******************
	ADC mappings
	Pin Address
	0 0xDC
	1 0x9C
	2 0xCC
	3 0x8C
	4 0xAC
	5 0xEC
	6 0xBC
	7 0xFC
	*******************/
	
	// 0x9C is our analog 1 pin
	Wire.beginTransmission(8);
	Wire.write(byte(0xDC));
	Wire.endTransmission();

	/* Grab the two bytes returned from the
	analog 1 pin, combine them
	and write the value to the
	combinedReadings array
	*/

	for(int r=0; r<READINGS; r++){
		Wire.requestFrom(8,2);
		val0 = Wire.read();
		val1 = Wire.read();
		channelReading = int(val0)*16 + int(val1>>4);
		printf("channelReading=%f",channelReading);
		analogReadingArduino = channelReading * 1023 /4095;
		combinedReadings[r] = analogReadingArduino;
		delay(100); }

	// Grab the average of our 7 readings
	// in order to get a more accurate value
	avResistance = 0;
	for (int r=0; r<READINGS; r++) {
		avResistance += combinedReadings[r];
	}
	avResistance /= READINGS;

	/* We can now calculate the resistance of
	the readings that have come back from analog 0
	*/
	avResistance = (1023 / avResistance) - 1;
	avResistance = RESISTOR / avResistance;
	resistance = avResistance / LDR;
	
	printf("resistance=%f",resistance);
	// Three second delay before taking our next
	// reading
	delay(3000);
}

