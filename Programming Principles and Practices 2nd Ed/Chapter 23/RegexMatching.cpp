#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<regex>

int main(void)
{
    std::regex pattern;

    std::string pat;
    std::cout << "Enter regex pattern: ";
    std::getline(std::cin,pat);

    try{
        pattern = pat;
        std::cout << "Pattern: " << pat << '\n';
    } catch(std::regex_error){
        std::cerr << pat << " is not a valid regex\n";
        return 1;
    }

    std::cout << "Now enter lines:\n";
    size_t linenum{1};

    for(std::string line; std::getline(std::cin,line); ++linenum){
        std::smatch matches;
        if(std::regex_search(line, matches, pattern)){
            std::cout << "Line " << linenum << ": " << line << '\n';
            for(size_t i{}; i < matches.size(); ++i)
                std::cout << "\tmatches[" << i << "]: "
                          << matches[i] << '\n';
        }
        else std::cout << "didn't match\n";
    }

    return 0;
}
