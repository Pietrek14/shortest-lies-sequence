#pragma once

#include <vector>
#include <ostream>

namespace LiesDetector {
    enum class Operand {
        EQUALS,
        LESS_THAN,
        MORE_THAN,
        NOT_EQUAL,
        MORE_OR_EQUAL,
        LESS_OR_EQUAL
    };

    struct Statement {
        Operand operand;
        int number;
        // Odpowiedz Jasia
        bool answer;

		friend std::ostream& operator<<(std::ostream& stream, const Statement& statement) {
			stream << "x ";

			switch(statement.operand) {
				case Operand::EQUALS: {
					stream << "=";
					break;
				}

				case Operand::LESS_THAN: {
					stream << "<";
					break;
				}

				case Operand::MORE_THAN: {
					stream << ">";
					break;
				}

				case Operand::NOT_EQUAL: {
					stream << "!=";
					break;
				}

				case Operand::MORE_OR_EQUAL: {
					stream << ">=";
					break;
				}

				case Operand::LESS_OR_EQUAL: {
					stream << "<=";
					break;
				}
			}

			stream << " " << statement.number;

			if(statement.answer) {
				stream << " (yes)";
			} else {
				stream << " (no)";
			}

			return stream;
		}
    };

    /// @returns The length of the sequence.
    int FindShortestLieSequence(std::vector<Statement> statements);
}