#pragma once
#include <string>

enum mnemonic { HLT = 0, ADD = 1, SUB = 2, STA = 3, 
		LDA = 5, BRA = 6, BRZ = 7, BRP = 8, DAT = 9, UNDEFINED};

class Line {
public:
	Line(std::string Label, mnemonic mnemonic, int Address) :
		label(Label), Mnemonic(mnemonic), address(Address) {}

	// set label to something so when get func 
	// is called it won't return undefined.
	Line(mnemonic mnemonic, int Address) :
		Mnemonic(mnemonic), address(Address), label("") {}

	~Line() {}

	Line(int machineCode) {
		auto machineStr = std::to_string(machineCode);
		Mnemonic = static_cast<mnemonic>(static_cast<int>(machineStr[0] - '0'));
		address = stoi(machineStr.substr(machineStr.size() - 1));
	}

	int toMachineCode();
	std::string getLabel() { return label; }
	mnemonic getMnemonic() { return Mnemonic; }
	int getaddress() { return address; }

private:
	
	std::string label;
	mnemonic Mnemonic;
	int address;
};