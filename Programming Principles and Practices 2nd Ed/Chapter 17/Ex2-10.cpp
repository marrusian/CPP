#include<iostream>
#include<fstream>

void to_lower(char* s)
{
  if(s)
   for(int i = 0; *(s+i); ++i)
     if(s[i] >= 'A' && s[i] <= 'Z')
       s[i] |= 0x20;
}

char* strdup(const char* s, int SIZE = 0, int SCALE_FACTOR = 1)
{
  if(s)
  {
      if(!SIZE)
          while(s[SIZE])
              ++SIZE;

      char* str = new char[SIZE];
      for(int i = 0, limit = SIZE/SCALE_FACTOR; i < limit; ++i)
        str[i] = s[i];

      return str;
  }

  return (new char{'\0'});
}

const char* findx(const char* s, const char* x)
{
  if(s && x){
    int j = 0;
    const char* occurence{nullptr};

    for(int i = 0; *(s+i); ++i){
        occurence = (s+i);
        while(x[j] == s[i]){
            ++j;
            ++i;
            if(!x[j] || !s[i])
              break;
         }
        if(!x[j])
          return occurence;
        else
          j = 0;
      }
  }

  return nullptr;
}

char* allfs(std::istream& is)
{
  char w = '\0';
  int i = 0;
  int SIZE = 15;
  constexpr int SIZE_SCALE = 2;
  char* charr = new char[SIZE];

  while(is.get(w)){
    if(i == SIZE){
      SIZE *= SIZE_SCALE;
      char* charr2 = strdup(charr, SIZE, SIZE_SCALE);

      delete[] charr;
      charr = charr2;
    }

    charr[i] = w;
    ++i;
  }

  return charr;
}



int main(void)
{
  char str[] = "Hello, world!";
  to_lower(nullptr);
  std::cout << str << '\n';

  char* str2 = strdup(nullptr);
  std::cout << str2;
  delete str2;

  const char* str3 = findx(str, "ll");
  std::cout << str3 << '\n';

  std::ifstream fin{"hs.log"};
  char* dynamicarray = allfs(fin);
  std::cout << dynamicarray << '\n';


  return 0;
}

