// This is a bad implementation of set.
// I didn't have time to make it good.
// It works for its purpose, just don't use it anywhere else.

#pragma once

#include <vector>
#include "../int/int.hpp"
#include <ostream>

#define LEFT false
#define RIGHT true

namespace Set
{
    struct IntervalBorder {
        Int::Int value;
		bool closed;

		IntervalBorder();
		IntervalBorder(Int::Int value, bool closed = false);

		virtual bool Side() const = 0;
		virtual bool Contains(const Int::Int& value) const = 0;
    };

	struct LeftIntervalBorder : public IntervalBorder {
		using IntervalBorder::IntervalBorder;

		bool Side() const override;
		bool Contains(const Int::Int& value) const override;
	};

	struct RightIntervalBorder : public IntervalBorder {
		using IntervalBorder::IntervalBorder;

		bool Side() const override;
		bool Contains(const Int::Int& value) const override;
	};

	class Interval {
		friend class Set;

		LeftIntervalBorder left;
		RightIntervalBorder right;
	public:
		Interval(LeftIntervalBorder left, RightIntervalBorder right);
		Interval(Int::Int left, Int::Int right);
		Interval(Int::Int left, bool leftClosed, Int::Int right, bool rightClosed);
		Interval(const Interval& other);

		bool IsEmpty() const;
		bool Contains(Int::Int value) const;
		bool ContainsIntegers() const;
		Interval Intersection(const Interval& other) const;

		friend std::ostream& operator<<(std::ostream& stream, const Interval& interval) {
			stream << (interval.left.closed ? '[' : '(') << interval.left.value << ", " << interval.right.value << (interval.right.closed ? ']' : ')');

			return stream;
		}

		static Interval SingleElement(Int::Int element);
		static Interval Empty();
	};

	class Set {
		std::vector<Interval> intervals;
	public:
		Set();
		Set(std::vector<Interval> intervals);
		Set(const Set& other);

		bool IsEmpty() const;
		bool Contains(Int::Int value) const;
		bool ContainsIntegers() const;
		Set Intersection(const Set& other) const;

		friend std::ostream& operator<<(std::ostream& stream, const Set& set) {
			if(set.intervals.size() == 0) {
				stream << Interval::Empty();
				return stream;
			}

			for(auto interval : set.intervals) {
				stream << interval << " ";
			}
			
			return stream;
		}

		static Set SingleElement(Int::Int element);
		static Set Empty();
		static Set Real();
	};
}