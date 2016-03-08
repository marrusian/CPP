#include<iostream>
#include<vector>
#include<stdexcept>
#include<cstring>

void error(std::string);

int main(void)
try{
	std::vector<int> numbers;
	int limit = 0, sum = 0;
	
	std::cout << "Please enter some integers(press '|' to stop): ";
	while(std::cin)
	{
		double elem;
		std::cin >> elem;
		if(elem != int(elem))
			error("Floating-point numbers are not allowed!");
		numbers.emplace_back(elem);
	}
	std::cin.clear();
	std::cin.ignore();
		
	std::cout << "Please enter how many of the numbers you wish "
			  << "to sum, starting from the first: ";
	
	std::cin >> limit;	
	if((limit < 0) || ((numbers.size()-1) < limit))
		error("The number has to be between 0 and " + std::to_string(numbers.size()-1));
			
	std::cout << "The sum of the first " << limit << " numbers( ";
	for (int i = 0; i < limit; i++)
	{
		std::cout << numbers[i] << ' ';
		sum += numbers[i];
	}
	std::cout << ") is " << sum;	
	
	return 0;
	
}catch(std::exception &estr)
{
	std::cerr << "Error: " << estr.what() << '\n';
	return 1;
}

void error(std::string estr)
{
	throw std::runtime_error(estr);
}
