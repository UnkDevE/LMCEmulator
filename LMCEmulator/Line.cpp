#include "Line.h"

// converts a line to machine code.
int Line::toMachineCode()
{
	if (Mnemonic != DAT || Mnemonic != UNDEFINED || Mnemonic != INP || Mnemonic != OUT) 
		return stoi(std::to_string(static_cast<int>(Mnemonic)) + std::to_string(address));
	else if (Mnemonic == INP) return 901;
	else if (Mnemonic == OUT) return 902;
	else return address;
}
