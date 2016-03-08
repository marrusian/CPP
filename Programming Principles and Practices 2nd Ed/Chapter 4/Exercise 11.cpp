#include<iostream>
#include<vector>

const int LIMIT = 100000;

int main(void)
{
	std::vector<int> primes;
	bool flag = true;
	
	for (int i = 2; i <= LIMIT; i++)
	{
		for (int k = 2; k*k <= i; k++)
		{
			if(i%k == 0)
			{
				flag = false;
				break;	
			}
			
		}
		
		if(flag)
			primes.push_back(i);
		
		flag = true;		
	}
	
	for (std::vector<int>::iterator it = primes.begin(); it != primes.end(); it++)
		std::cout << *it << '\n';
	
	return 0;
}
