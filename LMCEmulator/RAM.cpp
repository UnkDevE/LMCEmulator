#include "RAM.h"

std::optional<int> RAM::getAddressData(int address)
{
    if (addressess.find(address) != addressess.end())
        return addresses[address];
    return {};
}

void RAM::setAddressData(int address, int data)
{
	addresses[address] = data;
}
