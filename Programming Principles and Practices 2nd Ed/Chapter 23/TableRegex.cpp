#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<regex>
#include<stdexcept>

template<typename Target, typename Source>
Target to(Source arg)
{
    std::stringstream interpreter;
    Target result;

    if(!(interpreter << arg)
            || !(interpreter >> result)
            || !(interpreter >> std::ws).eof())
        throw std::runtime_error("to<>() failed");

    return result;
}

int main(void)
{
    std::ifstream fin{"table.txt"};
    if(!fin) throw std::runtime_error("Cannot open input file.");
    if(fin.peek()==EOF) throw std::runtime_error("Input file is empty.");

    std::string line;
    size_t linenum{1};

    std::regex header{R"(^[\w ]+(\s+[\w ]+)*$)"};             // header line
    std::regex row{R"(^([\w ]+)(\s+\d+)(\s+\d+)(\s+\d+)$)"};  // table line

    if(std::getline(fin,line)){
        std::smatch matches;
        if(!std::regex_match(line, matches, header))
            throw std::runtime_error("The table has no header.");
    }

    // Column totals:
    size_t boys{};
    size_t girls{};

    while(std::getline(fin,line)){
        ++linenum;
        std::smatch matches;
        if(!std::regex_match(line, matches, row))
            throw std::runtime_error("Bad line " + to<std::string,size_t>(linenum));

        if(fin.eof()) std::cout << "Reached EOF\n";

        // Check row:
        size_t curr_boy   = to<size_t,std::string>(matches[2]);
        size_t curr_girl  = to<size_t,std::string>(matches[3]);
        size_t curr_total = to<size_t,std::string>(matches[4]);
        if(curr_boy+curr_girl != curr_total)
            throw std::runtime_error("Bad row sum on line " + to<std::string,size_t>(linenum));

        if(matches[1] == " Alle Klasser"){
            if(curr_boy  != boys)     throw std::runtime_error("Boys don't add up\n");
            if(curr_girl != girls)    throw std::runtime_error("Girls don't add up\n");
            if(!(fin>>std::ws).eof()) throw std::runtime_error("Characters after total line\n");
            return 0;
        }

        // Update totals:
        boys  += curr_boy;
        girls += curr_girl;
    }

    throw std::runtime_error("Didn't find \"Alle Klasser\" line.\n");
}
