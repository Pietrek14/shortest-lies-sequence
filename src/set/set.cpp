#include "set.hpp"
#include <algorithm>
#include <iostream>

Set::IntervalBorder::IntervalBorder() : value(0), closed(false) {}

Set::IntervalBorder::IntervalBorder(Int::Int value, bool closed)
{
	this->value = value;
	this->closed = closed;
}

bool Set::LeftIntervalBorder::Side() const
{
	return LEFT;
}

bool Set::LeftIntervalBorder::Contains(const Int::Int& value) const
{
	if(closed)
		return this->value <= value;

	return this->value < value;
}

bool Set::RightIntervalBorder::Side() const
{
	return LEFT;
}

bool Set::RightIntervalBorder::Contains(const Int::Int& value) const
{
	if(closed)
		return this->value >= value;

	return this->value > value;
}

Set::Interval::Interval(LeftIntervalBorder left, RightIntervalBorder right) {
	if(left.value > right.value || (left.value == right.value && !(left.closed && right.closed))) {
		*this = Interval::Empty();
		return;
	}

	this->left = left;
	this->right = right;
}

Set::Interval::Interval(Int::Int left, Int::Int right) {
	if(left >= right) {
		*this = Interval::Empty();
		return;
	}

	this->left = LeftIntervalBorder(left, false);
	this->right = RightIntervalBorder(right, false);
}

Set::Interval::Interval(Int::Int left, bool leftClosed, Int::Int right, bool rightClosed) {
	if(left > right || (left == right && !(leftClosed && rightClosed))) {
		*this = Interval::Empty();
		return;
	}

	this->left = LeftIntervalBorder(left, leftClosed);
	this->right = RightIntervalBorder(right, rightClosed);
}

Set::Interval::Interval(const Interval& other) {
	this->left = other.left;
	this->right = other.right;
}

bool Set::Interval::IsEmpty() const {
	return left.value == right.value && !left.closed && !right.closed;
}

bool Set::Interval::Contains(Int::Int value) const
{
	return left.Contains(value) && right.Contains(value);
}

bool Set::Interval::ContainsIntegers() const {
	if(IsEmpty())
		return false;

	return !(left.value + 1 == right.value && !left.closed && !right.closed);
}

Set::Interval Set::Interval::Intersection(const Interval& other) const
{
	Int::Int _left, _right;
	bool leftClosed = false, rightClosed = false;

	if(left.value == other.right.value) {
		if(left.closed && other.right.closed) {
			return Interval::SingleElement(left.value);
		}

		return Interval::Empty();
	}

	if(right.value == other.left.value) {
		if(right.closed && other.left.closed) {
			return Interval::SingleElement(right.value);
		}

		return Interval::Empty();
	}

	if(left.value > other.left.value) {
		_left = left.value;
		leftClosed = left.closed;
	} else if(left.value == other.left.value) {
		if(left.closed || other.left.closed) {
			_left = left.value;
			leftClosed = true;
		} else {
			_left = left.value;
			leftClosed = false;
		}
	} else {
		_left = other.left.value;
		leftClosed = other.left.closed;
	}

	if(right.value < other.right.value) {
		_right = right.value;
		rightClosed = right.closed;
	} else if(right.value == other.right.value) {
		if(right.closed || other.right.closed) {
			_right = right.value;
			rightClosed = true;
		} else {
			_right = right.value;
			rightClosed = false;
		}
	} else {
		_right = other.right.value;
		rightClosed = other.right.closed;
	}

	if(left.value == other.left.value) {
		leftClosed = left.closed && other.left.closed;
	}

	if(right.value == other.right.value) {
		rightClosed = right.closed && other.right.closed;
	}

	return Interval(
		LeftIntervalBorder(
			_left,
			leftClosed
		),
		RightIntervalBorder(
			_right,
			rightClosed
		)
	);
}

Set::Interval Set::Interval::SingleElement(Int::Int element) {
	return Interval(
		LeftIntervalBorder(element, true),
		RightIntervalBorder(element, true)
	);
}

Set::Interval Set::Interval::Empty() {
	Interval result = Interval(
		LeftIntervalBorder(0, true),
		RightIntervalBorder(0, true)
	);

	result.left.closed = false;
	result.right.closed = false;

	return result;
}

Set::Set::Set() {}

Set::Set::Set(std::vector<Interval> intervals) {
	this->intervals = intervals;
}

Set::Set::Set(const Set& other) {
	this->intervals = other.intervals;
}

bool Set::Set::IsEmpty() const {
	if(intervals.empty())
		return true;

	for(const Interval& interval : intervals)
		if(!interval.IsEmpty())
			return false;

	return true;
}

bool Set::Set::Contains(Int::Int value) const
{
	if(IsEmpty())
		return false;

	for(const Interval& interval : intervals)
		if(interval.Contains(value))
			return true;

	return false;
}

bool Set::Set::ContainsIntegers() const {
	if(IsEmpty())
		return false;

	for(const Interval& interval : intervals)
		if(interval.ContainsIntegers())
			return true;

	return false;
}

Set::Set Set::Set::Intersection(const Set& other) const
{
	if(IsEmpty() || other.IsEmpty())
		return Set::Empty();

	Set result;

	for(const Interval& interval : intervals)
		for(const Interval& otherInterval : other.intervals) {
			Interval intersection = interval.Intersection(otherInterval);

			if(!intersection.IsEmpty())
				result.intervals.push_back(intersection);
		}

	// Return the result
    return result;
}

Set::Set Set::Set::SingleElement(Int::Int element) {
	return Set(std::vector<Interval>({ Interval::SingleElement(element) }));
}

Set::Set Set::Set::Empty() {
	return Set();
}

Set::Set Set::Set::Real() {
	return Set(std::vector<Interval>({ Interval(-Int::Int::Infinity(), Int::Int::Infinity()) }));
}