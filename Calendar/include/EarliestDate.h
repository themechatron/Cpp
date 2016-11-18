#pragma once
#ifndef EARLIESTDATE_H
#define EARLIESTDATE_H
#include "Competition.h"
class EarliestDate : public Competition {
private:
protected:
public:
	EarliestDate(const Date&, std::string place = "");
	EarliestDate(const EarliestDate&);
	virtual TimeLord& winner();
};
#endif