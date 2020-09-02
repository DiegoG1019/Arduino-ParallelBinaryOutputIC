#pragma once

class Bit4OutPins
{
private:
	int pinA, pinB, pinC, pinD;
	int pins[4] = { 0 };
	int Id;
	void _h();
public:
	bool Verbose = false;
	void PrintPins();
	void Write16(unsigned char n);
	void Write(bool A, bool B, bool C, bool D);
	Bit4OutPins(int pinA, int pinB, int pinC, int pinD, int id);
};


