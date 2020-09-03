/*
 Name:		ParallelBinaryPinOutput.cpp
 Created:	8/30/2020 10:43:37 PM
 Author:	Diego Garcia
 Editor:	http://www.visualmicro.com
*/

#include "Driver_74LS47.h"

void Driver_74LS47::_init(unsigned char displays, unsigned int* pins) {
	static int Instances = 0;
	id = Instances;
	Instances++;
	overcount = false;
	DisplayCount = displays;
	MaxNumber = pow(10, displays) - 1;
	for (int a = 0; a < MAXDISPLAYS; a++) {
		DisplayedDigits[a] = 0;
	}
	_h();
	if (displays > MAXDISPLAYS) {
		Serial.println("ERROR: display number surpasses Maximum Displays allowed. Check the library's source code \"Driver_74LS47.h\"@line19");
		return;
	}
	Serial.println("Initializing driver object with: ");
	for (int ind = 0; ind < displays; ind++) {
		int pinsForBitOut[4];
		int offset = ind * 4;
		for (int pinIndex = 0; pinIndex < 4; pinIndex++) {
			pinsForBitOut[pinIndex] = pins[offset + pinIndex];
		}
		Serial.print("	");
		this->displays[ind] = new BitOutPins<4>(pinsForBitOut, ind);
		Serial.print("	Display: ");
		Serial.print(ind);
		Serial.print(" w/ pins: ");
		for (int alpha = 0; alpha < 4; alpha++) {
			Serial.print(" ");
			Serial.print(pins[alpha]);
		}
		Serial.println();
	}
}

Driver_74LS47::Driver_74LS47(unsigned char displays, unsigned int* pins) {
	_init(displays, pins);
}

Driver_74LS47::Driver_74LS47(unsigned char displays, unsigned int startpin) {
	unsigned int* pinarray = new int[displays * 4];
	for (int ind = 0; ind < displays; ind++) {
		int arrayoffset = ind * 4;
		int pinselect = arrayoffset + startpin;
		for (int arrayselector = 0; arrayselector < 4; arrayselector++) {
			pinarray[arrayoffset + arrayselector] = pinselect + arrayselector;
		}
	}
	_init(displays, pinarray);
}

void Driver_74LS47::CalcOutput(unsigned int value) {

	if (verbose) {
		_h();
		Serial.print("Received number: ");
		Serial.print(value);
	}
	overcount = false;
	if (value > MaxNumber) {
		value = MaxNumber;
		overcount = true;
	}

	if (verbose) {
		Serial.print(" / Calculated output digits: ");
	}
	for (int ind = 0; value != 0; ind++) {
		DisplayedDigits[ind] = (value % 10);
		value /= 10;
		if (verbose) {
			Serial.print(DisplayedDigits[ind]);
			Serial.print(" ");
		}
	}
	if (verbose) {
		Serial.println();
	}
}

void Driver_74LS47::Write() {

	if (verbose) {
		_h();
		Serial.println("Writing digits: ");
	}
	for (int a = 0; a < DisplayCount; a++) {
		if (verbose) {
			Serial.print("	Display ");
			Serial.print(a);
			Serial.print(" Binary: ");
		}
		displays[a]->WriteN(DisplayedDigits[a]);
		if (verbose) {
			Serial.println();
		}
	}
}

void Driver_74LS47::OutputDisplay(unsigned int value) {
	CalcOutput(value);
	Write();
	All0();
}

bool Driver_74LS47::IsOverCounting() {
	if (verbose) {
		_h();
		Serial.print("Overcounting? ");
		Serial.println(overcount > 0 ? "true" : "false");
	}
	return overcount;
}

void Driver_74LS47::All0() {
	for (int a = 0; a < MAXDISPLAYS; a++) {
		DisplayedDigits[a] = 0;
	}
	if (verbose) {
		_h();
		Serial.println("0'ing out all digits");
	}
}

void Driver_74LS47::OutputAll0() {
	All0();
	Write();
}

void Driver_74LS47::_h() {
	Serial.print("Driver_74LS47(");
	Serial.print(id);
	Serial.print("): ");
}

void Driver_74LS47::PrintAllPins() {
	_h();
	Serial.println("Printing all pins: ");
	for (int a = 0; a < DisplayCount; a++) {
		Serial.print("	");
		displays[a]->PrintPins();
		Serial.println();
	}
}

void Driver_74LS47::TestSequence(unsigned int ms = DELAYTIME) {
	_h();
	Serial.println("Executing TestSequence for all displays");
	for (int a = 0; a < DisplayCount; a++) {
		for (int b = 0; b < 16; b++) {
			Serial.print("	>");
			displays[a]->WriteN(b);
			Serial.println();
			delay(ms);
		}
	}
}

void Driver_74LS47::LampTest() {
	_h();
	Serial.println("Executing lamptest for all displays");
	for (int a = 0; a < DisplayCount; a++) {
		Serial.print("	>");
		displays[a]->WriteN(8);
		Serial.println();
	}
}

void Driver_74LS47::FullSequence(unsigned int ms = DELAYTIME) {
	_h();
	Serial.print("Executing a full sequence. This may take a few seconds. MaxNumber = ");
	Serial.print(MaxNumber);
	Serial.print(" | range(0-");
	Serial.print(MaxNumber+1);
	Serial.println(")");
	for (int a = 0; a <= MaxNumber+1; a++) {
		if (verbose) {
			Serial.println("***");
		}
		OutputDisplay(a);
		delay(ms);
	}
	if (verbose) {
		Serial.println("***");
	}
}

bool Driver_74LS47::IsVerbose() {
	return verbose;
}

void Driver_74LS47::Verbosity(bool v) {
	verbose = v;
	for (int a = 0; a < DisplayCount; a++) {
		displays[a]->Verbose = v;
	}
}