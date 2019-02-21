#pragma once
#include <map>
#include <expermental/optional>

class RAM {

public:
    std::optional<int> getAddressData(int address);
	void setAddressData(int address, int data);

private:
	std::map<int, int> addresses;
};
