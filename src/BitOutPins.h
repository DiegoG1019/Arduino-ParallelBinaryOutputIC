#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

template <int pinCount>
class BitOutPins
{
protected:
	int PinCount = pinCount;
	int pins[pinCount] = { 0 };
	int Id;
	void _h();
public:
	bool Verbose = false;
	void PrintPins();
	void WriteN(unsigned char n);
	void Write(bool pinstates[pinCount]);
	BitOutPins(int assignedPins[pinCount], int id);
};

template class BitOutPins<4>;