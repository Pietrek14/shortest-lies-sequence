#include "liesDetector.hpp"
#include "../set/set.hpp"
#include <iostream>
#include <math.h>

Set::Set FromStatement(const LiesDetector::Statement& statement) {
	switch(statement.operand) {
		case LiesDetector::Operand::EQUALS: {
			return Set::Set::SingleElement(statement.number);
		}

		case LiesDetector::Operand::LESS_THAN: {
			std::vector<Set::Interval> intervals;

			intervals.push_back(Set::Interval(-Int::Int::Infinity(), statement.number));

			return Set::Set(intervals);
		}

		case LiesDetector::Operand::MORE_THAN: {
			std::vector<Set::Interval> intervals;

			intervals.push_back(Set::Interval(statement.number, Int::Int::Infinity()));

			return Set::Set(intervals);
		}

		case LiesDetector::Operand::LESS_OR_EQUAL: {
			std::vector<Set::Interval> intervals;

			intervals.push_back(Set::Interval(-Int::Int::Infinity(), false, statement.number, true));

			return Set::Set(intervals);
		}

		case LiesDetector::Operand::MORE_OR_EQUAL: {
			std::vector<Set::Interval> intervals;

			intervals.push_back(Set::Interval(statement.number, true, Int::Int::Infinity(), false));

			return Set::Set(intervals);
		}

		case LiesDetector::Operand::NOT_EQUAL: {
			std::vector<Set::Interval> intervals;

			intervals.push_back(Set::Interval(-Int::Int::Infinity(), statement.number));
			intervals.push_back(Set::Interval(statement.number, Int::Int::Infinity()));

			return Set::Set(intervals);
		}

		default: {
			throw std::runtime_error("Unknown operand!");
		}
	}
}

#ifdef DEBUG
void PrintBinary(unsigned int number) {
	for(int i = 32; i >= 0; i--) {
		std::cout << ((number & (1 << i)) ? "1" : "0");
	}

	std::cout << std::endl;
}
#endif

unsigned int BitArray(unsigned int size, unsigned int offset = 0) {
	unsigned int result = 0;

	for(int i = 0; i < size; i++) {
		result |= 1 << (i + offset);
	}

	return result;
}

unsigned int CountSetBits(unsigned int number)
{
    unsigned int result = 0;

    while (number) {
        result += number & 1;
        number >>= 1;
    }
    return result;
}

int LiesDetector::FindShortestLieSequence(std::vector<Statement> statements) {
    // Make all the statements true
    for(Statement& statement : statements) {
        if(statement.answer)
            continue;
        
        // Change the operand for the opposite
        // E.g. EQUALS turns to NOT_EQUAL
        statement.operand = (Operand)(((int)statement.operand + 3) % 6);

        statement.answer = true;
    }

	// Convert all statements to sets
	std::vector<Set::Set> sets;

	for(Statement statement : statements) {
#ifdef DEBUG
		std::cout << statement << std::endl;
#endif

		sets.push_back(FromStatement(statement));
	}

	// Find the shortest lie sequence
	unsigned int size = 0, offset = 0;

#ifdef DEBUG
	for(int i = 0; i < sets.size(); i++) {
		std::cout << "Statement " << i << ": " << sets[i] << std::endl;
	}
#endif

	while(size <= sets.size()) {
		Set::Set lieSequence = Set::Set::Real();

		const unsigned int array = ~BitArray(size, offset);

		for(int i = 0; i < sets.size(); i++) {
			if(array & (1 << i)) {
				lieSequence = lieSequence.Intersection(sets[i]);
			}
		}

		offset++;

		if(offset + size > sets.size()) {
			size++;
			offset = 0;
		}

#ifdef DEBUG
		PrintBinary(array);
		std::cout << "Result: " << lieSequence << std::endl;
		std::cout << "contains integers: " << lieSequence.ContainsIntegers() << std::endl;
#endif

		if(lieSequence.ContainsIntegers()) {
			break;
		}
	}

	return size;
}