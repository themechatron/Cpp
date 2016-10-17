#include<iostream>
using namespace std;
int main()
{
	const long long int max = 65536;
	int length;
	std::cout << "Enter upper limit: ";
	std::cin >> length;
	bool primes[max];
	for (int i = 0; i<max; i++){
		primes[i] = true;
	}
	primes[0] = primes[1] = false;

	for (int i = 2; i < length; i++){
		if (primes[i]){
			for (int j = i + i; j < length; j += i){
				primes[j] = false;
			}
		}
	}
	for (int i = 0; i < length; i++){
		if (primes[i]){
			std::cout << i << " ";
		}
	}
	system("pause");
	return 0;
}