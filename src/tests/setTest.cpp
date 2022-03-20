#include <iostream>
#include <vector>
#include "../set/set.hpp"

// I can't into unit tests :(

int main() {
	Set::Set set = Set::Set(std::vector<Set::Interval>{ 
		Set::Interval(1, 3),
	});

	if(set.ContainsIntegers())
		std::cout << set << " contains integers" << std::endl;
	else
		std::cout << set << " doesn't contain integers" << std::endl;

	return 0;
}