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
			
			throw "FAILURE at LINE " + Mnemonics[mnemonicNo] +
				" " + std::to_string(line.getAddress());
		}
		++PC;
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
    ACC += ram.getAddressData(address).value_or(0);
	return SUCCESS;
}

status Runtime::sub(int address) noexcept
{
    ACC -= ram.getAddressData(address).value_or(0);
	return SUCCESS;
}

status Runtime::sta(int address) noexcept
{
    ram.setAddressData(address, ACC);
	return SUCCESS;
}

status Runtime::lda(int address) noexcept
{
    if(auto op = ram.getAddressData(address)){
        ACC = *op;
        return SUCCESS;
    }
    else return FAILURE;
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
	

