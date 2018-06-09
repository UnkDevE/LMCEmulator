#pragma once
#include <map>

class RAM {

public:
	int getAddressData(int address);
	void setAddressData(int address, int data);

private:
	std::map<int, int> addresses;
};