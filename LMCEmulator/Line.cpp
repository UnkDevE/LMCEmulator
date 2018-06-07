#include "Line.h"

// converts a line to machine code.
int Line::toMachineCode()
{
	if (Mnemonic != DAT || Mnemonic != UNDEFINED) 
		return stoi(std::to_string(static_cast<int>(Mnemonic)) + std::to_string(address));
	else return address;
}
