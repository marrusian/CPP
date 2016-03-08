#include<iostream>
#include<string>
#include<stdexcept>

// Replaces punctuation with whitespace.
// Considers . (dot), ; (semicolon), , (comma), ? (question mark), - (dash), ' (single quote) punctuation characters.
// Doesn’t modify characters within a pair of double quotes (").

int main(void)
try{

  std::string whitespaces{".;,?-'"};
  bool modify{true};

  for(char w; std::cin.get(w); std::cout << w)
    if(w == '\"')
      modify ^= 1;
    else
      if(modify && (whitespaces.find(w) != std::string::npos))
        w = ' ';

  return 0;

} catch(std::exception &e){
    std::cerr << e.what() << '\n';
    return 1;
}
