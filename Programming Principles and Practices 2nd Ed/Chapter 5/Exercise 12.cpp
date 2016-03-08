#include<iostream>
#include<vector>
#include<random>
#include<chrono>
#include<stdexcept>
#include<cmath>
#include<deque>
#include<cstring>

// Error handler
void error(std::string);

// Main functions
void generate_sequence(std::vector<int>&, int);
void start_message(int&);
int check_input(double&);
std::deque<int> make_deck(int, int); // Convert inputed integer to vector;
std::pair<int, int> test_guess(std::deque<int>&, std::vector<int>&, int);
bool check_score(std::pair<int,int>&);
bool restart_round(void);

// Global Constants
const int REMOVE_DIGIT = 10;
const int MAX_BULLS = 4;
const int CHECK = -1;
const int NR_OF_DIGITS = 4;

// Global Timer
std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

int main(void)
try{
	std::vector<int> stack;
	std::deque<int> g_deck; // guess deque;
	int guess = 0, round = 1;
	double ckint; // check integer;
	std::pair<int, int> score(0, 0);
	
	generate_sequence(stack, NR_OF_DIGITS);
	
	start_message(round);
	while (true)
	{
		guess = check_input(ckint);
		g_deck = make_deck(guess, NR_OF_DIGITS);
		
		score = test_guess(g_deck, stack, NR_OF_DIGITS);
	
		if(check_score(score))
		{
			if(restart_round())
			{
				generate_sequence(stack, NR_OF_DIGITS);
				score = std::make_pair(0,0);
				start_message(round);
			}
			else
			{
				std::cout << "Goodbye!";
				break;
			}
		}	
	}
	
	return 0;
}catch(std::exception &estr)
{
	std::cerr << "Error: " << estr.what() << '\n';
	return 1;
}

void error(std::string er)
{
	throw std::runtime_error(er);
}

void generate_sequence(std::vector<int> &stack, int d_number)
{
	std::chrono::system_clock::duration d = std::chrono::system_clock::now() - start;
	unsigned seed = (std::chrono::duration_cast<std::chrono::nanoseconds>(d)).count();
	std::minstd_rand0 generator(seed);
	std::uniform_int_distribution<int> distribution(0, 9);
	
	for (int i = 0; i < d_number; i++)
	{
		stack.insert(stack.begin() + i, distribution(generator));
		if((i == 0) && (stack[i] == 0))
		{
			i--;
			continue;
		}
	}
	
	return;
}

void start_message(int &round_number)
{
	std::cout << "Round " << round_number << ". Guess a four digit number: ";
	round_number++;
	
	return;
}

int check_input(double &numb)
{
	while(true)
	{
		if(!(std::cin >> numb))
			error("Invalid character input, only integers are allowed. Terminating!");
		else if(numb != int(numb))
			error("Floating-point numbers are not allowed. Terminating!");
	
		int d_number = log10(numb) + 1; // digits number;
		if(d_number != NR_OF_DIGITS)
		{
			std::cout << "Your guess must have " << NR_OF_DIGITS << " digits."
					  << " Try again: ";
			continue;
		}
		
		return numb;	
	}
}

std::deque<int> make_deck(int number, int size)
{	
	std::deque<int> v;
	for (int i = size-1; i >= 0; i--)
		{
			v.emplace_front(number%10);
			number /= REMOVE_DIGIT;
		}
	
	return v;
}

std::pair<int,int> test_guess(std::deque<int> &guess, std::vector<int> &stack, int size)
{
	int bull = 0;
	int cow = 0;
	std::vector<int> stack_copy = stack;
	
	// Check for bulls;
	for (int i = 0; i < size; i++)
		if(guess[i] == stack_copy[i])
			{
				bull++;
				stack_copy[i] = CHECK;
				guess[i] = CHECK-1;	// if bull, mark out value;
			}
	// Now check for the rest;		
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)		
			if((guess[i] == stack_copy[j]))
			{
				cow++;
				stack_copy[j] = CHECK;
				break;	// don't count the same digit multiple times;
			}
		
	return std::make_pair(bull, cow);
}

bool check_score(std::pair<int,int> &sc)
{
	std::cout << sc.first << " bull(s) and " << sc.second << " cow(s)\n";
	if(sc.first == MAX_BULLS)
	{
		std::cout << "\nCongratulations! You guessed right!\n";
		return true;
	}
	else
	{
		std::cout << "\nTry another guess: ";	
		return false;
	}
}

bool restart_round(void)
{
	char answer = '\0';
	std::cout << "\nWant to play another round ? (y/n): ";
		std::cin >> answer;
	
	switch(answer)
	{
		case 'Y' :
		case 'y' : return true;
		case 'N' :
		case 'n' : return false;
	}
}
