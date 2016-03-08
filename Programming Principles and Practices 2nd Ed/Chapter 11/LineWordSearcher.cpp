#include<iostream>
#include<fstream>
#include<string>
#include<stdexcept>

// Given a file name and a word outputs each line that contains that word together with the line number.

int main(void)
try{

  std::string iname;
  std::cout << "Enter input file name: ";
  std::cin >> iname;
  std::ifstream fin{iname};
  if(!fin) throw std::runtime_error("Cannot open input file " + iname);

  fin.peek();
  if(fin.eof()) throw std::runtime_error("Input file " + iname + " is empty.");

  std::string word;
  std::cout << "Enter the word to search for: ";
  std::cin >> word;

  std::string line;
  for(int i = 1; std::getline(fin,line); ++i)
      if(line.find(word) != std::string::npos)
        std::cout << i << ' ' << line << '\n';

  return 0;

} catch(std::exception &e){
    std::cerr << e.what() << '\n';
    return 1;
}
