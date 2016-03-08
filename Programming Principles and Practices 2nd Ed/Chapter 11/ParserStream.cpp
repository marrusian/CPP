#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

class Punct_stream
{
  public:
    Punct_stream(std::istream& is): source{is}, sensitive{true}{}

    void whitespace(const std::string& s){white = s;}
    void add_white(char c){white += c;}
    void case_sensitive(bool b){sensitive = b;}

    bool is_whitespace(char) const;
    bool is_case_sensitive() const {return sensitive;}

    Punct_stream& operator>>(std::string& s);
    operator bool() {return !(source.fail() || source.bad()) && source.good();}
  private:
    std::istream& source;
    std::istringstream buffer;
    std::string white;
    bool sensitive;
};

Punct_stream& Punct_stream::operator>>(std::string& s)
{
    while(!(buffer >> s))
    {
        if(buffer.bad() || !source.good()) return *this;
        buffer.clear();

        std::string line;
        std::getline(source,line);

        for(char& c : line)
            if(is_whitespace(c))
              c = ' ';
            else if(!sensitive && isalpha(c))
              c = tolower(c);

        buffer.str(line);
    }

    return *this;
}

bool Punct_stream::is_whitespace(char c) const
{
  for(char ch : white)
    if(c == ch) return true;

  return false;
}

using std::cout;
using std::cin;

int main(void)
{
    Punct_stream ps{cin};
    ps.whitespace(";:,.?!()\"{}<>/&$@#%^*|~");
    ps.case_sensitive(false);

    std::cout << "Enter words: \n";
    std::vector<std::string> vs;
    for(std::string word; ps >> word; vs.push_back(word)){}

    std::stable_sort(vs.begin(), vs.end());
    for(int i = 0, limit = vs.size(); i < limit; ++i)
      if(i == 0 || vs[i] != vs[i-1])
        std::cout << vs[i] << '\n';

  return 0;
}
