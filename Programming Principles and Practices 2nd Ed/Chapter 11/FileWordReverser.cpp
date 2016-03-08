#include<iostream>
#include<fstream>
#include<string>
#include<forward_list>
#include<stdexcept>

// Reverses the order of words (defined as whitespace-separated strings) in a file.

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

  std::forward_list<std::string> rev;

  char w = '\0';
  for(std::string tempout; fin.get(w);){
      tempout.clear();
      if(!isspace(w)){
          fin.unget();
          fin >> tempout;
      }
      else
        tempout.push_back(w);

      rev.push_front(tempout);
  }

  for(const std::string &s : rev)
    fout << s;

  return 0;
} catch(std::exception &e)
{
  std::cerr << e.what() << '\n';
  return 1;
}
