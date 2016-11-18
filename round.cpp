#include<iostream>
#include<cmath>
using namespace std;
class Round {
private:
	double x, y, r;
public:
	Round(int _x = 1, int _y = 1, int _r = 2) {
		x = _x;
		y = _y;
		r = _r;
	}
	double getX() const {
		return x;
	}
	double getY() const {
		return y;
	}
	double getR() const {
		return r;
	}
	void setX(double _x) {
		x = _x;
	}
	void setY(double _y) {
		y = _y;
	}
	void setR(double _r) {
		if (_r >= 0) {
			r = _r;
		}
		else {
			cout << "Enter non negative value..!" << endl;
		}
	}
};
void EnterCircle(Round& p) {
	double temp;
	cout << "X: ";
	cin >> temp;
	
	p.setX(temp);
	cout << "Y: ";
	cin >> temp;

	p.setY(temp);
	cout << "R: ";
	cin >> temp;

	p.setR(temp);
}
bool crossed(Round& p, Round& q) {
	double result = sqrt((p.getX() - q.getX())*(p.getX() - q.getX())) + sqrt((p.getY() - q.getY())*(p.getY() - q.getY()));
	return (abs(p.getR() - q.getR()) <= result && result <= (p.getR() + q.getR()));
}

bool isTherePath(Round& p, Round& q) {
	return(crossed(p, q));
}
bool isTherePathA1An(Round *group,int n,int &path,int current) {
	bool temp = false;
	for (int i = current+1; i < n; i++) {
		if (isTherePath(group[current], group[i]) && current !=i) {
			temp = true;
			path++;
			if (path < n) {
				isTherePathA1An(group, n, path, i);
				break;
			}
		}
		else {
			temp = false;
		}
	}
	return temp;
}
int main() {
	int n;
	int path = 0;
	Round group[100];
	cout << "Enter number of the circles: ";
	cin >> n;
	for (int i = 0; i < n; i++) {
		cout <<"Circle "<< i+1 << ": " << endl;
		EnterCircle(group[i]);
	}
	cout << isTherePathA1An(group, n,path,0) << endl;
	cout << path;
	system("pause");
	return 0;
}