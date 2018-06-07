#pragma once
#include <map>

class RAM {

public:
	int getAdressData(int address);
	void setAdressData(int address, int data);

private:
	std::map<int, int> addresses;
};