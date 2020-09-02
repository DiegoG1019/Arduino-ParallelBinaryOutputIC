#include "Bit4OutPins.h"

#define ON HIGH
#define OFF LOW

void Bit4OutPins::_h() {
	Serial.print("Bit4OutPins of Id(");
	Serial.print(Id);
	Serial.print("): ");
}

Bit4OutPins::Bit4OutPins(int PinA, int PinB, int PinC, int PinD, int id) {
	Id = id;
	pinA = PinA;
	pinB = PinB;
	pinC = PinC;
	pinD = PinD;
	int _[4] = { pinA, pinB, pinC, pinD };
	_h();
	Serial.print("Initializing pins: ");
	for (int a = 0; a < 4; a++) {
		pins[a] = _[a];
		pinMode(pins[a], OUTPUT);
		digitalWrite(pins[a], ON);
		Serial.print(pins[a]);
		Serial.print("(");
		Serial.print(_[a]);
		Serial.print(") ");
	}
	/**/

}

void Bit4OutPins::PrintPins() {
	_h();
	Serial.print("Pins: ");
	for (int a = 0; a < 4; a++) {
		Serial.print(pins[a]);
		Serial.print(" ");
	}
}

void Bit4OutPins::Write16(unsigned char n) {
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

void Bit4OutPins::Write(bool A, bool B, bool C, bool D) {
	digitalWrite(pinA, A);
	digitalWrite(pinB, B);
	digitalWrite(pinC, C);
	digitalWrite(pinD, D);
}

