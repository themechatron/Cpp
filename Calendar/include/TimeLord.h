#pragma once
#ifndef TIMELORD_H
#define TIMELORD_H
#include<iostream>
#include "Calendar.h"
class TimeLord {
private:
	std::string name;
	std::vector<Calendar*> archive;
protected:
public:
	TimeLord(std::string name = "<New TimeLord>");
	void newCalendar(std::string name = "<Untitled calendar>");
	void newEvent(const Date&, int, int, std::string name = "<Untitled event>", std::string description = "",std::string place_name="");
	Calendar allArchives(std::string name="<All archives>");
	bool canVisit(std::string, const Date&, int)const;
	std::string getName()const;
	int numEvents()const;
	Date earliestVisitedDate()const;
	int timeSpentInCentury(int century)const;
	~TimeLord();
	friend std::ostream& operator<< (std::ostream&, const TimeLord&);
};
#endif //TIMELORD_H