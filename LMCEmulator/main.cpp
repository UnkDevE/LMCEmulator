#include "Runtime.h"

int main(int argc, char ** argv)
{
	if (argc < 2) {
		std::cout << "please give a file containing LMC code to run" << std::endl;
	}
	else {
		Assembler assembler = Assembler(std::string(argv[1]));
		Runtime runtime(assembler.assembleProgram());

		try {
			runtime.run();
		}
		catch (std::exception e) {
			std::cout << e.what() << std::endl;
		}
	}
}