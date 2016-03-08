#include<iostream>
#include<fstream>
#include<string>
#include<regex>

int main(void)
{
    std::string pattern;
    do{
        std::cout << "Enter input file name: ";
        std::string iname;
        std::getline(std::cin,iname);

        std::ifstream fin{iname};
        if(!fin) throw std::runtime_error("Cannot open input file \"" + iname + "\"");
        if(fin.peek()==EOF) throw std::runtime_error("Input file \"" + iname + "\" is empty.");

        std::cout << "Enter the regex pattern to search for: ";
        std::getline(std::cin,pattern);
        std::regex rgx{pattern};

        size_t linenum{1};
        std::cout << std::endl;
        for(std::string line; std::getline(fin,line); ++linenum){
            std::smatch matches;
            if(std::regex_search(line, matches, rgx))
                std::cout << "Line " << linenum << ": "
                                     << matches[0] << '\n';
        }
    } while(!pattern.empty());

    return 0;
}
