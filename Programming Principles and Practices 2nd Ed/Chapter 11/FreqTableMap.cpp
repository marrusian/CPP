#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<stdexcept>
#include<ctime>

// Write a program that reads a text file and writes out how many characters of each character classification are in the file.

typedef unsigned int uint;

void classify_char(char w, std::map<std::string,uint>& cs)
{
  if(iscntrl(w))
  {
      cs["control"]++;
      if(isspace(w)) cs["space"]++;
      return;
  }

  if(w == ' ')
  {
      cs["space"]++;
      cs["printable"]++;
      return;
  }
  else if(ispunct(w)) cs["punctuation"]++;
  else if(isalpha(w))
  {
    cs["alpha"]++;
    cs["alnum"]++;

    if(isupper(w))
      cs["upper"]++;
    else
      cs["lower"]++;
  }
  else if(isdigit(w))
  {
      cs["digit"]++;
      cs["alnum"]++;
  }

  cs["printable"]++;
  cs["graphical"]++;
}

int main(void)
try{
  std::string iname;
  std::cout << "Enter input file name: ";
  std::cin >> iname;

  std::ifstream fin{iname};
  if(!fin) throw std::runtime_error("Cannot open input file " + iname);

  fin.peek();
  if(fin.eof()) throw std::runtime_error("Input file " + iname + " is empty.");

  std::map<std::string, uint> classification = {{"space",0},{"alpha",0},{"digit",0},{"upper",0},
                                               {"lower",0},{"alnum",0},{"control",0},{"punctuation",0},
                                               {"printable",0},{"graphical",0}};

  clock_t t1 = clock();
  for(char w; fin.get(w);)
    classify_char(w,classification);

  for(const std::pair<std::string,uint>& p : classification)
    std::cout << p.first << ": " << p.second << '\n';

  t1 = clock() - t1;
  std::cout << "Elapsed: " << static_cast<double>(t1)/CLOCKS_PER_SEC << std::endl;

  return 0;
} catch(std::exception &e)
{
  std::cerr << e.what() << '\n';
  return 1;
}
