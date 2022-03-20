#pragma once

#include <istream>
#include <ostream>
#include <string>

namespace Int {
	class Int {
		int value;
		bool infinite;
	public:
		bool IsInfinite() const;
		int GetInfinity() const;
		int GetValue() const;

		Int();
		Int(int value);
		Int(const Int& other);

		Int& operator+=(const Int& other);
		Int& operator-=(const Int& other);
		Int& operator*=(const Int& other);
		Int& operator/=(const Int& other);
		Int& operator%=(const Int& other);
		Int& operator++();
		Int& operator--();
		Int operator++(int);
		Int operator--(int);
		Int operator-() const;	// negative
		Int operator+(const Int& other) const;
		Int operator-(const Int& other) const;
		Int operator*(const Int& other) const;
		Int operator/(const Int& other) const;
		Int operator%(const Int& other) const;
		bool operator==(const Int& other) const;
		bool operator!=(const Int& other) const;
		bool operator<(const Int& other) const;
		bool operator>(const Int& other) const;
		bool operator<=(const Int& other) const;
		bool operator>=(const Int& other) const;

		Int& operator+=(int other);
		Int& operator-=(int other);
		Int& operator*=(int other);
		Int& operator/=(int other);
		Int& operator%=(int other);
		Int operator+(int other) const;
		Int operator-(int other) const;
		Int operator*(int other) const;
		Int operator/(int other) const;
		Int operator%(int other) const;
		bool operator==(int other) const;
		bool operator!=(int other) const;
		bool operator<(int other) const;
		bool operator>(int other) const;
		bool operator<=(int other) const;
		bool operator>=(int other) const;

		friend std::istream& operator>>(std::istream& stream, Int &value) {
			std::string str;
			stream >> str;

			if(str == "inf") {
				value = Infinity();
			} else if(str == "-inf") {
				value = -Infinity();
			} else {
				value.infinite = false;
				value.value = std::stoi(str);
			}

			return stream;
		}

		friend std::ostream& operator<<(std::ostream& stream, const Int& value) {
			if(value.infinite) {
				if(value.value < 0)
					stream << "-";

				stream << "inf";
			} else {
				stream << value.value;
			}

			return stream;
		}

		static Int Infinity();
	};
}