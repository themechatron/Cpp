#pragma once
#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <string>
#include "Date.h"
class Event
{
public:
	Event(const Date&, int, int, std::string title = "<Untitled Event>", std::string description = "",std::string place_name="");
	virtual ~Event();
	virtual bool isInProgress(const Date&, int) const;
	virtual bool isHappeningAt(std::string, const Date&, int);
	Date getDate() const;
	int getHour() const;
	friend std::ostream& operator<< (std::ostream&, const Event&);
	friend std::istream& operator>> (std::istream&, Event&);
protected:
	Date date;
	int startHour;
	int endHour;
	std::string title;
	std::string description;
	std::string place_name;
	virtual std::ostream& write(std::ostream& out) const;
};

#endif // EVENT_H