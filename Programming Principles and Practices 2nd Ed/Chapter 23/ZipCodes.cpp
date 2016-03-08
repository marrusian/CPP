#include<iostream>
#include<fstream>
#include<string>
#include<regex>

int main(void)
{
    std::ifstream fin{"zipcodes.txt"};
    if(!fin) throw std::runtime_error("Cannot open input file.");
    if(fin.peek()==EOF) throw std::runtime_error("Input file is empty.");

    std::regex pattern{R"(\w{2}\s*\d{5}(–\d{4})?)"};

    int linenum{1};
    for(std::string line; std::getline(fin,line); ++linenum){
        std::smatch matches;
        if(std::regex_search(line, matches, pattern))
            std::cout << linenum << ": " << matches[0] << '\n';
    }

    return 0;
}
