#include<iostream>
#include<cstring>
#include<vector>

// Functions
double arthm(double&, double&, char&);
int get_number(void);

// Global Variables
std::vector<std::string> wdigit = {"zero", "one", "two", "three", "four", "five",
								  "six", "seven", "eight", "nine"}; // wdigit = worded digit;
std::string message;
bool flag = true;


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
	while (true)
	{
		val1 = get_number();
		cin >> op;
		val2 = get_number();
		
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
		
		flag = true;
	}
	
	return 0;
}

int get_number(void)
{
	double val;
	if(std::cin >> val)
		return val;
	else
	{
		std::cin.clear();
		std::string s;
		std::cin >> s;
		for (int i = 0; i < wdigit.size(); i++)
		{
			if(s == wdigit[i])
			{
				val = i;
				return val;
			}
			else if(i == wdigit.size() - 1)
			{
				message = "That's not a spelled-out single digit!";
				flag = false;
			}	
		}
		
	}
}

double arthm(double &x, double &y, char &symb)
{	
	if(flag)
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

