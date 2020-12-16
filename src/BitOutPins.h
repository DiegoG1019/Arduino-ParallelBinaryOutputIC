#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#define ON HIGH
#define OFF LOW

class BitOutBase
{
protected:
	static int Count;
	BitOutBase(){};
};

template <int pinCount>
class BitOutPins : BitOutBase
{
protected:
	int pins[pinCount] = { 0 };
	int Id;
	void _h()
	{
		Serial.print("\nBitOutPins[");
		Serial.print(pinCount);
		Serial.print("] of Id(");
		Serial.print(Id);
		Serial.print("): ");
	};
public:
	bool Verbose = false;
	void PrintPins() {
		_h();
		Serial.print("Pins: ");
		for (int a = 0; a < pinCount; a++) {
			Serial.print(pins[a]);
			Serial.print(" ");
		}
	}
	void WriteN(unsigned char n) {
		if (Verbose) {
			_h();
		}
		for (int a = 0; a < pinCount; a++) {
			if (Verbose) {
				Serial.print(" \"");
				Serial.print(bitRead(n, a));
				Serial.print("\" to pin");
				Serial.print(pins[a]);
			}
			digitalWrite(pins[a], (n&(B10000000>>a)) ? ON : OFF);
		}
	}
	void Write(bool pinstates[pinCount]) {
		for (int a = 0; a < pinCount; a++) {
			digitalWrite(pins[a], pinstates[a]);
		}
	}
	BitOutPins(int assignedPins[pinCount]) {
		Id = Count;
		Count++;
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
};