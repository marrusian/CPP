#include<iostream>
#include<vector>
#include<cstring>

void leaderboard(std::vector<std::string>&, std::vector<int>&);

int main(void)
{
	std::vector<int> scores;
	std::vector<std::string> names;
	
	std::cout << "Please enter a set of name-and-value pairs(Ex : Joe 22) : ";
	leaderboard(names, scores);
	
	for (int i = 0; i < names.size(); i++)
		std::cout << names[i] << ' ' << scores[i] << '\n';
	
	return 0;
}

// Insert name-and-score pairs;
void leaderboard(std::vector<std::string> &nv1, std::vector<int> &sv1) // names/scores vector;
{
	int score = 0;
	std::string p_name; // player name;
	bool duplicate = false;
	
	while (std::cin >> p_name >> score)
	{
		for (int i = 0; i < nv1.size(); i++)
			if(p_name == nv1[i])
			{
				std::cout << "This name is already taken. Try again: ";
				duplicate = true;
				break;
			}
		
		if(!duplicate)
		{
			nv1.emplace_back(p_name);
			sv1.emplace_back(score);
		}
	}
	
	return;	
}



