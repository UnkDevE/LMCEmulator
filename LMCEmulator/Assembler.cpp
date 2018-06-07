#include "Assembler.h"

RAM Assembler::assembleProgram()
{
	return RAM();
}

// get strings in string seperated by ' '
std::vector<std::string> Assembler::getWords(std::string str)
{
	std::vector<std::string> words{};
	std::string word = "";
	for (auto c : str) {
		if (c != ' ') {
			word += c;
		}
		else {
			words.push_back(word);
			word = "";
		}
	}

	return words;
}

// convert a list of strings to a Line class
Line Assembler::wordsToLine(std::vector<std::string> words)
{
	bool lastWordMnemonic = false;
	mnemonic mnemonic = UNDEFINED;
	std::string label = "";
	int address = 0;

	for (auto word : words) {
		if (mnemonic == UNDEFINED) {
			mnemonic = toMnemonic(word);
		}
		else if (mnemonic == UNDEFINED) {
			label = word;
		}
		else {
			try {
				address = stoi(word);
			}
			catch (std::invalid_argument) {
				if(labels.count(word) > 0) address = labels[word];
			}
		}
	}

	if (label != "") {
		return Line(label, mnemonic, address);
	}
	else {
		return Line(mnemonic, address);
	}
}

// converts String to uppercase
std::string Assembler::toUpper(std::string str)
{
	std::string upperStr = "";

	for (auto c : str) {
		upperStr.push_back(toupper(c));
	}

	return upperStr;
}

//  checks if string is a Mnemonic
mnemonic Assembler::toMnemonic(std::string str)
{
	str = toUpper(str);
	
	for (unsigned i = 0; i < Mnemonics.size(); i++){
		if (str == Mnemonics[i]) return static_cast<mnemonic>(i);
	}

	return UNDEFINED;
}

// populate the class
void Assembler::populateData()
{
	std::string linestr = "";
	while (std::getline(file, linestr)){
		Line line = wordsToLine(getWords(linestr));
		if (line.getLabel() != "") {
			labels[line.getLabel()] = line.getaddress();
		}
		lines.push_back(line);
	}
}
