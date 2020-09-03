# BitOutPins<int pinCount>
## Syntax
```C++
template<int pinCount>
BitOutPins(int assignedPins[pinCount], int id);
```
## Class members
```C++
bool Verbose = false;
```
Defines whether or not the object should output all of its behaviour through Serial.print()
```C++
void PrintPins();
```
Outputs all of the pins used by the object through Serial.print()
```C++
void WriteN(unsigned char n);
```
Outputs the defined char in serial binary format
```C++
void Write(bool pinstates[pinCount]);
```
Manually writes to each of the pins