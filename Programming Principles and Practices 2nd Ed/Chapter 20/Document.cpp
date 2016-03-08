#include<iostream>
#include<vector>
#include<list>
#include<string>

using Line = std::vector<char>;

class Doc_iterator{
        friend void replace(Doc_iterator, Doc_iterator, const std::string&, const std::string&);

    public:
        Doc_iterator(std::list<Line>::iterator ll, Line::iterator pp): ln{ll}, pos{pp} {}

        char& operator*() {return *pos;}
        Doc_iterator& operator++();
        Doc_iterator operator++(int) {auto temp = Doc_iterator{*this}; ++(*this); return temp;}

        bool operator==(const Doc_iterator& other) const
            { return ln==other.ln && pos==other.pos;}
        bool operator!=(const Doc_iterator& other) const
            { return !(*this==other);}

    private:
        std::list<Line>::iterator ln;
        Line::iterator pos;
};

Doc_iterator& Doc_iterator::operator++()
{
    ++pos;
    if(pos==ln->end()){
        ++ln;
        pos = ln->begin();
    }
    return *this;
}

struct Document{
        std::list<Line> lines;
        Document() {lines.push_back(Line{});}

        Doc_iterator begin() {return Doc_iterator{lines.begin(), lines.begin()->begin()};}
        Doc_iterator end()
        {
            auto last = lines.end();
            --last;
            return Doc_iterator{last, last->end()};
        }
};

std::istream& operator>>(std::istream& is, Document& d)
{
    char w = '\0';
    while(is.get(w)){
        d.lines.back().push_back(w);
        if(w == '\n')
            d.lines.push_back(Line{});
    }
    if(d.lines.back().size()) d.lines.push_back(Line{});
    return is;
}

void erase_line(Document& d, size_t n)
{
    if(d.lines.size()<n) return;
    auto p = d.lines.begin();
    std::advance(p,n);
    d.lines.erase(p);
}

Doc_iterator find(Doc_iterator di1, const Doc_iterator& di2, char w)
{
    while(di1!=di2 && *di1!=w) ++di1;
    return di1;
}

bool match(Doc_iterator di1, const Doc_iterator& di2, const std::string& s)
{
    auto sBeg = s.begin();
    auto sEnd = s.end();

    while(sBeg != sEnd && di1 != di2){
        if(*sBeg++ != *di1++) return false;
    }

    return true;
}

Doc_iterator find_txt(Doc_iterator first, Doc_iterator last, const std::string& s)
{
    if(!s.size()) return last;
    char first_char = s[0];
    while(true){
        auto p = find(first, last, first_char);
        if(p==last || match(p, last, s)) return p;
        first = ++p;
    }
}

void replace(Doc_iterator first, Doc_iterator last,
             const std::string& sfind, const std::string& srep)
{
   if(!sfind.size()) return last;
   auto p = first;
   while(true){
        p = find_txt(first, last, sfind);
        if(p==last) return;
        p.ln->erase(p.pos, p.pos+sfind.size());
        p.ln->insert(p.pos, srep.begin(), srep.end());
        first = ++p;
    }
}

size_t char_count(Doc_iterator first, Doc_iterator last)
{
    size_t count{};
    while(first++!=last)
        ++count;

    return count;
}

size_t word_countI(Doc_iterator first, Doc_iterator last)
// "Word" is defined as a whitespace-separated sequence of characters.
{
    size_t count{};
    while(first!=last)
        if(isspace(*first)) ++first;
        else{
            while(isgraph(*first)) ++first;
            ++count;
        }

    return count;
}

size_t word_countII(Doc_iterator first, Doc_iterator last)
// "Word" is defined as a sequence of consecutive alphabetic characters.
{
    size_t count{};
    while(first!=last)
        if(!isalpha(*first)) ++first;
        else{
            while(isalpha(*first)) ++first;
            ++count;
        }

    return count;
}

bool iscustomws(char w, const std::string& whitespace)
{
    for(char x : whitespace)
        if(x == w) return true;

    return false;
}

size_t word_countIII(Doc_iterator first, Doc_iterator last, const std::string& whitespace)
{
    size_t count{};
    while(first!=last)
        if(iscustomws(*first, whitespace)) ++first;
        else{
            while(!iscustomws(*first, whitespace)) ++first;
            ++count;
        }

    return count;
}

int main(void)
{
    Document d;
    std::cin >> d;

    replace(d.begin(), d.end(), "line", "phrase");
    for(char x : d)
        std::cout << x;

    std::cout << char_count(d.begin(), d.end()) << '\n';
    std::cout << word_countI(d.begin(), d.end()) << '\n';
    std::cout << word_countII(d.begin(), d.end()) << '\n';
    std::cout << word_countIII(d.begin(), d.end(), "!.,;\n\t- ") << '\n';

    auto p = find_txt(d.begin(), d.end(), "line");
    if(p==d.end())
        std::cout << "not found\n";
    else
        std::cout << "very found\n";



    return 0;
}
