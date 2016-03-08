#include<iostream>
#include<string>
#include<limits>

typedef long unsigned int luint;

luint strlen(const char* s)
{
    if(s){
        luint size{};
        while(*s++)
            ++size;

        return size;
    }

    return 0;
}

char* strdup(const char* s, luint SIZE = 0, const int S_FACTOR = 1)
{
    if(s){
        if(!SIZE){
            SIZE = strlen(s);
            ++SIZE;         // Make space for the null-byte.
        }

        char* sn = new char[SIZE]{};
        for(luint i = 0, limit = SIZE/S_FACTOR; i < limit; ++i)
            *(sn + i) = *(s + i);

        return sn;
    }
    return new char{'\0'};
}

char* findx(const char* s, const char* x)
{
  if(s && x){
    int j = 0;
    const char* occurence{nullptr};

    while(*s){
        while(x[j] == *s++)
            if(!x[++j]){
                occurence = s - j;
                return const_cast<char*>(occurence);
            }

        j = 0;
    }
  }

  return nullptr;
}

int strcmp(const char* s1, const char* s2)
{
    if(s1 && s2){
       while(*s1 == *s2++)
           if(!(*s1++))
               return 0;

       return *s1-(*--s2);
    }

    return 0;
}

char* strcat(char* s, const char* s2)
{
    if(s){
        int i = 0;
        while(s[i]) i++;
        while(*s2)
            s[i++] = *s2++;
        return s;
    }

    return nullptr;
}

bool is_palindrome(const std::string& s)
{
    std::string temp;
    for(int i = s.size()-1; i >= 0; --i)
        temp.push_back(s[i]);

    for(int i = 0; s[i]; ++i)
        if(temp[i] != s[i]) return false;

    return true;
}

bool is_palindrome(const char s[], int n)
{
    char temp[n];
    for(int i = n-1, j = 0; i >= 0; --i, ++j)
        temp[j] = s[i];

    for(int i = 0; s[i]; ++i)
        if(temp[i] != s[i]) return false;

    return true;
}

bool is_palindrome(const char* first, const char* last)
{
    int length = last-first+1;
    char temp[length+1];
    int i = 0;
    while(i <= length){
        temp[i] = last[-i];
        ++i;
    }

    i = 0;
    while(first <= last)
        if(*first++ != temp[i++]) return false;

    return true;
}

char* read_string(std::istream& is)
{
    luint SIZE = 15;
    constexpr int SCALE_FACTOR = 2;
    char* s = new char[SIZE]{};
    char w = '\0';
    for(luint i = 0; is.get(w); ++i){
        if(i == SIZE){
            SIZE *= SCALE_FACTOR;
            char* charr2 = strdup(s,SIZE,SCALE_FACTOR);
            delete[] s;
            s = charr2;
        }

        s[i] = w;
    }

    is.clear();
    return s;
}

int main(void)
{
    for(char* word; word = read_string(std::cin); delete[] word){
        std::cout << std::endl;
        std::cout << word << " is";
        if(!is_palindrome(word,strlen(word))) std::cout << " not";
        std::cout << " a palindrome\n";
    }


    return 0;
}
