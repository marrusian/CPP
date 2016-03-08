#include<iostream>
#include<cstring>
#include<cmath>

void message(int, int [], std::string[]);
int sumCents(int []);

int main(void)
{
	int money[6] = {};
	std::string moneyn[6] = {"Pennies", "Nickels", "Dimes", "Quarters", "Half Dollars", "Dollars"};
	int total_cents = 0;
	
	for(int i = 0; i < 6; i++)
	{
		std::cout << moneyn[i] << ": ";
		std::cin >> money[i];
	}
	
	std::cout << std::endl;
	
	for(int i = 0; i < 6; i++)
	{
		if(money[i] > 0)
		{
			message(i, money, moneyn);	
		}
	}
	
	std::cout << std::endl;
	std::cout << "The value of all your coins is ";
	std::cout << sumCents(money) << " cents!\n";	
	
	return 0;
}

void message(int index, int money_val[], std::string money_name[])
{
	std::cout << "You have " << money_val[index] << " ";
	if(money_val[index] == 1)
		for(std::string::iterator it = money_name[index].begin(); it != (money_name[index].end() - 1); it++)
			std::cout << *it;
	else
		std::cout << money_name[index];
	std::cout << std::endl;
	
	return;
}

int sumCents(int money_val[])
{
	int run = 0, n = 0, k = 0;
	int total = 0;
	while(run < 6)
	{		
		if(n >= k)
		{
			total += money_val[(run)]*(pow(5.0, n) * pow(2.0, k));
			k++;
			run++;
		}
		else
		{
			n++;
			k = 0;
		}
	}
	
	return total;	
}
