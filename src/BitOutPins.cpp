#include "BitOutPins.h"

#define ON HIGH
#define OFF LOW

template <int pinCount>
void BitOutPins<pinCount>::_h() {
	Serial.print("BitOutPins[");
	Serial.print(pinCount);
	Serial.print("] of Id(");
	Serial.print(Id);
	Serial.print("): ");
}

template <int pinCount>
void BitOutPins<pinCount>::WriteN(unsigned char n) {
	if (Verbose) {
		_h();
	}
	for (int a = 0; a < 4; a++) {
		if (Verbose) {
			Serial.print(" \"");
			Serial.print(bitRead(n, a));
			Serial.print("\" to pin");
			Serial.print(pins[a]);
		}
		if (bitRead(n, a) == 0) {
			digitalWrite(pins[a], OFF);
		}
		if (bitRead(n, a) == 1) {
			digitalWrite(pins[a], ON);
		}
	}
}

template <int pinCount>
BitOutPins<pinCount>::BitOutPins(int assignedPins[pinCount], int id){
	Id = id;
	_h();
	Serial.print("Initializing pins: ");
	for (int a = 0; a < pinCount; a++) {
		pins[a] = assignedPins[a];
		pinMode(pins[a], OUTPUT);
		digitalWrite(pins[a], ON);
		Serial.print(pins[a]);
		Serial.print("(");
		Serial.print(assignedPins[a]);
		Serial.print(") ");
	}
	/**/

}

template <int pinCount>
void BitOutPins<pinCount>::Write(bool pinstates[pinCount]) {
	for (int a = 0; a < pinCount; a++) {
		digitalWrite(pins[a], pinstates[a]);
	}
}

template <int pinCount>
void BitOutPins<pinCount>::PrintPins() {
	_h();
	Serial.print("Pins: ");
	for (int a = 0; a < pinCount; a++) {
		Serial.print(pins[a]);
		Serial.print(" ");
	}
}