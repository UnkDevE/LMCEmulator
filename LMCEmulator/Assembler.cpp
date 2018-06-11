#include "Assembler.h"

// assemble the lmc code
RAM Assembler::assembleProgram()
{
	RAM ram = RAM();
	for (unsigned i = 0; i < lines.size(); i++) {
		ram.setAddressData(i, lines[i].toMachineCode());
	}
	return ram;
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
	words.push_back(word);

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
		if (mnemonic == UNDEFINED) {
			label = word;
		}
		else {
			try {
				address = stoi(word);
			}
			catch (std::invalid_argument) {
				if (labels.count(word) > 0) address = labels[word];
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

	for (unsigned i = 0; i < Mnemonics.size(); i++) {
		if (str == Mnemonics[i]) {
			if (i > 8) {
				if (i == 9) return INP;
				if (i == 10) return OUT;
			}
			else if (i > 3) {
				return static_cast<mnemonic>(i + 1);
			}
			else {
				return static_cast<mnemonic>(i);
			}
		}
	}

	return UNDEFINED;
}

// populate the labels map with select lines
void Assembler::populateLabels()
{
	std::string linestr = "";
	for (int lineNum = 0; std::getline(file, linestr); lineNum++) {
		if (getWords(linestr).size() > 2){
			Line line = wordsToLine(getWords(linestr));
			if (line.getMnemonic() == DAT) {
				labels[line.getLabel()] = line.getAddress();
			}
			else {
				labels[line.getLabel()] = lineNum;
			}
			
		}
	}
}

void Assembler::populateLines() {
	std::string linestr = "";
	while (std::getline(file, linestr)) {
		Line line = wordsToLine(getWords(linestr));
		if (line.getMnemonic() != DAT) lines.push_back(line);
	}
}
