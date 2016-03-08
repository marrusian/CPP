#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <algorithm>    
#include <map>
#include <set>
#include <string>
#include <iterator>
#include <cctype>
#include <limits>

using std::cout; using std::cin; using std::endl;

void f114(void)
{
    std::iostream::iostate oldState = cin.rdstate();
    cin.clear();

    std::map<std::string, size_t> word_count;
    std::set<std::string> exclude{"the", "but", "and", "or", "a", "an"};

    cout << "Insert words: \n";
    std::string word;
    while(cin >> word) {
        auto w = std::remove_if(word.begin(), word.end(), ispunct);
        word.erase(w, word.end());

        std::for_each(word.begin(), word.end(), [](char& ch) {ch = tolower(ch);});
        if(exclude.find(word) == exclude.end())
            ++word_count[word];
    }

    for(const auto& x : word_count)
        cout << x.first << " occurs " << x.second << " time(s) " << endl;

    cin.clear(oldState);
}

std::string normalize(const std::string& str)
{
    std::string word;
    word.reserve(20);

    std::remove_copy_if(str.cbegin(), str.cend(),
                       std::back_inserter(word),
                       [](char ch) {return isspace(ch) || ispunct(ch);});
    std::for_each(word.begin(), word.end(), [](char& ch) {ch = tolower(ch);});

    return word;
}

bool comp_names(const std::string& str1, const std::string& str2)
{
    return normalize(str1) < normalize(str2);
}

void f117menu(std::ostream& os)
{
    os << "\n1. Add family name\n"
       << "2. Add new children to existing family\n";
}

void f117add_family(std::map<std::string, std::vector<std::string>, decltype(comp_names)*>& mp)
{
    std::string name;

    cout << "Insert name: ";
    while(getline(cin >> std::ws, name)) {
        mp[name];
        cout << "Insert name: ";
    }

    if(cin.eof())
        cin.clear();
}

void f117add_children(std::map<std::string, std::vector<std::string>, decltype(comp_names)*>& mp)
{
    std::string children, family;

    cout << "Insert family name: ";
    getline(cin >> std::ws, family);

    if(mp.find(family) == mp.end())
        cout << "There is no such family name\n";
    else {
        cout << "Insert child name: ";
        while(getline(cin >> std::ws, children)){
            mp[family].emplace_back(children);
            cout << "Insert child name: ";

            if(cin.eof())
                cin.clear();
        }
    }
}

void f117(void)
{
    std::iostream::iostate oldState = cin.rdstate();
    cin.clear();

    std::map<std::string, std::vector<std::string>, decltype(comp_names)*> families(comp_names);
    std::string option;

    f117menu(cout);
    while(cin >> option) {
        try{
            switch(stoi(option)) {
                case 1 : f117add_family(families); break;
                case 2 : f117add_children(families); break;
            }
        } catch (std::invalid_argument& err) {
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        f117menu(cout);
    }

    for(const auto& x : families) {
        cout << x.first << ": ";
        for(const auto& y : x.second)
            cout << y << " | ";
        cout << endl;
    }

    cin.clear(oldState);
}

void f1112(void)
{
    std::iostream::iostate oldState = cin.rdstate();
    cin.clear();

    std::string str;
    int val;
    std::vector<std::pair<std::string,int>> prs;

    cout << "Insert (string, int) pairs: \n";
    while(cin >> str >> val)
        prs.emplace_back(str, val);

    for(const auto& x : prs)
        cout << x.first << " " << x.second << endl;

    cin.clear(oldState);
}

std::pair<std::string, int> f1113a(const std::vector<std::string>& v)
{
    if(!v.empty())
        return std::pair<std::string, int>(v.back(), v.back().size());
    else
        return std::pair<std::string, int>();
}

std::pair<std::string, int> f1113b(const std::vector<std::string>& v)
{
    if(!v.empty())
        return {v.back(), v.back().size()};
    else
        return {};
}

std::pair<std::string, int> f1113c(const std::vector<std::string>& v)
{
    if(!v.empty())
        return std::make_pair(v.back(), v.back().size());
    else
        return std::make_pair("", 0);
}

void f1120(void)
{
    std::iostream::iostate oldState = cin.rdstate();
    cin.clear();

    std::map<std::string, size_t> word_count;
    std::set<std::string> exclude{"the", "but", "and", "or", "a", "an"};

    cout << "Insert words: \n";
    std::string word;
    while(cin >> word) {
        auto w = std::remove_if(word.begin(), word.end(), ispunct);
        word.erase(w, word.end());

        std::for_each(word.begin(), word.end(), [](char& ch) {ch = tolower(ch);});
        if(exclude.find(word) == exclude.end()) {
            ++word_count.emplace(word, 0).first->second;
            // auto ret = word_count.emplace(word, 1);
            // if(!ret.second)
            //     ++ret.first->second;
        }
    }

    for(const auto& x : word_count)
        cout << x.first << " occurs " << x.second << " time(s) " << endl;

    cin.clear(oldState);  
}

void f1122(void)
{
    std::map<std::string, std::vector<int>> mp;
    std::pair<std::map<std::string, std::vector<int>>::iterator, bool> ret = mp.insert(std::pair<std::string, std::vector<int>>("", {}));
}

template <typename T, typename U>
void ff126(std::map<T,U>& mp)
{
    // std::map<T,U>::mapped_type = mp[std::map<T,U>::key_type]
}

void f1128(void)
{
    std::map<std::string, std::vector<int>> mp;
    std::map<std::string, std::vector<int>>::iterator ret = mp.find("");
}

std::map<std::string, std::string> build_map(const std::string& mapFile)
{
    std::ifstream ifs(mapFile);

    if(!ifs)
        throw std::runtime_error("Cannot open input file '" + mapFile + "' : " + strerror(errno));

    std::map<std::string, std::string> trans_map;
    std::string key, value;

    while(ifs >> key && getline(ifs, value)) {
        if(std::find_if_not(value.cbegin(), value.cend(), isspace) != value.cend())
            trans_map[key] = value.substr(1);
        else
            throw std::runtime_error("no rule for " + key);
    }

    return trans_map;
}

const std::string& 
transform(const std::string& word, const std::map<std::string, std::string> &m)
{
    auto map_it = m.find(word);

    if(map_it != m.cend())
        return map_it->second;
    else
        return word;
}

void word_transform(const std::string& mapFile, const std::string& inputFile)
{
    std::ifstream ifs(inputFile);
    if(!ifs)
        throw std::runtime_error("Cannot open input file '" + inputFile + "' : " + strerror(errno));

    auto trans_map = build_map(mapFile);
    std::string text;

    while(getline(ifs, text)) {
        std::istringstream stream(text);
        std::string word;
        bool firstWord = true;

        while(stream >> word) {
            if(firstWord)
                firstWord = false;
            else
                std::cout << " ";

            cout << transform(word, trans_map);
        }

        cout << endl;
    }
}

int main(void)
{
    f114();
    f117();
    f1112();
    f1120();
    word_transform("transformation_rules", "transform_text");


    return 0;
}