#include<iostream>
#include<vector>
#include<cmath>

int main(void)
{
	std::vector<long double> grains;
	int min_req = 0;
	long double amount;
	
	std::cin >> amount;
	grains.push_back(0);
	
	for(int i = 0; i < 64; i++)
	{
		grains.push_back(grains.back() + pow(2.0,double(i)));
		if((min_req == 0) && (amount <= grains.back()))
		{
			min_req = i+1;
			std::cout << "The minimum required squares to get " << amount;
			std::cout << " grains is " << min_req << '\n';
		}
	}
	
	std::cout << grains[63];
	
	
	
	return 0;
}

