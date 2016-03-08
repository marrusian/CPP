#include<iostream>
#include<iomanip>
#include<iterator>
#include<map>
#include<string>
#include<numeric>

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, std::pair<T1,T2> p)
{
    return os << '{' << std::setw(10) << p.first << ", "
                     << std::setw(10)  << p.second
              << '}';
}

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::map<T1,T2>& mp)
{
    for(const auto& x : mp)
        os << x << '\n';
    return os;
}

template<typename T1, typename T2>
std::istream& operator>>(std::istream& is, std::pair<T1,T2>& p)
{
    std::pair<T1,T2> temp{};
    is >> temp.first >> temp.second;
    if(!is) return is;
    p = temp;
    return is;
}

template<typename T1, typename T2>
std::istream& operator>>(std::istream& is, std::map<T1,T2>& mp)
{
    size_t count{1};
    std::cout << "Pair " << count << ": ";
    for(std::pair<T1,T2> p; is >> p; mp.insert(p))
        std::cout << "Pair " << ++count << ": ";
    return is;
}

struct SumVals{
    int operator()(int v, const std::pair<std::string, int> p) const
        {return v+p.second;}
};

int main(void)
{
    constexpr size_t SIZE = 10;
    std::map<std::string,int> msi;
    for(size_t count = SIZE; count; --count){
        std::pair<std::string,int> p;
        std::cout << "Pair " << (SIZE+1)-count << ": ";
        std::cin >> p;
        msi.insert(p);
    }

    std::cout << msi << '\n';
    msi.clear();

    std::cin >> msi;
    std::cout << '\n';
    std::cout << msi << '\n';
    std::cout << std::accumulate(msi.begin(), msi.end(), 0, SumVals{});

    std::cout << '\n';
    std::map<int,std::string> mis;
    for(auto iter = msi.begin(), iterEnd = msi.end(); iter != iterEnd; ++iter)
        mis.insert(std::pair<int,std::string>{iter->second, iter->first});
    std::cout << mis;

    return 0;
}
