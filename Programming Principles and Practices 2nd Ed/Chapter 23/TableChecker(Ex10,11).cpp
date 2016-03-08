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

    std::regex header{R"(^[\w ]+(\s+[\w ]+)*$)"};                     // header line
    std::regex row{R"((^\s+(\d*)[\w ]+)(\s+\d+)(\s+\d+)(\s+\d+)$)"};  // table line

    std::string head;
    if(std::getline(fin,line)){
        std::smatch matches;
        if(!std::regex_match(line, matches, header))
            throw std::runtime_error("The table has no header.");
        head = matches[0];
    }

    // For writing a table with the years merged.
    std::ofstream fout{"tableym.txt"};
    if(!fout) throw std::runtime_error("Cannot open output file.");
    struct Year_klasse{
        size_t drenge{};
        size_t piger{};
        size_t elialt{};
    };
    constexpr size_t CLASSES = 11;
    std::vector<Year_klasse> yk(CLASSES);

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
        size_t curr_boy   = to<size_t,std::string>(matches[3]);
        size_t curr_girl  = to<size_t,std::string>(matches[4]);
        size_t curr_total = to<size_t,std::string>(matches[5]);
        if(curr_boy+curr_girl != curr_total)
            throw std::runtime_error("Bad row sum on line " + to<std::string,size_t>(linenum));

        // Merge classes:
        if(!matches.str(2).empty()){
            size_t year = to<size_t,std::string>(matches[2]);
            yk[year].drenge += curr_boy;
            yk[year].piger  += curr_girl;
            yk[year].elialt += curr_boy+curr_girl;
        }

        if(matches[1] == " Alle Klasser"){
            if(curr_boy  != boys)     throw std::runtime_error("Boys don't add up\n");
            if(curr_girl != girls)    throw std::runtime_error("Girls don't add up\n");
            if(!(fin>>std::ws).eof()) throw std::runtime_error("Characters after total line\n");
        }

        // Update totals:
        boys  += curr_boy;
        girls += curr_girl;
    }

    fout << head << " \t" << "PREVIOUS YEAR DIFFERENCE" << '\n';
    for(size_t i{}; i < yk.size(); ++i){
        fout << ' ' << i << "\t\t"
             << yk[i].drenge << "\t\t"
             << yk[i].piger  << "\t\t"
             << yk[i].elialt << "\t\t";
        if(i)
            fout << static_cast<ssize_t>(yk[i].elialt)-static_cast<ssize_t>(yk[i-1].elialt);
        else fout << i;

        fout << '\n';
    }
}
