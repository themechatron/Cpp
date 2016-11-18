#pragma once
#ifndef MOSTTIMEINCENTURY_H
#define MOSTTIMEINCENTURY_H
#include "Competition.h"
class MostTimeInCentury : public Competition {
private:
	int century;
protected:
public:
	MostTimeInCentury(const Date&, std::string = "", int = 0);
	MostTimeInCentury(const MostTimeInCentury&);
	int getCentury() const;
	virtual TimeLord& winner();
};
#endif // !MOSTTIMEINCENTURY_H
