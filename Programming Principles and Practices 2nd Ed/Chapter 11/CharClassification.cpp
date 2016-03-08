#include<iostream>
#include<string>
#include<stdexcept>

// Program that reads strings and for each string outputs the character classification of each character.
// A character can have several classifications.

void specify_chcls(char x)
{
  std::cout << x << ":";

  if(isalpha(x)){
    if(islower(x))
      std::cout << " lower";
    else if(isupper(x))
      std::cout << " upper";

    std::cout << " letter";
  }
  else if(isdigit(x)){
      std::cout << " digit";
  }
  else if(isspace(x) && x != '\n'){
      if(isblank(x))
        std::cout << " blank";

      std::cout << " space";
    }
  else if(ispunct(x))
    std::cout << " punctuation character";
  else if(iscntrl(x))
    std::cout << " control character";
  else
    std::cout << " not ASCII";
}

int main(void)
try{

  std::cout << "Insert words: ";

  for(char w; std::cin.get(w);){
      specify_chcls(w);
      std::cout << '\n';
  }

  return 0;

} catch(std::exception &e){
    std::cerr << e.what() << '\n';
    return 1;
}
