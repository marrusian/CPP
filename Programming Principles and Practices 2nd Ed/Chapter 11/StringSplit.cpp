#include<iostream>
#include<sstream>
#include<string>
#include<vector>

// Returns a vector of whitespace-separated substrings from the argument s,
// where whitespace is defined as “ordinary whitespace” plus the characters in w.

std::vector<std::string> split(const std::string& s, const std::string& w)
{
  std::string parse{s};
  for(char& ch : parse)
    if(w.find(ch) != std::string::npos)
      ch = ' ';

  std::istringstream sin{parse};
  std::vector<std::string> substrs;
  for(std::string temp; sin >> temp; substrs.push_back(temp)){}

  return substrs;
}

int main(void)
{



  return 0;
}
