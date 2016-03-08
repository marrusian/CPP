#include<iostream>
#include<stdexcept>

int main(void)
try{
	int n = 0;
	int b = 1;
	std::cout << "Please enter how many numbers from the Fibonacci"
			  << " sequence you wish to compute: ";
	std::cin >> n;
	for (int a = 0, c = 1; a >= 0; c++)
	{
		a = a + b;
		b = a - b;
		std::cout << a << ' ';
	}
	std::cout << '\n' << b << " is the largest Fibonacci number that fits in an INT\n";
	
	
	return 0;
}catch(std::exception &estr)
{
	std::cerr << "Error: " << estr.what() << '\n';
	return 1;
}
