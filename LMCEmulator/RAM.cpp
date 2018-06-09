#include "RAM.h"

int RAM::getAddressData(int address)
{
	return addresses[address];
}

void RAM::setAddressData(int address, int data)
{
	addresses[address] = data;
}
