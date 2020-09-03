# Driver_74LS47
## Syntax
```C++
#define MAXDISPLAYS 2
#define DELAYTIME 100
Driver_74LS47(unsigned char displays, unsigned int* pins);
Driver_74LS47(unsigned char displays, unsigned int startpin);
```
Where `unsigned int* pins` is an array holding the pins to claim for the object. The array should be the size of the amount of displays times four (`displays * 4`)

Where `unsigned int startpin` is the pin from which to start claiming one by one in ascending order i.e. `startpin =2` & `displays = 2` would equal `pins[2*4] = {2,3,4,5 , 6,7,8,9};`

## Class members
```C++
unsigned char DisplayedDigits[MAXDISPLAYS];
```
The array where individual digit for each individual display is stored. Can be modified directly, however the output will only show upon a `Write();` call
```C++
void PrintAllPins();
```
Prints all used pins through `Serial.print();` specifically, it calls `PrintPins()` on each of the internal `BitOutPins<4>` objects
```C++
void CalcOutput(unsigned int value);
```
Separates the given number into digits and stores them to `DisplayedDigits[MAXDISPLAYS]`
```C++
void OutputDisplay(unsigned int value);
```
Combines both `CalcOutput(unsigned int value);` and `Write();` in a single call
```C++
bool IsOverCounting();
```
Returns a boolean value signaling whether or not the last outputted number was capped at the display's maximum displayable value
```C++
void All0();
```
Sets all indexes in `DisplayedDigits[MAXDISPLAYS]` to 0
```
void OutputAll0();
```
Combines `All0();` and `Write();` in a single call
```C++
void TestSequence(unsigned int ms = DELAYTIME);
```
Runs each display through all of their possible displayable values individually, with ms defining the delay between each value being shown. Defaults to `DELAYTIME`
```C++
void LampTest();
```
Prints the number 8 (all segments) on all available displays
```C++
void FullSequence(unsigned int ms = DELAYTIME);
```
Runs every number between 0 and MaxNumber+1 sequentially, with ms defining the delay between each value being shown. Defaults to `DELAYTIME`
```C++
bool IsVerbose();
```
Returns whether verbosity is active
```C++
void Verbosity(bool v);
```
Sets the verbosity for the object. Specficially, sequentially runs through all internal BitOutPins objects to enable or disable their verbosity.