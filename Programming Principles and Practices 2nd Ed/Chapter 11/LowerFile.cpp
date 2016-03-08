#include<iostream>
#include<fstream>
#include<string>
#include<stdexcept>

int main(void)
try{
  std::string iname;
  std::cout << "Enter input file name: ";
  std::cin >> iname;
  std::ifstream fin{iname};
  if(!fin) throw std::runtime_error("Cannot open input file " + iname);

  fin.peek();
  if(fin.eof())
    throw std::runtime_error("Input file is empty.");

  std::string oname;
  std::cout << "Enter output file name: ";
  std::cin >> oname;
  std::ofstream fout{oname};
  if(!fout) throw std::runtime_error("Cannot open output file " + oname);

  for(char w; fin.get(w); )
  {
      if(isalpha(w))
        w = tolower(w);

      fout << w;
  }


  return 0;
} catch(std::exception &e)
  {
     std::cerr << e.what() << '\n';
     return 1;
  }
