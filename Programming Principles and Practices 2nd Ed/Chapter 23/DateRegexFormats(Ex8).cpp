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
    if(!(interpreter<<arg)
            || !(interpreter>>result)
            || !(interpreter>>std::ws).eof())
        throw std::runtime_error("to<>() failed.");
    return result;
}

int main(void)
{
    const std::string daysuf{R"((?:st|nd|rd|th)?)"};
    const std::string dd{R"(([0-2]?[0-9]|3[01]))"};
    const std::string mm{R"((0?[0-9]|1[0-2]))"};
    // January, February, March, April, May, June, July, August, September, October, November, December
    const std::string m{R"((Jan(?:uary)?|Feb(?:ruary)?|Mar(?:ch)?|Apr(?:il)?|May|Jun(?:e)?|Jul(?:y)?|Aug(?:ust)?|(?:Sep|Nov|Dec)(?:ember)?|Oct(?:ober)?))"};
    const std::string yy{R"((\d{2,4}))"};
    const std::string pct{R"([\./- ]?)"};

    std::ifstream fin{"timedates.txt"};
    if(!fin) throw std::runtime_error("Cannot open input file.");
    if(fin.peek()==EOF) throw std::runtime_error("Input file is empty.");

    //                                    ~population(in millions)
    std::regex ddmmyy{dd+pct+mm+pct+yy};  // 3420
    std::regex yymmdd{yy+pct+mm+pct+dd};  // 1660
    std::regex mmddyy{mm+pct+dd+pct+yy};  // 320                 
    std::regex mddyy{m+pct+dd+", "+yy, std::regex::flag_type::icase};	// e.g. Jan 15, 1994
    std::regex mdddaysuf{m+pct+dd+daysuf, std::regex::flag_type::icase};// e.g. Mar 21th

    size_t linenum{1};
    for(std::string line; std::getline(fin,line); ++linenum){
        std::smatch matches;
        if(std::regex_search(line, matches, mdddaysuf)){
            std::cout << "Date found on line " << to<std::string,size_t>(linenum)
                                               << ": " << matches[0] << '\n';
        }
    }
    return 0;
}
