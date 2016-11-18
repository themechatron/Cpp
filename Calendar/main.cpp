#include <iostream>
#include "Event.h"
#include "WeeklyEvent.h"
#include "Calendar.h"
#include "Date.h"
#include "TimeLord.h"
#include "Competition.h"
#include "EarliestDate.h"
#include "MostEventNum.h"
#include "MostTimeInCentury.h"
int main()
{
	//task 1
	TimeLord zaki("ZAKI");//timelord
	zaki.newCalendar("zaki");
	zaki.newEvent(Date(2016, 5, 1), 12, 14, "Easter lunch","Description","Sofia");
	zaki.newEvent(Date(2016, 7, 2), 15, 17, "Work out", "Chest","");//empty string for place
	zaki.newEvent(Date(2016, 5, 1), 9, 18, "Studying", "OOP-Lekcii", "FMI");
	zaki.newCalendar("gosho");
	zaki.newEvent(Date(2016, 8, 20), 0, 24, "Rest", "Day","Home");
	zaki.newEvent(Date(2100, 2, 2), 10, 11, "Running", "Cardio", "Rila mountain");
	zaki.newEvent(Date(2016, 4, 12), 0, 24, "Armwresting", "Right hand", "");
	zaki.newEvent(Date(2016, 5, 5), 0, 24, "Something again", "SU", "FMI");
	std::cout << zaki;
	Calendar pesho = zaki.allArchives("2016 archives");
	std::cout << pesho;
	std::cout << pesho.hasEventAt("Empty string", Date(2016, 7, 2), 16) << std::endl;//done
	std::cout << zaki.canVisit("FMI", Date(2016, 5, 1), 10) << std::endl;//done
	//task 2
	TimeLord gosho("Gosho");//timelord
	gosho.newCalendar("gosho");
	gosho.newEvent(Date(2016, 5, 5), 0, 24, "Hack fmi", "Programming", "FMI");
	gosho.newEvent(Date(2100, 2, 2), 13, 15, "", "", "");
	gosho.newEvent(Date(2016, 4, 12), 0, 24, "Armwresting", "Right hand", "");
	gosho.newEvent(Date(2016, 8, 20), 0, 24, "Rest", "Day", "Home");
	std::cout <<"Earliest visited date: "<< zaki.earliestVisitedDate() << std::endl;//ok
	std::cout << "Time spent in century: "<<zaki.timeSpentInCentury(21) << std::endl;//ok
	std::cout << "Number of events: "<<zaki.numEvents() << std::endl;//ok
	TimeLord ivan("Ivan");//timelord
	ivan.newCalendar("Ivan");
	ivan.newEvent(Date(400, 8, 4),12,14, "", "", "");
	ivan.newEvent(Date(2016, 4, 12), 0, 24, "Armwresting", "Right hand", "");
	ivan.newEvent(Date(2016, 5, 5),0,24, "Something", "", "FMI");
	ivan.newEvent(Date(2016, 8, 20), 0, 24, "Rest", "Day", "Home");
	Competition *example = new MostTimeInCentury(Date(2016, 5, 5), "FMI",6);
	example->registerTimeLord(zaki);
	example->registerTimeLord(gosho);
	example->registerTimeLord(ivan);
	gosho.newEvent(Date(510, 1, 1), 12, 15, "", "", "");//ok
	example->registerTimeLord(gosho);//ok
	example->print_participants();
	example->registerTimeLord(zaki);//ok
	example->registerTimeLord(gosho);//ok
	//new
	Competition *earliest = new EarliestDate(Date(2016, 4, 12), "");
	earliest->registerTimeLord(zaki);
	earliest->registerTimeLord(gosho);
	earliest->registerTimeLord(ivan);
	//new
	Competition *numEvent = new MostEventNum(Date(2016, 8, 20), "Home");
	numEvent->registerTimeLord(zaki);
	numEvent->registerTimeLord(gosho);
	numEvent->registerTimeLord(ivan);
	std::cout << "Most time in century: " << example->winner().getName() << std::endl; //ok
	std::cout << "Earliest date: " << earliest->winner().getName() << std::endl; //ok
	std::cout << "Most event number: " << numEvent->winner().getName() << std::endl; //ok
	system("pause");
	return 0;
}