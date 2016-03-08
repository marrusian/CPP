#include<iostream>
#include<vector>
#include<random>
#include<algorithm>
#include<chrono>

const int SIZE = 100;

int main(void)
{
	std::vector<int> mode;
	std::vector<int> seq;
	std::vector<int> pos;
	int s1, s2, s3 = 0;
	unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
	
	std::minstd_rand0 generator (seed1);
	std::uniform_int_distribution<int> distribution1(1, 100);
	s1 = distribution1(generator);
	s2 = distribution1(generator);
	s3 = distribution1(generator);
	std::poisson_distribution<int> distribution2(s1+s2-s3);

		
	for (int i = 0; i <= SIZE; i++)
	{
		seq.push_back(distribution2(generator));
		std::cout << seq.back() << '\n';
	}
	
	sort(seq.begin(), seq.end());
	
	for (int i = 0, c1 = 1, c2 = 1; i < seq.size() - 1; i++)
	{
		if(seq.at(i) == seq.at(i+1))
			c1++;
		else
		{
			if(c1 > c2)
			{
				c2 = c1;
				pos.insert(pos.begin()+0, i);
				pos.insert(pos.begin()+1, c2);
			}	
			c1 = 0;
		}
	}
	
	std::cout << "Mode is: " << seq.at(pos[0]) << "(" << pos[1] << " times)";
	
	
	return 0;
}
