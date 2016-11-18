#include "Date.h"
#include <iostream>

Date::Date(int year, int month, int day) : year(year), month(month), day(day)
{
	// empty - all work is done in the initializer list
}

int Date::dayOfWeek() const {
	int y = this->year;
	int m = this->month;
	int d = this->day;
	// formula taken from Wikipedia
	// returns 0 for Sunday, 1 for Monday, ..., 6 for Saturday
	// https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week#Implementation-dependent_methods
	return (d += m<3 ? y-- : y - 2, 23 * m / 9 + d + 4 + y / 4 - y / 100 + y / 400) % 7;
}

bool Date::isLeapYear() const {
	return (year % 100 != 0 && year % 4 == 0) || year % 400 == 0;
}

bool Date::isLastDayOfMonth() const {
	switch (month) {
	case 4:
	case 6:
	case 9:
	case 11:
		return day == 30;
	case 2:
		if (isLeapYear()) {
			return day == 29;
		}
		else {
			return day == 28;
		}
	default:
		// all other months have 31 days
		return day == 31;
	}
}

bool Date::isLastMonthOfYear() const {
	return month == 12;
}

bool Date::operator==(const Date& other) const {
	return year == other.year &&
		month == other.month &&
		day == other.day;
}

bool Date::operator!=(const Date& other) const {
	return !(*this == other);
}

bool Date::operator< (const Date& other) const {
	if (year > other.year) {
		return false;
	}
	if (year == other.year &&
		(month > other.month || (month == other.month && day >= other.day))) {
		return false;
	}
	return true;
}

bool Date::operator<= (const Date& other) const {
	return *this < other || *this == other;
}

bool Date::operator> (const Date& other) const {
	return !(*this <= other);
}

bool Date::operator>= (const Date& other) const {
	return !(*this < other);
}

// prefix operator ++date
Date& Date::operator++() {
	if (!isLastDayOfMonth()) {
		day++;
	}
	else {
		day = 1;
		if (!isLastMonthOfYear()) {
			month++;
		}
		else {
			month = 1;
			year++;
		}
	}
	return *this;
}

// postfix operator date++
Date Date::operator++(int dummy) {
	Date old(*this);
	++*this;
	return old;
}

Date Date::operator+(int days) const {
	Date result(*this);
	while (days) {
		++result;
		--days;
	}
	return result;
}

std::ostream& operator<<(std::ostream& out, const Date& date) {
	out << date.year << "-" << date.month << "-" << date.day;
	// return the same stream to enable chaining
	return out;
}

std::istream& operator>> (std::istream& in, Date& date) {
	in >> date.year >> date.month >> date.day;
	// return the same stream to enable chaining
	return in;
}
int Date::getYear()const {
	return year;
}