#include<iostream>
#include<vector>
#include<cmath>

const int MIN_VALUE = 1;
const int MAX_VALUE = 100;

int main(void)
{
	int number;
	int guess = (MAX_VALUE + MIN_VALUE)/2;
	int high_val = MAX_VALUE;
	int low_val = MIN_VALUE;
	char choice;
	
	std::cout << "Please enter a number between " << MIN_VALUE << " and " << MAX_VALUE << ": ";
	std::cin >> number;
	
	if((!number) || (number < 1) || (number > 100))
	{
		std::cout << "Invalid!";
		return 1;
	}
	
	while(number != guess)
	{			
		std::cout << "Is your number less than " << guess << " ?";
		std::cin >> choice;
			
		if((choice == 'y') || (choice == 'Y'))
		{
			high_val = guess;
			guess = (guess + low_val)/2;
		}
		else if ((choice == 'n') || (choice == 'N'))
		{
			low_val = guess;
			guess = ceil((guess + high_val)/2.0);
		}
		else
			std::cout << "Your choice is invalid!\n";			
	}
	
	std::cout << "Your number is : " << guess;

	return 0;
}
