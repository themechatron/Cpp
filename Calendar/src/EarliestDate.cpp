#include "EarliestDate.h"
EarliestDate::EarliestDate(const Date& other, std::string place) :Competition(other, place) { }
EarliestDate::EarliestDate(const EarliestDate& other) : Competition(other) { }
TimeLord& EarliestDate::winner() {
	if (participant.size() != 0) {
		int index = 0;
		for (unsigned int i = 0; i < participant.size(); i++) {
			if (participant[index]->earliestVisitedDate() > participant[i]->earliestVisitedDate()) {
				index = i;
			}
		}
		return *participant[index];
	}
	else {
		TimeLord *temp = new TimeLord("undefined");
		return *temp;
	}
}