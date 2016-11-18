#include<iostream>
#include<cmath>
using namespace std;
double dist(int a, int b, int c, int pX, int pY, int pZ) {
	return sqrt(pow((a - pX), 2) + pow((b - pY), 2) + pow((c - pZ), 2)); 
}
double fitness(int cubA, int cubB, int cubC, double planets[3][4],int planetsNum) {
	double sum = 0;
	for (int i = 0; i < planetsNum; i++) {
		sum = sum + dist(cubA, cubB, cubC, planets[i][0], planets[i][1], planets[i][2])*planets[i][3];
	}
	return sum;
}
int main() {
	double planets[3][4] = {{1,1,1,0.98},{2,2,2,1.05},{3,3,3,1.02}};
	double cubA, cubB, cubC, x;
	double saveFitness = 0;
	int length = 1,one,two,three;
	cout << "Enter coordinates for left angle of the cube: ";
	cin >> cubA >> cubB >> cubC;
	cout << "Enter the length of the side of the cube: ";
	cin >> x;
	for (int i = ceil(cubA); i <= int(cubA + x); i++) {
		for (int j = ceil(cubB); j <= int(cubB + x); j++) {
			for (int k = ceil(cubC); k <= int(cubC + x); k++)
			{
				if (fitness(i, j, k, planets, 3)>saveFitness) {
					saveFitness = fitness(i, j, k, planets, 3);
					one = i;
					two = j;
					three = k;
				}
			}
		}
	}
	cout << "Best point is: " << "(" << one << "," << two << "," << three << ") with fitness value: " << saveFitness << endl;
	system("PAUSE");
	return 0;
}