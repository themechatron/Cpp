#include "Competition.h"
#include<time.h>
Competition::Competition(const Date& other, std::string place):date(other),place(place){ }
Competition::Competition(const Competition& other) {
	date = other.date;
	place = other.place;
	participant = other.participant;
	for (unsigned int i = 0; i < participant.size(); i++) {
		participant[i] = new TimeLord(*participant[i]);
	}
}
bool Competition::registerTimeLord(TimeLord& other) {
	bool check = false;
	if (participant.size() != 0){
		for (unsigned int i = 0; i < participant.size(); i++) {
			if (participant[i] == &other) {
				check = false;
				break;
			}
			else {
				check = true;
			}
		}
	}
	else {
		check = true;
	}
	if (check) {
		for (int h = 0; h <= 24; h++) {
			if (other.canVisit(place, date, h)) {
				participant.push_back(&other);
				std::cout << "Added new participant..!" << std::endl;
				return true;
			}
		}
		std::cout << "Cannot add new participant..!" << std::endl;
		return false;
	}
	else {
		std::cout << "The user is already registered..!" << std::endl;
		return false;
	}
}
int Competition::numParticipants()const {
	return participant.size();
}
TimeLord& Competition::winner() {
	if (participant.size() != 0) {
		srand(time(NULL));
		unsigned int index = rand() % participant.size();
		return *participant[index];
	}
	else {
		return (TimeLord("undefined"));
	}
}
Competition::~Competition() {
	for (unsigned int i = 0; i < participant.size(); i++) {
		delete participant[i];
	}
}
void Competition::print_participants()const {
	std::cout << "Date: " << date << std::endl;
	std::cout << "Place: " << place << std::endl;
	for (unsigned i = 0; i < participant.size(); i++) {
		std::cout << *participant[i] << std::endl;
	}
}