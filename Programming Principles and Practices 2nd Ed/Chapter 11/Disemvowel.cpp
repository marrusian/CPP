#include<iostream>
#include<fstream>
#include<string>
#include<stdexcept>

// Removes all vowels from a file (“disemvowels”). For example, Once upon a time! becomes nc pn tm!.
// Surprisingly often, the result is still readable; try it on your friends.

int main(void)
try{

  std::string vowel_set{"aAeEiIoOuU"};

  std::string iname;
  std::cout << "Enter input file name: ";
  std::cin >> iname;

  std::ifstream fin{iname};
  if(!fin) throw std::runtime_error("Cannot open input file " + iname);

  fin.peek();
  if(fin.eof()) throw std::runtime_error("Input file " + iname + " is empty.");

  std::ofstream fout{iname};
  if(!fout) throw std::runtime_error("Cannot open output file " + iname);

  for(char w; fin.get(w); )
      if(vowel_set.find(w) == std::string::npos)
        fout << w;

  return 0;

} catch(std::exception &e){
    std::cerr << e.what() << '\n';
    return 1;
}
