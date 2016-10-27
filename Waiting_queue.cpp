#include<iostream>
#include<queue>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>
using namespace std;

//3 опашки: каса, пуканки, 3д очила

class WaitingQueue{
private:
	int ticksPerPerson;
	int idleTime;
	queue<string> waiting;
	int remainingTicks;
	bool busy;
	//const v kraq na metod ozna4ava 4e ne moje da promenq this-a

public:
	WaitingQueue(int);
	int getIdleTime() const;
	int getNumWaiting() const;
	void push(string);
	bool tick(string&);// vajno da e referenciq
};

WaitingQueue::WaitingQueue(int numTicks) : ticksPerPerson(numTicks), idleTime(0), remainingTicks(0), busy(false) {}

int WaitingQueue::getIdleTime() const{
	return idleTime;
}

int WaitingQueue::getNumWaiting() const{
	return waiting.size();
}

void WaitingQueue::push(string name){
	waiting.push(name);
}

bool WaitingQueue::tick(string& poppedClient){
	if (!busy){
		if (waiting.empty()){ // ne e bila zaeta i o6te ne e
			idleTime++;
			return false;
		}
		else{ // ne e bila zaeta no ve4e e
			busy = true;
			remainingTicks = ticksPerPerson;
			cout << "Start processing " << waiting.front() << endl;
			return false;
		}
	}
	else{
		remainingTicks--;
		if (remainingTicks == 0){
			poppedClient = waiting.front();
			waiting.pop();
			busy = false;
			return true;
		}
		else{
			return false;
		}
	}
}


int main(){
	int numClients = 0;

	bool hasMoved;
	string client;
	WaitingQueue tickets(30);
	WaitingQueue popcorn(90);
	WaitingQueue glasses(15);
	srand(time(NULL));
	for (int t = 0; t<1800; t++){
		if (t % 120 == 0){
			int n = rand() % 11;
			for (int i = 0; i<n; i++){
				stringstream result;
				result << "Client" << numClients;
				string clientName = result.str();
				tickets.push(clientName);
				numClients++;
				/* 2 variant
				char clientName[13];
				sprintf(clientName,"%s%d","Client",numclient);
				*/
			}
		}

		hasMoved = tickets.tick(client); // bool tick (std::string& handledUser) - svyr6ila li e da obslujva 4ovek v tazi
		//sekunda i koi to4no e obslujen za da go prehvyrlim na dr opa6ka
		if (hasMoved){
			cout << client << " has moved from Tickets to ";
			if (rand() % 10 < 7){
				cout << "Popcorn." << endl;
				popcorn.push(client);
			}
			else{
				cout << "Glasses." << endl;
				glasses.push(client);
			}
		}

		hasMoved = popcorn.tick(client);
		if (hasMoved){
			cout << client << " has moved from Popcorn to Glasses" << endl;
			glasses.push(client);
		}

		hasMoved = glasses.tick(client);
		if (hasMoved){
			cout << client << " has entered the cinema!" << endl;
		}
	}
	cout << "Total waiting people: " << (tickets.getNumWaiting() + popcorn.getNumWaiting() + glasses.getNumWaiting()) << endl;
	cout << "Total people waiting for popcorn: " << popcorn.getNumWaiting() << endl;
	cout << "Ticket idle time: " << tickets.getIdleTime() << endl;
	cout << "Popcorn idle time: " << popcorn.getIdleTime() << endl;
	cout << "Glasses idle time: " << glasses.getIdleTime() << endl;
	system("pause");
	return 0;
}
