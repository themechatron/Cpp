#pragma once
#ifndef CALENDAR_H
#define CALENDAR_H
#include <vector>
#include <string>
#include "Event.h"
#include "Date.h"
class Calendar
{
public:
	Calendar(std::string name = "<New Calendar>");
	Calendar(const Calendar&);
	Calendar& operator=(const Calendar&);
	~Calendar();
	std::string getName() const;
	void rename(const std::string&);
	void addEvent(const Date&, int, int, std::string = "Event", std::string = "",std:: string ="");
	void addWeeklyEvent(const Date&, int, int, int, std::string = "Weekly Event", std::string = "",std::string="");
	bool isFree(const Date& date, int hour) const;
	Calendar& operator+=(const Calendar&);
	bool hasEventAt(std::string, const Date&, int);
	int eventNum()const;
	Date earliestDate()const;
	Date getDate(int index) const;
	int getHour(int index) const;
	friend std::ostream& operator<< (std::ostream&, const Calendar&);
protected:
private:
	std::string name;
	std::vector<Event*> events;
	void init(const Calendar& other);
	void destroy();
};

#endif // CALENDAR_H