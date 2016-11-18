#include "Calendar.h"
#include "Event.h"
#include "WeeklyEvent.h"
void Calendar::init(const Calendar& other) {
	name = other.name;
	events = other.events;
	for (unsigned int i = 0; i < events.size(); i++) {
		// copy the events so that they are not shared
		// between the calendars
		events[i] = new Event(*events[i]);
	}
}

void Calendar::destroy() {
	// delete all events that we have created using new
	for (unsigned int i = 0; i < events.size(); i++) {
		delete events[i];
	}
}

Calendar::Calendar(std::string name) : name(name) {
	// empty implementation
	// events is automatically initialized
	// using its default constructor
}

Calendar::Calendar(const Calendar& other) {
	init(other);
}

Calendar::~Calendar()
{
	destroy();
}

Calendar& Calendar::operator=(const Calendar& other) {
	if (this != &other) {
		destroy();
		init(other);
	}
	return *this;
}

std::string Calendar::getName() const {
	return name;
}

void Calendar::rename(const std::string& newName) {
	name = newName;
}

bool Calendar::isFree(const Date& date, int hour) const {
	for (unsigned int i = 0; i < events.size(); i++) {
		if (events[i]->isInProgress(date, hour)) {
			return false;
		}
	}
	return true;
}
void Calendar::addEvent(const Date& date, int start, int end, std::string title, std::string descr,std::string place_name) {
	Event* e = new Event(date, start, end, title, descr,place_name);
	events.push_back(e);
}
void Calendar::addWeeklyEvent(const Date& date, int start, int end, int numReps,
	std::string title, std::string descr,std::string place_name) {
	Event* we = new WeeklyEvent(date, start, end, numReps, title, descr,place_name);
	events.push_back(we);
}
/*
bool cancelEvent(const Event& event);
bool cancelEvents(const Date& date);
*/

std::ostream& operator<< (std::ostream& out, const Calendar& cal) {
	out << "Calendar: " << cal.name << std::endl;
	out << "Events:" << std::endl;
	for (unsigned i = 0; i < cal.events.size(); i++) {
		out << *cal.events[i];
	}
	return out;
}
Calendar& Calendar::operator+=(const Calendar& other) {
	for (unsigned int i = 0; i < other.events.size(); i++) {
		events.push_back(other.events[i]);
		events[i] = new Event(*events[i]);
	}
	return *this;
}
bool Calendar::hasEventAt(std::string place, const Date& other, int hour) {
	for (unsigned int i = 0; i < events.size(); i++) {
		/*Event *temp = events[i];
		temp = new Event(*temp);*/
		if (events[i]->isHappeningAt(place, other, hour)) {
			//delete temp;
			return true;
		}
		//delete temp;
	}
	return false;
}
int Calendar::eventNum()const {
	return events.size();
}
Date Calendar::earliestDate()const {
	int index = 0;
	for (unsigned int i = 0; i < events.size(); i++) {
		if (events[index]->getDate() > events[i]->getDate()) {
			index = i;
		}
	}
	return events[index]->getDate();
}
Date Calendar::getDate(int index)const {
	return events[index]->getDate();
}
int Calendar::getHour(int index)const {
	return events[index]->getHour();
}