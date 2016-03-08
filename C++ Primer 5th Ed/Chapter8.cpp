#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(int argc, char *argv[])
{
    std::vector<std::string> lines;
    std::string line;
    std::ifstream ifs;
    for(char **p = argv+1; p < argv+argc; ++p) {
        ifs.open(*p);
        if(!ifs)
            perror("Cannot open file");
        while(getline(ifs, line))
            lines.push_back(line);
        if(ifs.bad())
            perror("Corrupted stream");
        ifs.close();
    }

    for(const std::string& str : lines)
        std::cout << str << "\n";
    std::cout << std::flush;

    return 0;
}