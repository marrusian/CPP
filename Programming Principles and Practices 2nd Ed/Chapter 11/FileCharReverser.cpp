#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stdexcept>

// Reverses the order of characters in a text file.

int main(void)
try{
  std::string iname;
  std::cout << "Enter input file name: ";
  std::cin >> iname;

  std::ifstream fin{iname};
  if(!fin) throw std::runtime_error("Cannot open input file " + iname);

  fin.peek();
  if(fin.eof()) throw std::runtime_error("Input file " + iname + " is empty.");

  std::string oname;
  for(int i = 0; iname[i] != '.'; ++i)
    oname.push_back(iname[i]);
  oname += "Reversed.txt";

  std::ofstream fout{oname};
  if(!fout) throw std::runtime_error("Cannot open output file " + oname);

  char w = '\0';
  for(std::string tempin, tempout; fin.get(w);){
      if(!isspace(w)){
          fin.unget();
          tempout.clear();
          fin >> tempin;
          for(int i = tempin.length() - 1; i >= 0; --i)
            tempout.push_back(tempin[i]);
          fout << tempout;
      }
      else
        fout << w;
  }

  return 0;
} catch(std::exception &e)
{
  std::cerr << e.what() << '\n';
  return 1;
}
