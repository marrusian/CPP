#include<iostream>
#include<cstring>
#include<vector>

int main(void)
{
	std::vector<std::string> wdigit = {"zero", "one", "two", "three", "four", "five",
								  "six", "seven", "eight", "nine"}; // wdigit = worded digit;
	int digit = -1;
	std::string sdigit;
	
	std::cout << "Insert a single digit or a spelled-out digit: ";	
	while (true)
	{
		if(std::cin >> digit)
		{
			if((digit >= 0) && (digit < 10))
				std::cout << wdigit[digit] << '\n';
			else
				std::cout << "That's not a single digit. Try again: ";
		}
		else
		{
			std::cin.clear();
			std::cin >> sdigit;
			for (int i = 0; i < wdigit.size(); i++)
			{
				if(sdigit == wdigit[i])
				{
					std::cout << i << '\n';
					break;
				}
				else if(i == wdigit.size()-1)
					std::cout << "That's not a valid input. Try again: ";
			}		
		}	
	}	
	
	return 0;
}

