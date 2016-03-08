#include<iostream>
#include<vector>
#include<cstring>
#include<stdexcept>
#include<cmath>

const int DAYS_OF_THE_WEEK = 7;
std::vector<std::string> days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday",
								 "Saturday", "Sunday"};

int main(void)
try{
	std::vector< std::vector<int> > values(DAYS_OF_THE_WEEK);
	std::vector<int> sums(DAYS_OF_THE_WEEK);
	std::string d_name; // day name;
	int value = 0, rejected = 0;
	
	std::cout << "Enter (day-of-the-week, value) pairs: ";
	
	while (std::cin >> d_name >> value)
	{
		d_name.front() = toupper(d_name.front());
		for (int i = 0; i < DAYS_OF_THE_WEEK; i++)
		{
			if((d_name == days[i]) || (d_name == days[i].substr(0, 3)))
			{
				values[i].emplace_back(value);
				sums[i] += value;
				break;
			}
			else if(i == DAYS_OF_THE_WEEK - 1)
			{
				std::cout << "That's not a legal day name. Try again: ";
				rejected++;
				break;
			}
		}				
	}
	
	for (int i = 0; i < DAYS_OF_THE_WEEK; i++)
	{
		std::cout << days[i] << ": ";
		for (int j = 0; j < values[i].size(); j++)
		{
			std::cout << values[i][j];
			if(j != values[i].size() - 1)
				std::cout << ", ";
		}
		std::cout << ".\t Sum: ";
		if(sums[i])
			std::cout << sums[i] << '\n';
		else
			std::cout << NAN << '\n';
	}
	
	std::cout << "Rejected values: " << rejected;
	
	return 0;
}catch (std::exception &estr)
{
	std::cerr << "Error: " << estr.what() << '\n';
	return 1;
}
