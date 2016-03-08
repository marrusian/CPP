#include<iostream>
#include<fstream>
#include<string>
#include<array>
#include<ctime>
#include<stdexcept>

// Write a program that reads a text file and writes out how many characters of each character classification are in the file.

constexpr int ENUM_SIZE = 10;
enum class Char{space, alpha, digit, upper, lower, alnum, control,
                punctuation, printable, graphical};

typedef unsigned int uint;

void classify_char(char w, std::array<uint,ENUM_SIZE>& cs)
{
  if(iscntrl(w))
  {
      cs[int(Char::control)]++;
      if(isspace(w)) cs[int(Char::space)]++;
      return;
  }

  if(w == ' ')
  {
      cs[int(Char::space)]++;
      cs[int(Char::printable)]++;
      return;
  }
  else if(ispunct(w)) cs[int(Char::punctuation)]++;
  else if(isalpha(w))
  {
    cs[int(Char::alpha)]++;
    cs[int(Char::alnum)]++;

    if(isupper(w))
      cs[int(Char::upper)]++;
    else
      cs[int(Char::lower)]++;
  }
  else if(isdigit(w))
  {
      cs[int(Char::digit)]++;
      cs[int(Char::alnum)]++;
  }

  cs[int(Char::printable)]++;
  cs[int(Char::graphical)]++;
}

const std::string& announce_classf(int type)
{
  static std::string space = "space";
  static std::string alpha = "alpha";
  static std::string digit = "digit";
  static std::string upper = "upper";
  static std::string lower = "lower";
  static std::string alnum = "alnum";
  static std::string control = "control";
  static std::string punctuation = "punctuation";
  static std::string printable = "printable";
  static std::string graphical = "graphical";
  static std::string def = "???";

  switch(static_cast<Char>(type))
  {
    case Char::space:       return space;
    case Char::alpha:       return alpha;
    case Char::digit:       return digit;
    case Char::upper:       return upper;
    case Char::lower:       return lower;
    case Char::alnum:       return alnum;
    case Char::control:     return control;
    case Char::punctuation: return punctuation;
    case Char::printable:   return printable;
    case Char::graphical:   return graphical;
    default: return def;
  };
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

  std::array<uint,ENUM_SIZE> classification{0};

  clock_t t1 = clock();
  for(char w; fin.get(w);)
    classify_char(w,classification);

  for(int i = 0; i < ENUM_SIZE; ++i)
    std::cout << announce_classf(i) << ": " << classification[i] << '\n';

  t1 = clock() - t1;
  std::cout << "Elapsed: " << static_cast<double>(t1)/CLOCKS_PER_SEC << std::endl;

  return 0;
} catch(std::exception &e)
{
  std::cerr << e.what() << '\n';
  return 1;
}
