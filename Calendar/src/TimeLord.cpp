#include "TimeLord.h"
TimeLord::TimeLord(std::string name) :name(name) {
	// empty implementation
	// archive is automatically initialized
	// using its default constructor
}
void TimeLord::newCalendar(std::string name) {
	archive.push_back(new Calendar(name));
}
void TimeLord::newEvent(const Date& other, int start, int end, std::string name, std::string description,std::string place_name) {
	if (archive.size() == 0) {
		std::cout << "Cannot add event...Create calendar first..!" << std::endl;
		return;
	}
	archive.back()->addEvent(other, start, end, name, description,place_name);
}
Calendar TimeLord::allArchives(std::string name) {
	Calendar *temp = new Calendar(name);
	for (unsigned int i = 0; i < archive.size(); i++) {
		(*temp) += *archive[i]; // Calendar::operator+=
	}
	return *temp;
}
std::ostream& operator<<(std::ostream& out, const TimeLord& other) {
	std::cout <<"TimeLord: "<< other.name << std::endl;
	for (unsigned int i = 0; i < other.archive.size(); i++) {
		std::cout << (*other.archive[i]);
	}
	return out;
}
bool TimeLord::canVisit(std::string place, const Date& other, int hour) const{
	//1st way
	for (unsigned int i = 0; i < archive.size(); i++) {
		if (archive[i]->hasEventAt(place, other, hour))
			return true;
	}
	return false;
	//return allArchives().hasEventAt(place, other, hour); //2nd way
}
TimeLord::~TimeLord() {
	for (unsigned int i = 0; i < archive.size(); i++) {
		delete archive[i];
	}
}
int TimeLord::numEvents()const {
	int index = 0;
	for (unsigned int i = 0; i < archive.size(); i++) {
		index += archive[i]->eventNum();
	}
	return index;
}
Date TimeLord::earliestVisitedDate()const {
	int index = 0;
	for (unsigned int i = 0; i < archive.size(); i++) {
		if (archive[index]->earliestDate() > archive[i]->earliestDate()) {
			index = i;
		}
	}
	return archive[index]->earliestDate();
}
int TimeLord::timeSpentInCentury(int century)const {
	int totalHours = 0;
	for (unsigned int i = 0; i < archive.size(); i++) {
		for (unsigned int j = 0; j < archive[i]->eventNum(); j++) {
			if (archive[i]->getDate(j).getYear()/100==(century-1)) {
				totalHours += archive[i]->getHour(j);
			}
		}
	}
	return totalHours;
}
std::string TimeLord::getName() const {
	return name;
}