#include "Runtime.h"

// runs the program
status Runtime::run()
{
	for (bool hlt = false; !hlt;) {
		Line line(ram.getAddressData(PC));
		if (line.getMnemonic() == HLT) hlt = true;
		if(runMnemonic(line.getMnemonic(), line.getAddress()) == FAILURE){
			unsigned mnemonicNo = static_cast<unsigned>(line.getMnemonic());
			if (static_cast<int>(line.getMnemonic()) > 4) --mnemonicNo;
			
			throw "FAIURE at LINE " + Mnemonics[mnemonicNo] +
				" " + std::to_string(line.getAddress());
		}
	}

	return SUCCESS;
}

// runs the specified mnemonic
status Runtime::runMnemonic(mnemonic Mnemonic, int data)
{
	switch (Mnemonic) {
	case ADD:
		return add(data);
	case SUB:
		return sub(data);
	case STA:
		return sta(data);
	case LDA:
		return lda(data);
	case BRA:
		return bra(data);
	case BRZ:
		return brz(data);
	case BRP:
		return brp(data);
	case INP:
		return inp();
	case OUT:
		return out();
	default:
		return FAILURE;
	}
}

status Runtime::add(int address) noexcept
{
	try {
		ACC += ram.getAddressData(address);
	}
	catch (std::exception e) {
		return FAILURE;
	}
	return SUCCESS;
}

status Runtime::sub(int address) noexcept
{
	try{
		ACC -= ram.getAddressData(address);
	}
	catch (std::exception e) {
		return FAILURE;
	}
	return SUCCESS;
}

status Runtime::sta(int address) noexcept
{
	try{
		ram.setAddressData(address, ACC);
	}
	catch (std::exception e) {
		return FAILURE;
	}
	return SUCCESS;
}

status Runtime::lda(int address) noexcept
{
	try{
		ACC = ram.getAddressData(address);
	}
	catch (std::exception e) {
		return FAILURE;
	}
	return SUCCESS;
}

status Runtime::bra(int address) noexcept
{
	PC = address;
	return SUCCESS;
}

status Runtime::brz(int address) noexcept
{
	if (ACC == 0) {
		PC = address;
	}
	return SUCCESS;
}

status Runtime::brp(int address) noexcept
{
	if (ACC >= 0) {
		PC = address;
	}
	return SUCCESS;
}

status Runtime::inp() noexcept
{
	try {
		std::cin >> ACC;
	}
	catch (std::exception e) {
		return FAILURE;
	}
	return SUCCESS;
}

status Runtime::out() noexcept
{
	try{
		std::cout << ACC << std::endl;
	}
	catch (std::exception e) {
		return FAILURE;
	}
	return SUCCESS;
}
	

