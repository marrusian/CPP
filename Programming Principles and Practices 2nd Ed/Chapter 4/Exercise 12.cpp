#include<iostream>

const int LIMIT = 100000;

int main()
{
	int i = 3, j, flag;
	bool arr[LIMIT] = {};

	while (i < LIMIT)
	{	// Plecam de la i^2 si eliminam toti multipli impari;
		for(j = i; (j*i) < LIMIT; j += 2)
		{
			arr[i*j] = true;
		}

		flag = i * i;
		for(i += 2; i < LIMIT; i += 2)
		{
			if(!arr[i])
			{	
				std::cout << i << '\n';	
				if(flag <= LIMIT)
					break;
				else
					continue;			
			}	
		}
	}

	return 0;
}

