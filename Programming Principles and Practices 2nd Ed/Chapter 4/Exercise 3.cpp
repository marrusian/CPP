#include<iostream>
#include<vector>

int main(void)
{
	std::vector<double> dist;
	double sum = 0;
	double max_dist = 0;
	double min_dist = 0;
	
	std::cout << "Please enter distances (>0) separated by whitespace\n";
	std::cout << "(insert any non-digit to terminate): ";
	
	for(double val, i = 0; std::cin >> val; i++)
	{
		if (val > 0)
		{
			dist.push_back(val);
			sum += val;
			if ((i == 0) || max_dist < val)
				max_dist = val;
			if ((i == 0) || min_dist > val)
				min_dist = val;
		}
		else
			std::cout << "That's not a valid distance!\n";			
	}
	
	std::cout << "\nSum of all distances: " << sum;
	std::cout << "\nSmallest distance: " << min_dist;
	std::cout << "\nGreatest distance: " << max_dist;
	std::cout << "\nMean distance: " << sum/dist.size();	
	
	return 0;
}
