#include "MostEventNum.h"
MostEventNum::MostEventNum(const Date& other, std::string place) :Competition(other, place) { }
MostEventNum::MostEventNum(const MostEventNum& other) : Competition(other) { }
TimeLord& MostEventNum::winner() {
	if (participant.size() != 0) {
		int index = 0;
		for (unsigned int i = 0; i < participant.size(); i++) {
			if (participant[index]->numEvents() < participant[i]->numEvents()) {
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