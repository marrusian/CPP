#include<iostream>
#include<vector>
#include<algorithm>

int main(void)
{
	std::vector<double> temps;
	double sum = 0;
	for(double temp; std::cin >> temp;)
	{
		temps.push_back(temp);
		sum += temps.back();
	}
	
	std::cout << "Average temperature: " << sum/temps.size() << '\n';
	
	sort(temps.begin(), temps.end());
	
	std::cout << "Median temperature: ";
	if(temps.size()%2 != 0)
		std::cout << temps[temps.size()/2];
	else
		std::cout << (temps[temps.size()/2 - 1] + temps[temps.size()/2])/2;
			
	
	return 0;
}

