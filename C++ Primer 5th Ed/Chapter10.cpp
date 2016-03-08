#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <list>
#include <string>
#include <functional>
#include <iterator>
#include <type_traits>

using std::cin; using std::cout; using std::endl;
using namespace std::placeholders;

template <class InputIterator>
void print(InputIterator beg, InputIterator end)
{
    while(beg != end)
        cout << *beg++ << " ";
    cout << endl;
}

void f101(void)
{
    std::iostream::iostate oldState = cin.rdstate();
    std::vector<int> vint;

    cin.clear();
    cout << "Insert integers: ";
    for(int i; cin >> i; vint.push_back(i))
        continue;

    if(cin.bad())
        perror("Corrupted stream");

    int val;

    cin.clear();
    cout << "Insert value: ";
    while(cin >> val) {
        auto count = std::count(vint.cbegin(), vint.cend(), val);
        cout << val << " occurs " << count << " times\n";
        cout << "Insert value: ";
    }

    if(cin.bad())
        perror("Corrupted stream");
    
    cout << endl;
    cin.clear(oldState);
}

void f102(void)
{
    std::iostream::iostate oldState = cin.rdstate();
    std::list<std::string> lstr;

    cin.clear();
    cout << "Insert integers: ";
    for(int i; cin >> i; lstr.push_back(std::to_string(i)))
        continue;

    if(cin.bad())
        perror("Corrupted stream");

    int val;

    cin.clear();
    cout << "Insert value: ";
    while(cin >> val) {
        auto count = std::count(lstr.cbegin(), lstr.cend(), std::to_string(val));
        cout << val << " occurs " << count << " times\n";
        cout << "Insert value: ";
    }

    if(cin.bad())
        perror("Corrupted stream");
    
    cout << endl;
    cin.clear(oldState);
}

void f103(void)
{
    std::iostream::iostate oldState = cin.rdstate();
    std::vector<int> vint;

    cin.clear();
    cout << "Insert integers: ";
    for(int i; cin >> i; vint.push_back(i))
        continue;

    if(cin.bad())
        perror("Corrupted stream");

    cout << "Sum: " << std::accumulate(vint.cbegin(), vint.cend(), 0ULL) << endl;

    cin.clear(oldState);
}

template <class OutputIterator>
inline void f106(OutputIterator iter, size_t n)
{
    std::fill_n(iter, n, 0);
}

void f109(std::vector<std::string>& cont)
{
    std::sort(cont.begin(), cont.end());

    auto end_unique = std::unique(cont.begin(), cont.end());
    print(cont.cbegin(), cont.cend());

    cont.erase(end_unique, cont.end());
    print(cont.cbegin(), cont.cend());
}

void f1011(std::vector<std::string>& cont)
{
    f109(cont);

    std::stable_sort(cont.begin(), cont.end(), [](const std::string& s1,
                             const std::string &s2) {return s1.size() < s2.size();});

    print(cont.cbegin(), cont.cend());
}

// template <class C>
// void f1013(C& cont, bool (*p)(typename C::const_reference e1))
// {
//     auto end_part = std::partition(cont.begin(), cont.end(), p);
//     print(end_part, cont.end());
// }

template <class C, class P>
void f1013(C& cont, P pred)
{
    auto end_part = std::partition(cont.begin(), cont.end(), pred);
    print(end_part, cont.end());
}

void f1014(void)
{
    auto f = [](int a, int b) {return a+b;};
    f(2,5);
}

void f1015(int a)
{
    auto f = [a](int b) {return a+b;};
    f(5);
}

void f1016(std::vector<std::string>& words, std::vector<std::string>::size_type sz)
{
    sort(words.begin(), words.end());
    words.erase(std::unique(words.begin(), words.end()), words.end());

    stable_sort(words.begin(), words.end(),
                 [](const std::string &a, const std::string& b)
                    {return a.size() < b.size();});

    auto wc = find_if(words.begin(), words.end(),
                [sz](const std::string &a)
                    {return a.size() >= sz;});

    std::for_each(wc, words.end(),
                    [](const std::string& s) {cout << s << " ";});
    cout << endl;
}

void f1018(std::vector<std::string>& words, std::vector<std::string>::size_type sz)
{
    sort(words.begin(), words.end());
    words.erase(std::unique(words.begin(), words.end()), words.end());

    stable_sort(words.begin(), words.end(),
                 [](const std::string &a, const std::string& b)
                    {return a.size() < b.size();});

    auto wc = std::partition(words.begin(), words.end(),
                             [sz](const std::string &a)
                              {return a.size() < sz;});

    std::for_each(wc, words.end(),
                    [](const std::string& s) {cout << s << " ";});
    cout << endl;
}

void f1019(std::vector<std::string>& words, std::vector<std::string>::size_type sz)
{
    sort(words.begin(), words.end());
    words.erase(std::unique(words.begin(), words.end()), words.end());

    stable_sort(words.begin(), words.end(),
                 [](const std::string &a, const std::string& b)
                    {return a.size() < b.size();});

    auto wc = std::stable_partition(words.begin(), words.end(),
                                  [sz](const std::string &a)
                                    {return a.size() < sz;});

    std::for_each(wc, words.end(),
                    [](const std::string& s) {cout << s << " ";});
    cout << endl;
}

bool pred(const std::string& s1) {return s1.size() < 5;}

void f1021(int a)
{
    auto f = [&a]() -> bool {return a? --a : a;};

    while(f())
        continue;
}

inline bool check_size(const std::string& str, std::string::size_type sz)
{
    return str.size() >= sz;
}

void f1022(const std::string& fileName)
{
    std::ifstream ifs(fileName);
    if(!ifs){
        perror(("Cannot open input file " + fileName).c_str());
        return;
    }

    std::istream_iterator<std::string> eos;
    std::istream_iterator<std::string> ifit(ifs);
    
    size_t count = 0;
    std::for_each(ifit, eos, [&count](const std::string& s) {if(s.size()>=6) ++count;});
    // while(ifit != eos)
    //     if(ifit++->size() >= 6)
    //         ++count;

    if(ifs.bad()){
        perror("Corrupted stream");
        return;
    }

    cout << "Number of words with length() > 5: " << count << endl;
}

void f1024(const std::vector<int>& vint, const std::string& str)
{
    auto it = std::find_if_not(vint.cbegin(), vint.cend(), bind(check_size, str, _1));
   
    if(it == vint.cend())
        cout << "There is no value > " << str.size();
    else
        cout << "First element in vector with value > " << str.size()
             << " is " << *it;

    cout << endl;
}

template <typename T>
void f1027(const std::vector<T>& vec)
{
    std::list<T> lst;
    std::vector<T> vtemp(vec);

    std::sort(vtemp.begin(), vtemp.end());
    std::unique_copy(vtemp.begin(), vtemp.end(), std::back_inserter(lst));

    print(lst.cbegin(), lst.cend());
}

template <typename T>
void f1028(const std::vector<T>& vec)
{
    std::vector<T> c1, c3;
    std::list<T> c2;

    std::copy(vec.cbegin(), vec.cend(), std::back_inserter(c1));
    std::copy(vec.cbegin(), vec.cend(), std::front_inserter(c2));
    std::copy(vec.cbegin(), vec.cend(), std::inserter(c3, c3.begin()));

    cout << "C1: ";
    print(c1.cbegin(), c1.cend());
    cout << "C2: ";
    print(c2.cbegin(), c2.cend());
    cout << "C3: ";
    print(c3.cbegin(), c3.cend());
}

void f1029(const std::string& fileName)
{
    std::ifstream ifs(fileName);
    if(!ifs){
        perror(("Cannot open input file " + fileName).c_str());
        return;
    }

    std::istream_iterator<std::string> isit(ifs), eof;
    std::vector<std::string> vec(isit, eof);

    if(ifs.bad()){
        perror("Corrupted stream");
        return;
    }

    print(vec.cbegin(), vec.cend());
}

void f1030(void)
{
    std::iostream::iostate oldState = cin.rdstate();
    cin.clear();

    cout << "Insert values: ";
    std::istream_iterator<double> isit(cin), eof;

    std::vector<double> seq(isit, eof);
    std::sort(seq.begin(), seq.end());

    std::ostream_iterator<double> osit(cout, " ");
    std::copy(seq.cbegin(), seq.cend(), osit);

    cout << endl;
    cin.clear(oldState);
}

void f1031(void)
{
    std::iostream::iostate oldState = cin.rdstate();
    cin.clear();

    cout << "Insert values: ";
    std::istream_iterator<double> isit(cin), eof;

    std::vector<double> seq(isit, eof);
    std::sort(seq.begin(), seq.end());

    std::ostream_iterator<double> osit(cout, " ");
    std::unique_copy(seq.cbegin(), seq.cend(), osit);

    cout << endl;
    cin.clear(oldState);
}

void f1033(const std::string& inFile, const std::string& outFile1,
            const std::string& outFile2)
{
    std::ifstream ifs(inFile);
    if(!ifs) {
        perror(("Cannot open input file " + inFile).c_str());
        return;
    }

    std::ofstream ofs1(outFile1), ofs2(outFile2);

    if(!ofs1) {
        perror(("Cannot open output file " + outFile1).c_str());
        return;    
    }

    if(!ofs2) {
        perror(("Cannot open output file " + outFile2).c_str());
        return;    
    }

    std::istream_iterator<double> ifit(ifs), eof;
    std::ostream_iterator<int> ofit1(ofs1, " "), ofit2(ofs2, " ");
    std::for_each(ifit, eof, [&](int val) {val%2? ofit1=val : ofit2=val;});

    if(ifs.bad()) {
        perror("Corrupted stream");
        return;
    }

    if(ofs1.bad() || ofs2.bad()) {
        perror("Corrupted stream");
        return;
    }
}

template <class C>
void f1034(const C& cont)
{
    std::ostream_iterator<typename C::value_type> osit(cout, " ");
    std::copy(cont.crbegin(), cont.crend(), osit);
    cout << endl;
}

template <class C>
void f1035(const C& cont)
{
    std::ostream_iterator<typename C::value_type> osit(cout, " ");
    std::reverse_copy(cont.cbegin(), cont.cend(), osit);
    cout << endl;
}

template <class C>
void f1036(const C& cont)
{
    if(std::is_arithmetic<typename C::value_type>::value){
        auto pos = std::find(cont.crbegin(), cont.crend(), 0);
        if(pos != cont.crend())
            cout << "Zero found at position: " << cont.crend() - pos - 1 << endl;
    }
}

template <typename T>
void f1037(const std::vector<T>& vec)
{
    std::list<T> lst;
    std::copy(vec.crbegin()+2, vec.crbegin()+7, std::back_inserter(lst));
    print(lst.cbegin(), lst.cend());
}

void f1042(std::list<std::string>& lst)
{
    lst.sort();
    print(lst.cbegin(), lst.cend());

    lst.unique();
    print(lst.cbegin(), lst.cend());
}

int main(void)
{
    f101();
    f102();
    f103();
    // f106();
    std::vector<std::string> v{"the", "quick", "red", "fox", "jumps", "over",
                               "the", "slow", "red", "turtle"};
    f1011(v);
    //f1013(v, pred);
    f1013(v, [](const std::string& s){return s.size() < 5;});
    f1021(1000);
    f1022("Chapter10.cpp");
    std::vector<int> vi{1,2,3,4,5,6,7,8,9,10};
    f1024(vi, "partition");
    f1027(std::vector<int>{5,1,2,6,-5,-2,3,1,5,-6,2,3});
    f1028(std::vector<int>{1,2,3,4,5,6,7,8,9});
   // f1029("Chapter10.cpp");
    f1030();
    f1033("f1033", "f1033_odd", "f1033_even");
    f1034(std::vector<int>{1,2,3,4,5,6,7,8,9});
    f1035(std::vector<int>{1,2,3,4,5,6,7,8,9});
    f1036(std::vector<int>{9,5,1,2,3,0,2,1,3});
    f1037(std::vector<int>{8,3,1,5,6,0,2,3,-5,-1});
    std::list<std::string> lstr{"the", "quick", "red", "fox", "jumps", "over",
                               "the", "slow", "red", "turtle"};
    f1042(lstr);

    return 0;
}

