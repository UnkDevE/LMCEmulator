#include "RAM.h"

int RAM::getAdressData(int address)
{
	return addresses[address];
}

void RAM::setAdressData(int address, int data)
{
	addresses[address] = data;
}
