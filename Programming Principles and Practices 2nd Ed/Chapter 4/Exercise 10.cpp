#include<iostream>
#include<vector>
#include<cstring>
#include<random>

// Constants
const int ROCK = 0;
const int SCISS = 1;
const int PAPER = 2;

// Globals
std::vector<std::string> av_ch = {"Rock", "Scissors", "Paper"}; // available choices
int count1 = 0, count2 = 0, draws = 0;

// Functions
void message(int&);
void evaluate(char&, int&);
void winner(const int&, const int&);

int main(void)
{
	std::string user_ch; // user choice;
	int comp_ch; // computer choice;
	
	
	std::default_random_engine generator;
	std::poisson_distribution<int> distribution(1);

	while (std::cin >> user_ch)
	{
		comp_ch = distribution(generator);
		evaluate(user_ch.front(), comp_ch);
	}

	return 0;
}

void message(int &id)
{
	std::cout << "Comp has chosen " << av_ch[id] << ". ";
	return ;
}

void evaluate(char &u_roll, int &c_roll)
{
	
	switch(u_roll)
	{
		case 'r' :
		case 'R' : message(c_roll); winner(ROCK, c_roll); break;
		case 'p' :
		case 'P' : message(c_roll); winner(PAPER, c_roll); break;
		case 's' :
		case 'S' : message(c_roll); winner(SCISS, c_roll); break;
		default : std::cout << "That's not a valid choice!. Try again: ";
	}
	
	return;
}

void winner(const int &u, const int &c) // user - computer;
{
	if(u == c)
	{
		std::cout << "Tie !\n";
		draws++;		
	}
	else if((u == 0) && (c == 1))
	{
		std::cout << "You won!\n";
		count1++;
	}
	else if((u == 1) && (c == 2))
	{
		std::cout << "You won!\n";
		count1++;
	}
	else if((u == 2) && (c == 0))
	{
		std::cout << "You won!\n";
		count1++;
	}
	else
	{
		std::cout << "You lose!\n";
		count2++;
	}
	
	return;
}
