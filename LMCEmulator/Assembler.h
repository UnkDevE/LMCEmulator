#pragma once
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <cctype>
#include "RAM.h"
#include "Line.h"

class Assembler {
public:
	Assembler(std::string filename) {
		file.open(filename, std::ios::in);
	}

	RAM assembleProgram();

private:
	std::vector<std::string> getWords(std::string str);
	Line wordsToLine(std::vector<std::string> words);
	mnemonic toMnemonic(std::string str);
	void populateData();

	std::vector<Line> lines;
	std::string toUpper(std::string str);
	std::ifstream file;
	std::map<std::string, int> labels;
	const std::vector<std::string> Mnemonics = std::vector<std::string>{
		"HLT",
		"ADD",
		"SUB",
		"STA",
		"LDA",
		"BRA",
		"BRZ",
		"BRP",
		"DAT"
	};
};