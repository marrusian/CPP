#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<map>
#include<vector>
#include<algorithm>
#include<cctype>
#include<stdexcept>
#include<iterator>

/*  Ideas for re-organizing this program in the future:
 *      a) Remove any facility that isn't primarily concerned with
 *     punctuation - see http://en.wikipedia.org/wiki/Punctuation
 *     for a precise definition of the term and a well-defined set
 *     of punctuation marks - from the Punct_stream.
 *
 *      b) By the aforementioned point, it is implied that any
 *     facility concerning contractions shall not be removed,
 *     as it is closely related to punctuation.
 *     However, there are two options that should be considered:
 *         1. If it is decided to raise the complexity of the
 *         program by elaborating a proper grammar analysis
 *         system (for differentiating between the multiple
 *         extensions of the [-'s] and [-'d] contractions),
 *         an individual Contraction_stream should be designed.
 *
 *         2. If it is decided that such complexity is not needed
 *         and the discrimination between those extensions is not
 *         important, it follows that the program can maintain its
 *         current straightforward extension function (labeled as
 *         "expand_contraction").
 *
 *       c) As a result of point a), any facility concerning plurals
 *       shall be integrated into a Plural_stream. By providing this
 *       encapsulation on the concept of plurals, it can be further
 *       designed as a separate entity, without the need to worry
 *       about the structure and integrity of the Punct_stream.
 *       This is important, because it allows for future expansion
 *       regarding verbs discriminations that naturally leads, again,
 *       to the development of a grammar analysis system.
 *       It also improves the clarity of the program through modularity.
 *
 *       Side&self note: Because the idea of a grammar analysis system
 *          has appeared twice in rather different topics (contractions
 *          and plurality), it may be fundamental to the core of the
 *          program. A thing is certain: it surely involves the use of
 *          grammars (i.e. BNFs). It remains to be looked upon.
 *
 *       d) Because the original goal of the program is to provide
 *       sufficient linguistic manipulation facilities in order to
 *       prepare a text for use in word query programs, all of the
 *       above concepts should be given a common and easy to use
 *       interface that shall reflect the primary idea behind them,
 *       i.e. a Query_stream.
*/

class Punct_stream
{
    public:
        Punct_stream(std::istream& is, const std::string& spaces, bool snstv = true)
            : source{is}, white{spaces}, sens{snstv}
        {
            if(irreg_plurals.empty())
                init_map();
            if(sing_nouns.empty())
                init_vector();
        }

        Punct_stream& operator>>(std::string& s);

        void add_whitespace(char w) {white += w;}
        void erase_whitespace(char w);
        std::string remove_plural(const std::string& word);

        bool& sensitive() {return sens;}
        bool& plural() {return plur;}
        bool& short_forms() {return shform;}
        bool is_whitespace(char w);

        operator bool() {return source.good()|buffer.good();}

    private:
        std::istream& source;
        std::istringstream buffer;
        std::string white;
        bool sens;
        bool shform{true};
        bool plur{true};

        static std::map<std::string,std::string> irreg_plurals;
        static std::vector<std::string> sing_nouns;
        void init_map();
        void init_vector();
};

std::map<std::string,std::string> Punct_stream::irreg_plurals{};
std::vector<std::string> Punct_stream::sing_nouns{};

void Punct_stream::init_map()
{
    std::ifstream fin{"IrregularPlurals.txt"};
    if(!fin) throw std::runtime_error("Cannot open input file for initializing map.");
    for(std::string temp_left, temp_right; fin >> temp_left >> temp_right;)
        irreg_plurals[temp_right] = temp_left;
}

void Punct_stream::init_vector()
{
    std::ifstream fin{"SingularNouns.txt"};
    if(!fin) throw std::runtime_error("Cannot open input file for initializing vector.");
    sing_nouns.insert(sing_nouns.begin(), std::istream_iterator<std::string>{fin},
                                          std::istream_iterator<std::string>{});
}

std::string Punct_stream::remove_plural(const std::string& word)
{
    static constexpr size_t MIN_PLURAL_CHARS = 3;

    if(word.size() > MIN_PLURAL_CHARS){
        //  If word ends in "ss", return it.
        if(word.substr(0,word.size()-2) == "ss")
            return word;

        //  If word has an irregular plural, return its singular counterpart.
        auto p = irreg_plurals.find(word);
        if(p!=irreg_plurals.end())
            return p->second;

        //  If word is a singular noun ending in s, return it.
        auto q = std::lower_bound(sing_nouns.begin(), sing_nouns.end(), word);
        if(q!=sing_nouns.end() && *q==word)
            return word;

        //  If word ends in -ies, change -ies to -y.
        if(word.substr(word.size()-3) == "ies")
            return word.substr(0, word.size()-3) + 'y';

        //  If word ends in -es, cut it.
        if(word.substr(word.size()-2) == "es"){
            std::string prefix1 = word.substr(word.size()-4, 2);
            char prefix2 = prefix1.back();
            if((prefix1=="ch" || prefix1=="sh") || (prefix2=='s' || prefix2=='x' || prefix2=='z'))
                return word.substr(0, word.size()-2);
        }

        // If word ends in -s and contains no apostrophe, cut it.
        if(word.back() == 's')
            if(word.find("\'") == std::string::npos)
                return word.substr(0, word.size()-1);
    }

    return word;
}

bool Punct_stream::is_whitespace(char w)
{
    for(char ch : white)
        if(ch==w) return true;
    return false;
}

void Punct_stream::erase_whitespace(char w)
{
    auto p = std::find(white.begin(), white.end(), w);
    if(p!=white.end())
        white.erase(p);
}

std::string expand_contraction(const std::string& word)
{
    size_t pos = word.find('\'');

    if(pos != std::string::npos){
        std::string temp;
        for(char ch : word) temp += tolower(ch);

        if(temp[pos-1]=='n' && temp[pos+1]=='t'){
            std::string shform = word.substr(0, word.size()-3);
            if(shform != "ca")
                return shform + " not";
            else
                return shform + "nnot";
        }

        if(temp[pos+1]=='s'){
            std::string shform = word.substr(0, word.size()-2);
            if(shform != "let")
                return shform + " is";
            else
                return shform + " us";
        }

        if(temp[pos+1]=='l' && temp[pos+2]=='l')
            return word.substr(0, word.size()-3) + " will";

        if(temp[pos+1]=='r' && temp[pos+2]=='e')
            return word.substr(0, word.size()-3) + " are";

        if(temp[pos+1]=='v' && temp[pos+2]=='e')
            return word.substr(0, word.size()-3) + " have";
    }
    return word;
}

Punct_stream& Punct_stream::operator>>(std::string& s)
{   // The buffer state needs to be saved an restored between operations.
    // Doing so ensures real-time state-check when reading from files
    // (otherwise we would get a premature eof() from the buffer).
    std::ios_base::iostate p = buffer.rdstate();

    while(!(buffer>>s)){
        if(buffer.bad() || !source.good()) return *this;
        buffer.clear();

        std::istringstream iss{};
        std::string line;
        std::getline(source, line);
        iss.str(line);

        std::string parsed_line;
        for(std::string temp; iss >> temp;){
            if(!shform)
                temp = expand_contraction(temp);

            for(auto iter = temp.begin(), iterEnd = temp.end(); iter != iterEnd; ++iter)
                if(is_whitespace(*iter)){
                    temp.erase(iter);
                    --iter;
                }
                else if(!sens)
                    *iter = tolower(*iter);

            if(!plur)
                temp = remove_plural(temp);

            parsed_line += temp;

            for(char x; iss.get(x) && isspace(x); parsed_line += x){}
            iss.unget();
        }

        buffer.str(parsed_line);
    }

    buffer.clear(p);
    return *this;
}

int main(void)
{
    std::cout << "Enter input file name: ";
    std::string iname;
    std::getline(std::cin,iname);

    std::ifstream fin{iname};
    if(!fin) throw std::runtime_error("Cannot open input file \'" + iname + "\'");
    if(fin.peek()==EOF) throw std::runtime_error("Input file \'" + iname + "\' is empty.");

    std::ofstream fout{"customoutput.txt"};

    Punct_stream ps{fin, R"(.:;,-=?'"[]~§“”/\#$%^&*{}<>()!@_)", false};
    ps.plural() = false;
    ps.short_forms() = false;
    for(std::string temp; ps >> temp;)
        fout << temp << '\n';

    return 0;
}

