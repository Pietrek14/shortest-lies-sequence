#include <iostream>
#include <fstream>
#include "liesDetector/liesDetector.hpp"

int main(int argc, char const *argv[]) {
    if(argc != 2) {
        std::cout << "I expect 1 argument, " << (argc - 1) << " given!" << std::endl;
        return 1;
    }

	std::ifstream inputFile(argv[1]);

	if(!inputFile.is_open()) {
		std::cout << "Could not open file: " << argv[1] << std::endl;
		return 1;
	}

	int statementsCount;

	inputFile >> statementsCount;

	std::vector<LiesDetector::Statement> statements;

	for(int i = 0; i < statementsCount; i++) {
		LiesDetector::Statement statement;
		char operand;

		inputFile >> operand;

		switch(operand) {
			case '=': {
				statement.operand = LiesDetector::Operand::EQUALS;
				break;
			}

			case '<': {
				statement.operand = LiesDetector::Operand::LESS_THAN;
				break;
			}

			case '>': {
				statement.operand = LiesDetector::Operand::MORE_THAN;
				break;
			}

			default: {
				std::cout << "Unknown operand: " << operand << std::endl;
				return 1;
			}
		}

		inputFile >> statement.number;

		std::string answer;

		inputFile >> answer;

		if(answer == "yes") {
			statement.answer = true;
		} else if(answer == "no") {
			statement.answer = false;
		} else {
			std::cout << "Unknown answer: " << answer << std::endl;
			return 1;
		}

		statements.push_back(statement);
	}

	std::cout << "Shortest lie sequence length: " << LiesDetector::FindShortestLieSequence(statements) << std::endl;

    return 0;
}