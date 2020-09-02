/*
 Name:		ParallelBinaryPinOutput.h
 Created:	8/30/2020 10:43:37 PM
 Author:	Diego Garcia
 Editor:	http://www.visualmicro.com
*/

#ifndef _ParallelBinaryPinOutput_h
#define _ParallelBinaryPinOutput_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#endif

#define MAXDISPLAYS 6
#define DELAYTIME 100

#include "../Bit4OutPins.h"

class Driver_74LS47
{
private:
	Bit4OutPins* displays[MAXDISPLAYS];
	unsigned char DisplayCount;
	unsigned int MaxNumber;
	bool overcount;
	void _h();
	bool verbose = false;
	unsigned int id;
public:
	unsigned char DisplayedDigits[MAXDISPLAYS];
	Driver_74LS47(unsigned char display, unsigned int startpin);
	void PrintAllPins();
	void CalcOutput(unsigned int value);
	void Write();
	void OutputDisplay(unsigned int value);
	bool IsOverCounting(); //Is it attempting to display a number higher than what it can
	void All0();
	void OutputAll0();
	void TestSequence();
	void TestSequence(unsigned int ms);
	void LampTest();
	void FullSequence();
	void FullSequence(unsigned int ms);
	bool IsVerbose();
	void Verbosity(bool v);
};
