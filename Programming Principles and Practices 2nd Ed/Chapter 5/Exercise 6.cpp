#include<iostream>
#include<cstring>
#include<stdexcept>
#include<vector>
#include<cmath>
#include<climits>

void error(std::string);
double ctok(double&);
double ktoc(double&);
double ctof(double&);
double ftoc(double&);
double check_range(double&);

const int ABS_ZERO_K = 0;
const double ABS_ZERO_C = -273.15;
const double ABS_ZERO_F = -459.67;
const double K_TO_C = 273.15;


int main(void)
try{
	
	double c = 0;
	std::cin >> c;
	
	std::cout << ctok(c) << std::endl;
	std::cout << ctof(c) << std::endl;

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

double ctok(double &c)
{
	double k = c + K_TO_C;
	if(k < ABS_ZERO_K)
		error("Entered temperature can't be lower than -273.15 Celsius (absolut zero)");
	

	return check_range(k);;
}

double ktoc(double &k)
{
	double c = k + -K_TO_C;
	if(c < ABS_ZERO_C)
		error("Entered temperature can't be lower than 0 Kelvin (absolut zero)");
	

	return check_range(c);;
}

double ctof(double &c)
{
	double f = (9.0/5.0)*c + 32;
	if(f < ABS_ZERO_F)
		error("Entered temperature can't be lower than -273.15 Celsius (absolut zero)");
	
	return check_range(f);
}

double ftoc(double &f)
{
	double c = (5.0/9.0)*(f-32);
	if(c < ABS_ZERO_C)
		error("Entered temperature can't be lower than -459.67 Fahrenheit (absolut zero)");
	
	return check_range(c);
}

double check_range(double &unit)
{
	if(unit > INT_MAX)
		error("The result is not within INTEGER upper limit(" + std::to_string(INT_MAX) + ")");
	else
		return unit;
}

