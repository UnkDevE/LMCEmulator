#pragma once
#include <iostream>
#include "RAM.h"
#include "Line.h"
#include "Assembler.h"

enum status { SUCCESS, FAILURE };

class Runtime {
public:
	Runtime(RAM Ram) :
		ram(Ram), PC(0), ACC(0) 
		{}

	status run();
	
private:
	status runMnemonic(mnemonic Mnemonic, int data);
	status add(int address) noexcept;
	status sub(int address) noexcept;
	status sta(int address) noexcept;
	status lda(int address) noexcept;
	status bra(int address) noexcept;
	status brz(int address) noexcept;
	status brp(int address) noexcept;
	status inp() noexcept;
	status out() noexcept;
	
	int ACC;
	int PC;
	RAM ram;
};