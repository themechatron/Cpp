#pragma once
#ifndef MOSTEVENTNUM_H
#define MOSTEVENTNUM_H
#include "Competition.h"
class MostEventNum : public Competition {
private:
protected:
public:
	MostEventNum(const Date&, std::string place = "");
	MostEventNum(const MostEventNum&);
	virtual TimeLord& winner();
};
#endif // !MOSTEVENTNUM_H
