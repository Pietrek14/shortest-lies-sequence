#include "int.hpp"
#include <stdexcept>

// Minus infinity is represented with value -1 and infinite set to true.

bool Int::Int::IsInfinite() const
{
	return infinite;
}

/// @returns 1 if the value is infinity, -1 if it's negative infinity, 0 otherwise.
int Int::Int::GetInfinity() const
{
	if(infinite)
		return value;

	return 0;
}

int Int::Int::GetValue() const
{
	return value;
}

Int::Int::Int() {
	value = 0;
	infinite = false;
}

Int::Int::Int(int value) {
	this->value = value;
	this->infinite = false;
}

Int::Int::Int(const Int& other) {
	this->value = other.value;
	this->infinite = other.infinite;
}

Int::Int& Int::Int::operator+=(const Int& other) {
	if (infinite || other.infinite) {
		infinite = true;
	}
	else {
		value += other.value;
	}

	return *this;
}

Int::Int& Int::Int::operator-=(const Int& other) {
	if (infinite || other.infinite) {
		infinite = true;
	}
	else {
		value -= other.value;
	}

	return *this;
}

Int::Int& Int::Int::operator*=(const Int& other) {
	if(other.value == 0) {
		value = 0;
		infinite = false;

		return *this;
	}

	if (infinite || other.infinite) {
		if(other.value < 0) {
			value *= -1;
		}

		infinite = true;
	}
	else {
		value *= other.value;
	}

	return *this;
}

Int::Int& Int::Int::operator/=(const Int& other) {
	if(other.value == 0) {
		throw std::runtime_error("Division by zero");
	}

	if (infinite || other.infinite) {
		if(other.value < 0) {
			value *= -1;
		}

		infinite = true;
	}
	else {
		value /= other.value;
	}

	return *this;
}

Int::Int& Int::Int::operator%=(const Int& other) {
	if (infinite || other.infinite) {
		if(other.value < 0) {
			value *= -1;
		}

		infinite = true;
	}
	else {
		value %= other.value;
	}

	return *this;
}

Int::Int& Int::Int::operator++() {
	if (!infinite) {
		value++;
	}

	return *this;
}

Int::Int& Int::Int::operator--() {
	if (!infinite) {
		value--;
	}

	return *this;
}

Int::Int Int::Int::operator++(int) {
	Int result = *this;

	if (!infinite) {
		value++;
	}

	return result;
}

Int::Int Int::Int::operator--(int) {
	Int result = *this;

	if (!infinite) {
		value--;
	}

	return result;
}

Int::Int Int::Int::operator-() const {
	Int result = *this;

	result.value *= -1;

	return result;
}

Int::Int Int::Int::operator+(const Int& other) const {
	Int result = *this;

	if (infinite || other.infinite) {
		result.infinite = true;
	}
	else {
		result.value += other.value;
	}

	return result;
}

Int::Int Int::Int::operator-(const Int& other) const {
	Int result = *this;

	if (infinite || other.infinite) {
		result.infinite = true;
	}
	else {
		result.value -= other.value;
	}

	return result;
}

Int::Int Int::Int::operator*(const Int& other) const {
	Int result = *this;

	if (infinite || other.infinite) {
		if(other.value < 0) {
			result.value *= -1;
		}

		result.infinite = true;
	}
	else {
		result.value *= other.value;
	}

	return result;
}

Int::Int Int::Int::operator/(const Int& other) const {
	Int result = *this;

	if(other.value == 0) {
		throw std::runtime_error("Division by zero!");
	}

	if (infinite || other.infinite) {
		if(other.value < 0) {
			result.value *= -1;
		}

		result.infinite = true;
	}
	else {
		result.value /= other.value;
	}

	return result;
}

Int::Int Int::Int::operator%(const Int& other) const {
	Int result = *this;

	if(other.value == 0) {
		throw std::runtime_error("Division by zero!");
	}

	if (infinite || other.infinite) {
		if(other.value < 0) {
			result.value *= -1;
		}

		result.infinite = true;
	}
	else {
		result.value %= other.value;
	}

	return result;
}

bool Int::Int::operator==(const Int& other) const {
	if (infinite || other.infinite) {
		return infinite == other.infinite && value == other.value;
	}

	return value == other.value;
}

bool Int::Int::operator!=(const Int& other) const {
	if (infinite || other.infinite) {
		return infinite != other.infinite || value != other.value;
	}

	return value != other.value;
}

bool Int::Int::operator<(const Int& other) const {
	if (infinite || other.infinite) {
		return GetInfinity() < other.GetInfinity();
	}

	return value < other.value;
}

bool Int::Int::operator>(const Int& other) const {
	if (infinite || other.infinite) {
		return GetInfinity() > other.GetInfinity();
	}

	return value > other.value;
}

bool Int::Int::operator<=(const Int& other) const {
	if (infinite || other.infinite) {
		return GetInfinity() <= other.GetInfinity();
	}

	return value <= other.value;
}

bool Int::Int::operator>=(const Int& other) const {
	if (infinite || other.infinite) {
		return GetInfinity() >= other.GetInfinity();
	}

	return value >= other.value;
}

Int::Int& Int::Int::operator+=(int other) {
	if(infinite)
		return *this;

	value += other;

	return *this;
}

Int::Int& Int::Int::operator-=(int other) {
	if(infinite)
		return *this;

	value -= other;

	return *this;
}

Int::Int& Int::Int::operator*=(int other) {
	if(other == 0) {
		value = 0;
		infinite = false;

		return *this;
	}

	if(infinite) {
		if(other < 0) {
			value *= -1;
		}

		return *this;
	}

	value *= other;

	return *this;
}

Int::Int& Int::Int::operator/=(int other) {
	if(other == 0) {
		throw std::runtime_error("Division by zero");
	}

	if(infinite) {
		if(other < 0) {
			value *= -1;
		}

		return *this;
	}

	value /= other;

	return *this;
}

Int::Int& Int::Int::operator%=(int other) {
	if(other == 0) {
		throw std::runtime_error("Division by zero");
	}

	if(infinite) {
		if(other < 0) {
			value *= -1;
		}

		return *this;
	}

	value %= other;

	return *this;
}

Int::Int Int::Int::operator+(int other) const {
	Int result = *this;

	if(!infinite) {
		result.value += other;
	}

	return result;
}

Int::Int Int::Int::operator-(int other) const {
	Int result = *this;

	if(!infinite) {
		result.value -= other;
	}

	return result;
}

Int::Int Int::Int::operator*(int other) const {
	Int result = *this;

	if(other == 0) {
		result.value = 0;
		result.infinite = false;

		return result;
	}

	if(infinite) {
		if(other < 0) {
			result.value *= -1;
		}

		return result;
	}

	result.value *= other;

	return result;
}

Int::Int Int::Int::operator/(int other) const {
	Int result = *this;

	if(other == 0) {
		throw std::runtime_error("Division by zero!");
	}

	if(infinite) {
		if(other < 0) {
			result.value *= -1;
		}

		return result;
	}

	result.value /= other;

	return result;
}

Int::Int Int::Int::operator%(int other) const {
	Int result = *this;

	if(other == 0) {
		throw std::runtime_error("Division by zero!");
	}

	if(infinite) {
		if(other < 0) {
			result.value *= -1;
		}

		return result;
	}

	result.value %= other;

	return result;
}

bool Int::Int::operator==(int other) const {
	if(infinite) {
		return false;
	}

	return value == other;
}

bool Int::Int::operator!=(int other) const {
	if(infinite) {
		return true;
	}

	return value != other;
}

bool Int::Int::operator<(int other) const {
	if(infinite) {
		return value > 0;
	}

	return value < other;
}

bool Int::Int::operator>(int other) const {
	if(infinite) {
		return value < 0;
	}

	return value > other;
}

bool Int::Int::operator<=(int other) const {
	if(infinite) {
		return value > 0;
	}

	return value <= other;
}

bool Int::Int::operator>=(int other) const {
	if(infinite) {
		return value < 0;
	}

	return value >= other;
}

Int::Int Int::Int::Infinity() {
	Int result;
	result.value = 1;
	result.infinite = true;

	return result;
}