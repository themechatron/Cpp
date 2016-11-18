#include "MostTimeInCentury.h"
MostTimeInCentury::MostTimeInCentury(const Date& other, std::string place, int c) :Competition(other, place) { century = c; }
MostTimeInCentury::MostTimeInCentury(const MostTimeInCentury& other) : Competition(other) { century = other.century; }
TimeLord& MostTimeInCentury::winner() {
	if (participant.size() != 0) {
		int index = 0;
		for (unsigned int i = 0; i < participant.size(); i++) {
			if (participant[index]->timeSpentInCentury(century) < participant[i]->timeSpentInCentury(century)) {
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
int MostTimeInCentury::getCentury()const {
	return century;
}