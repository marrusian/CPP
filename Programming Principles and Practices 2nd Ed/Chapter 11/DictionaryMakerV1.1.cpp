#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<forward_list>
#include<stdexcept>

// Replaces punctuation with whitespace.
// Considers . (dot), ; (semicolon), , (comma), ? (question mark),' (single quote) punctuation characters.
// Doesn’t modify characters within a pair of double quotes (").
// Replaces don't with do not, can't with cannot, etc.;
// Leaves hyphens within words intact.
// Converts all characters to lower case.

constexpr int ONE_LETTER = 1;

void short_to_long(std::string& s, char ch)
{
  std::size_t pos = s.find(ch);

  if(s[pos-1] == 'n' && s[pos+1] == 't'){
       s.erase(pos-1);
       if(s != "ca")
        s += " not";
       else
        s += "nnot";
  }
  else if(s[pos+1] == 's'){
      s.erase(pos);
      if(s != "let")
        s += " is";
      else
        s += " us";
  }
  else if(s[pos+1] == 'l' && s[pos+2] == 'l'){
      s.erase(pos);
      s += " will";
  }
  else if(s[pos+1] == 'r' && s[pos+2] == 'e'){
      s.erase(pos);
      s += " are";
  }
  else if(s[pos+1] == 'v' && s[pos+2] == 'e'){
      s.erase(pos);
      s += " have";
  }
  else
    for (char& w : s)
      if (w == '\'') w = ' ';
}

int main(void)
try{

  std::string whitespaces{".;,-=?':[]/\"~§“”#$%^&*{}<>()!@+-_0123456789"};
  std::string vowels{"aeiou"};

  std::string iname;
  std::cout << "Enter input file name: ";

  std::cin >> iname;
  std::ifstream fin{iname};
  if(!fin) throw std::runtime_error("Can't open input file " + iname);

  fin.peek();
  if(fin.eof()) throw std::runtime_error("Input file " + iname + " is empty.");

  std::forward_list<std::string> dictionary;
  for(std::string temp; fin >> temp;)// std::cout << temp << static_cast<char>(std::cin.get()))
  {
      for(auto iter = temp.begin(), iterEnd = temp.end(); iter != iterEnd; ++iter)
        if(isupper(*iter))
          *iter = tolower(*iter);
        else
          if((whitespaces.find(*iter)) != std::string::npos)
          {
            if(*iter == '-' && isalpha(*(iter-1)) && isalpha(*(iter+1)))
              continue;
            else if(*iter == '\'')
              short_to_long(temp, *iter);
            else
              *iter = ' ';
          }

      for(std::istringstream sin{temp}; sin >> temp;)
        if(temp.length() > ONE_LETTER)
          for(char ch : temp)
            if(vowels.find(ch) != std::string::npos){
              dictionary.push_front(temp);
              break;
            }
   }


  dictionary.sort();
  dictionary.unique();
  for(auto iter = dictionary.begin(), iterEnd = dictionary.end(); iter != iterEnd; ++iter)
      std::cout << *iter << '\n';


  return 0;

} catch(std::exception &e){
    std::cerr << e.what() << '\n';
    return 1;
}
