#include "Event.h"
#include <string>
#include <iostream>
Event::Event(const Date& date, int start, int end,
	std::string title, std::string description, std::string place_name)
	:date(date), startHour(start), endHour(end), title(title), description(description), place_name(place_name)
{ }
Event::~Event() {}

bool Event::isInProgress(const Date& when, int hour) const {
	return date == when && hour >= startHour && hour < endHour;
}

std::ostream& Event::write(std::ostream& out) const {
	out << title << "@" << date <<
		" (from " << startHour << "h to " << endHour << "h)" << std::endl;
	out << "Description: "<<description << std::endl;
	out << "Name of the place: "<<place_name << std::endl;
	out << std::endl;
	return out;
}

std::ostream& operator<< (std::ostream& out, const Event& e) {
	return e.write(out);
}

std::istream& operator>> (std::istream& in, Event& e) {
	in >> e.title;
	in >> e.date;
	in >> e.startHour >> e.endHour;
	in >> e.description;
	return in;
}

bool Event::isHappeningAt(std::string place, const Date& other, int hour) {
	if (place_name != "") {
		return ((place_name == place) && date == other && hour >= startHour && hour<endHour);
	}
	return (date==other && hour>=startHour && hour<endHour);
}
Date Event::getDate()const {
	return date;
}
int Event::getHour()const {
	return endHour - startHour;
}