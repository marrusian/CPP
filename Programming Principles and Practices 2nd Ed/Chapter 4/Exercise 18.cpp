#include<iostream>
#include<vector>
#include<cmath>

int main(void)
{
	std::vector<double> quad;
	double discrim = 0;
	double sol1, sol2;
	
	std::cout << "Introduceti coeficientii ec. de gradul II descrescator: ";
	for (int i = 0; i < 3; i++)
	{
		double coef;
		std::cin >> coef;
		quad.push_back(coef);
	}
	
	discrim = quad.at(1)*quad.at(1) - 4*quad.at(0)*quad.at(2);
	
	if(discrim >= 0)
	{
		sol1 = (-quad.at(1) - sqrt(discrim))/(2*quad.at(0));
		sol2 = (-quad.at(1) + sqrt(discrim))/(2*quad.at(0));
		
		std::cout << "X = " << sol1 << "\t Y = " << sol2 << '\n';
	}
	else
	{
		discrim = -discrim;
		sol1 = (-quad.at(1) - sqrt(discrim))/(2*quad.at(0));
		sol2 = (-quad.at(1) + sqrt(discrim))/(2*quad.at(0));
		
		std::cout << "X = " << sol1 << "i\t Y = " << sol2 << "i\n";
	}
	

	
	
	
	return 0;
}
