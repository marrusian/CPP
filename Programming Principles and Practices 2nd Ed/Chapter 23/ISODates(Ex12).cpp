#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<regex>
#include<stdexcept>
#include<array>

/*
 *  The ISO_date functor can be used to convert any kind
 * of date format to the ISO yyyy-mm-dd date format.
*/

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

class ISO_date{
    public:
        ISO_date()
        {
            months =
            {
                "january",  "february",   "march",
                "april",    "may",        "june",
                "july",     "august",     "september",
                "november", "october",    "december"
            };

            days =
            {
                "monday", "tuesday", "wednesday", "thursday",
                "friday", "saturday","sunday"
            };
        }
        std::string operator()(const std::string& year,
                               const std::string& month,
                               const std::string& day);
    private:
        std::array<std::string,12> months;
        std::array<std::string,7> days;
        template<typename Array>
        std::string to_date(const std::string& str, const Array& arr);
};

template<typename Array>
std::string ISO_date::to_date(const std::string& str, const Array& arr)
{
    if(!str.empty()){
        if(isdigit(str.front())){
            if(to<size_t,std::string>(str)<10 && str.front()!='0')
                return "0"+str;
            return str;
        }

        size_t arrEnd{arr.size()};
        size_t itemEnd{};
        size_t daySize{};

        for(size_t i{}; i < arrEnd; ++i){
            if(str.size() > arr[i].size())
                itemEnd = arr[i].size();
            else
                itemEnd = str.size();

            daySize = str.size();
            size_t j{};
            while(j < itemEnd && tolower(str[j])==arr[i][j]) ++j;

            if(j==daySize){
                if(i+1<10)
                    return "0"+to<std::string,size_t>(i+1);
                return to<std::string,size_t>(i+1);
            }
        }
    }

    return str;
}

std::string ISO_date::operator()(const std::string& year,
                                 const std::string& month,
                                 const std::string& day)
{
    return std::string{year+'-'+to_date(month,months)+'-'+to_date(day,days)};
}

int main(void)
{
    const std::string daysuf{R"((?:st|nd|rd|th)?)"};
    const std::string dd{R"(([0-2]?[0-9]|3[01]))"};
    const std::string mm{R"((0?[0-9]|1[0-2]))"};
    // January, February, March, April, May, June, July, August, September, October, November, December
    const std::string m{R"((Jan(?:uary)?|Feb(?:ruary)?|Mar(?:ch)?|Apr(?:il)?|May|Jun(?:e)?|Jul(?:y)?|Aug(?:ust)?|(?:Sep|Nov|Dec)(?:ember)?|Oct(?:ober)?))"};
    const std::string yy{R"((\d{2,4}))"};
    const std::string pct{R"([\./- ])"};

    std::ifstream fin{"timedates.txt"};
    if(!fin) throw std::runtime_error("Cannot open input file.");
    if(fin.peek()==EOF) throw std::runtime_error("Input file is empty.");

    //                                    ~population(in millions)
    std::regex ddmmyy{dd+pct+mm+pct+yy};  // 3420
    std::regex yymmdd{yy+pct+mm+pct+dd};  // 1660
    std::regex mmddyy{mm+pct+dd+pct+yy};  // 320
    std::regex mddyy{m+pct+dd+", "+yy,    std::regex::flag_type::icase};// e.g. Jan 15, 1994
    std::regex mdddaysuf{m+pct+dd+daysuf, std::regex::flag_type::icase};// e.g. Mar 21th

    std::ofstream fout{"timedatesISO.txt"};
    if(!fout) throw std::runtime_error("Cannot open output file.");
    ISO_date isd{};

    size_t linenum{1};
    for(std::string line; std::getline(fin,line); ++linenum){
        std::smatch matches;
        if(std::regex_search(line, matches, mdddaysuf)){
            std::cout << "Date found on line " << to<std::string,size_t>(linenum)
                                               << ": " << matches[0] << '\n';
            fout << matches.prefix() << isd("1947",matches[1],matches[2]) << matches.suffix() << '\n';
        }


    }
    return 0;
}
