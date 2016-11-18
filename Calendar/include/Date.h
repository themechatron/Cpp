#pragma once
#ifndef DATE_H
#define DATE_H

#include <iostream>
class Date
{
public:
	Date(int year = 1970, int month = 1, int day = 1);
	bool operator== (const Date&) const;
	bool operator!= (const Date&) const;
	bool operator< (const Date&) const;
	bool operator<= (const Date&) const;
	bool operator> (const Date&) const;
	bool operator>= (const Date&) const;
	Date& operator++();
	Date operator++(int);
	Date operator+ (int) const;
	int dayOfWeek() const;
	bool isLastDayOfMonth() const;
	bool isLastMonthOfYear() const;
	bool isLeapYear() const;
	int getYear()const;
	friend std::ostream& operator<< (std::ostream&, const Date&);
	friend std::istream& operator>> (std::istream&, Date&);
protected:
private:
	int year;
	int month;
	int day;
};

#endif // DATE_H