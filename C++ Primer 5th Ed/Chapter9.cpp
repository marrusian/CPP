#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <iomanip>
#include <deque>
#include <iterator>
#include <forward_list>
#include <map>
#include <limits>
#include <array>

template <typename T>
inline bool is_equal(const std::vector<T>& v1, const std::vector<T>& v2)
{
    if(v1.size() == v2.size()) {
        for(decltype(v1.size()) i = 0, lim = v1.size(); i < lim; ++i)
            if(v1[i] != v2[i])
                return false;
        return true;
    }

    return false;
}

template <typename T>
int comp(const std::list<T>& lst, const std::vector<T>& vct)
{
    auto lim = lst.size() < vct.size()? lst.size() : vct.size();
    decltype(vct.size()) i = 0;

    for(auto bgl = lst.cbegin(); i < lim; ++i, ++bgl)
        if(*bgl != vct[i])
            return *bgl - vct[i];

    return lst.size() - vct.size();
}

void f918(void)
{
    std::string word;
    std::deque<std::string> dq;

    while(std::cin >> word)
        dq.emplace_back(word);

    if(!std::cin.bad())
        std::cin.clear();

    for(auto bg = dq.cbegin(), nd = dq.cend(); bg != nd; ++bg)
        std::cout << *bg << " ";
    std::cout << std::endl;
}

template <typename T>
void f920(const std::list<T>& lst)
{
    std::deque<T> dq_even, dq_odd;

    for(auto bg = lst.cbegin(), nd = lst.cend(), fst = bg; bg != nd; ++bg)
        if(std::distance(fst, bg)%2)
            dq_odd.emplace_back(*bg);
        else
            dq_even.emplace_back(*bg);

    printf("Even deque: ");
    for(const auto &x : dq_even)
        std::cout << x << " ";
    std::cout << std::endl;

    printf("Odd deque: ");
    for(const auto& x : dq_odd)
        std::cout << x << " ";
    std::cout << std::endl;
}

void f926(void)
{
    int ia[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89};

    std::vector<int> vec(std::begin(ia), std::end(ia));
    std::list<int> lst(std::begin(ia), std::end(ia));

    auto itl = lst.begin();
    auto itv = vec.begin();
    for(size_t i = 0; i < sizeof(ia)/sizeof(int); ++i)
        if(ia[i] % 2){
            itl = lst.erase(itl);
            ++itv;
        }
        else{
            itv = vec.erase(itv);
            ++itl;
        }

    std::cout << "Vector: ";
    for(auto x : vec)
        std::cout << x << " ";
    std::cout << std::endl;

    std::cout << "List: ";
    for(auto x : lst)
        std::cout << x << " ";
    std::cout << std::endl;
}

void f927(void)
{
    std::forward_list<int> flt = {0,1,2,3,4,5,6,7,8,9};

    auto prev = flt.before_begin();
    auto curr = flt.begin();

    while(curr != flt.end())
        if(*curr % 2)
            curr = flt.erase_after(prev);
        else{
            prev = curr;
            ++curr;
        }

    std::cout << "Even list: ";
    for(auto x : flt)
        std::cout << x << " ";
    std::cout << std::endl;
}

void f928(std::forward_list<std::string>& flt, const std::string& findStr,
            const std::string& insertStr)
{
    auto curr = flt.begin();
    auto prev = flt.before_begin();

    while(curr != flt.end() && *curr != findStr) {
        prev = curr;
        ++curr;
    }

    if(curr == flt.end())
        flt.emplace_after(prev, insertStr);
    else
        flt.emplace_after(curr, insertStr);

    for(const auto& x : flt)
        std::cout << x << " ";
    std::cout << std::endl;
}

void eg94(void)
{
    std::vector<int> ivec;

    std::cout << "ivec: size " << ivec.size()
              << " capacity: " << ivec.capacity() << std::endl;

    ivec.resize(24);
    std::cout << "ivec: size " << ivec.size()
              << " capacity: " << ivec.capacity() << std::endl;

    ivec.reserve(50);
    std::cout << "ivec: size " << ivec.size()
              << " capacity: " << ivec.capacity() << std::endl;

    ivec.resize(ivec.capacity());
    std::cout << "ivec: size " << ivec.size()
              << " capacity: " << ivec.capacity() << std::endl;

    ivec.push_back(0);
    std::cout << "ivec: size " << ivec.size()
              << " capacity: " << ivec.capacity() << std::endl;

    ivec.shrink_to_fit();
    std::cout << "ivec: size " << ivec.size()
              << " capacity: " << ivec.capacity() << std::endl;
}

void f941(const std::vector<char>& vec)
{
    std::string str(vec.begin(), vec.end());
    std::string str2(&vec[0]);
}

void f947(void)
{
    std::string str{"ab2c3d7R4E6"};
    std::string::size_type pos = 0;

    while((pos = str.find_first_of("0123456789", pos)) != std::string::npos)
    {
        std::cout << "str[" << pos << "] = " << str[pos] << std::endl;
        ++pos;
    }

    pos = 0;
    while((pos = str.find_first_not_of("0123456789", pos)) != std::string::npos)
    {
        std::cout << "str[" << pos << "] = " << str[pos] << std::endl;
        ++pos;
    }
}

void f949(const std::string& fileName)
{
    std::pair<std::string, unsigned> pr("", std::numeric_limits<unsigned>::max());

    std::ifstream ifs(fileName);
    if(!ifs)
        perror("Cannot open input file");

    std::string word;
    while(ifs >> word) {
        unsigned descAscCounter;
        std::string::size_type pos = 0;

        while((pos = word.find_first_of("qypgjthklfdlb", pos)) != std::string::npos){
            ++pos;
            ++descAscCounter;
        }

        if(pr.first.size() < word.size() && pr.second >= descAscCounter)
            pr = std::make_pair(word, descAscCounter);
    }

    if(ifs.bad())
        perror("Corrupted stream");

    std::cout << pr.first << " | " << pr.second << std::endl;
}

void f950(const std::vector<std::string>& vec)
try{
    long double sum = 0.0L;

    for(const std::string& num : vec)
        sum += stold(num);

    std::cout << "Sum: " << sum << std::endl;
}catch(std::invalid_argument& err) {
    std::cerr << err.what() << ": invalid argument" << std::endl;
}catch(std::out_of_range& err) {
    std::cerr << err.what() << ": out of range" << std::endl;
}

class F951
{
public:
    F951(const std::string& date);
    unsigned get_year() const {return year;}
    unsigned get_month() const {return month;}
    unsigned get_day() const {return day;}
    std::string show_as_date(void)
        {return std::to_string(month) + "/" + std::to_string(day) + "/" + std::to_string(year);}

private:
    unsigned year{1900}, month{01}, day{01};
    static const std::array<std::string,12> MONTHS;
};

const std::array<std::string,12> F951::MONTHS = {"January", "February", "March",
                                                "April", "May", "June", "July",
                                                "August", "September", "October",
                                                "November", "December"};

F951::F951(const std::string& date)
{
    size_t p = 0;
    size_t i = 0;

    for(i; i < MONTHS.size(); ++i)
        if(date.find(MONTHS[i]) != std::string::npos ||
            date.find(MONTHS[i].substr(0, 3)) != std::string::npos)
               break;
    
    if(i != MONTHS.size())
        month = i+1;
    else{
        p = date.find_first_of("0123456789");
        month = stoi(date.substr(p));
    }

    p = date.find_first_of("0123456789", p += std::to_string(month).length());
    day = stoi(date.substr(p));

    p = date.find_first_of("0123456789", p += std::to_string(day).length());
    year = stoi(date.substr(p));
}

int main(void)
{
    std::vector<int> v1;
    std::vector<int> v2(10);
    std::vector<int> v3(10,2);
    std::vector<int> v4{1,2,3};
    std::vector<int> v5(v4.begin(), v4.end());
    std::vector<int> v6(v3);

    std::list<int> lst = {1,2,3,4,5,6};
    std::cout << comp(lst, v4) << std::endl;
    
    f918();
    f920(lst);
    f926();
    f927();

    std::forward_list<std::string> fst = {"fasole", "cartofi"};
    f928(fst, "fasole", "patrunjel");
    f928(fst, "boaba", "linte");

    f947();
    f949("primer.cpp");

    std::vector<std::string> vint{"1", "2", "3", "4", "5", "6", "7", "8", "9"};
    f950(vint);
    std::vector<std::string> vfl{"1.1","2.2","3.3","4.4","5.5","6.6","7.7","8.8","9.9"};
    f950(vfl);

    F951 obj("November 28, 2015");
    std::cout << obj.show_as_date() << std::endl;


    return 0;
}

