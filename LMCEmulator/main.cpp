#include "Runtime.h"

int main(int argc, char ** argv)
{

	if (argc < 2) {
		std::cout << "no file given to emulate lmc code." << std::endl;
	}
	else {
		Assembler* assembler = new Assembler(std::string(argv[1]));
		Runtime runtime(assembler->assembleProgram());

		try {
			runtime.run();
		}
		catch (std::exception e) {
			std::cout << e.what() << std::endl;
		}
	}
}