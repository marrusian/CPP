#include<iostream>
#include<vector>
#include<cmath>
#include<stdexcept>
#include<cstring>
#include<utility>

void error(std::string);
std::pair<double, double> quadratic(double&, double&, double&);

int main(void)
try{
	double c1 = 0, c2 = 0, c3 = 0;
	std::pair <double, double> sols;
	
	std::cout << "Introduceti coeficientii ec. de gradul II descrescator: ";
	while (std::cin >> c1 >> c2 >> c3)
	{
		sols = quadratic(c1, c2, c3);
		if(!std::isnan(sols.first))
			std::cout << "x1 = " << sols.first << "\t x2 = " << sols.second << '\n';
		
		std::cout << "\nIntroduceti alta ecuatie: ";
	}
	
	if(!std::cin)
		error("Invalid character input. Terminating !");
	
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

std::pair<double, double> quadratic(double &a, double &b, double &c)
{
	if(!a)
	{
		std::cout << "X^2's coefficient is 0, that's not a quadratic.\n";
		return std::make_pair(NAN, NAN);
	}
	
	double discrim = 0;
	discrim = b*b - 4*a*c;
	
	if(discrim < 0)
	{
		std::cout << "This equation has no real roots!\n";
		return std::make_pair(NAN, NAN);
	}
	else
	{
		double x1, x2;
		x1 = (-b - sqrt(discrim))/(2*a);
		x2 = (-b + sqrt(discrim))/(2*a);
		
		return std::make_pair(x1,x2);
	}
}

