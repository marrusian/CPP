#include<iostream>
#include<cstring>

double arthm(double&, double&, char&);
std::string message;

int main(void)
{
	using namespace std;
	
	double val1, val2;
	char op; // operation;
	double result = 0; 
	
	cout << "Simple calculator V0.1 Alpha\n";
	cout << "Please enter a pair of values and the operation you wish to carry out.\n";
	cout << "Available operations: +, -, /, *, %.\n";
	cout << "Format: 'v1' 'operation' 'v2'. \n";
	
	std::cout << "Input: ";
	while (cin >> val1 >> op >> val2)
	{
		result = arthm(val1, val2, op);
		if(message.back() != '!')
		{
			cout << message << val1 << " and " << val2 << " is " << result << '\n';
			std::cout << "Input: ";
		}	
		else
		{
			cout << message << '\n';
			cout << "Try again: ";
		}
	}
	
	return 0;
}

double arthm(double &x, double &y, char &symb)
{
	switch(symb)
	{
		case '+' : message = "The sum of "; return x+y; break;
		case '-' : message = "The difference of "; return x-y; break;
		case '*' : message = "The product of "; return x*y; break;
		case '%' : message = "The remainder of "; return int(x)%int(y); break;
		case '/' : if(y != 0)
				  {
				  	message = "The ratio of ";
					return x/y;
					break;
				  }
				  else
				  	message = "Trying to divide by zero!"; break;
		default : message = "That's not a valid operation!"; break;
	}
}

