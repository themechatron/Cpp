#pragma once
#ifndef COMPETITION_H
#define COMPETITION_H
#include "Date.h"
#include "TimeLord.h"
#include<vector>
class Competition {
private:
protected:
	Date date;
	std::string place;
	std::vector<TimeLord*> participant;
public:
	Competition(const Date&, std::string="");
	Competition(const Competition&);
    bool registerTimeLord(TimeLord&);
    int numParticipants()const;
	void print_participants() const;
	virtual TimeLord& winner();
	virtual ~Competition();
};
#endif