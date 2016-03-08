#include<iostream>
#include<vector>
#include<cmath>

typedef long unsigned int luint;

// Adds the elements of one vector<T> to the elements of another.
// For example, f(v1,v2) should do v1[i]+=v2[i] for each element of v1.

template<typename T>
void f(std::vector<T>& v1, const std::vector<T>& v2)
{
    size_t limit = v1.size();
    // If v1.size() <= v2.size(), limit = v1.size() always.
    if(limit > v2.size())
        limit = v2.size();

    for(size_t i = 0; i < limit; ++i)
        v1[i] += v2[i];
}

// Takes a vector<T> vt and a vector<U> vu as arguments
// and returns the sum of all vt[i]*vu[i]s.

template<typename T, typename U>
auto f(const std::vector<T>& vt, const std::vector<U>& vu)
{
    size_t limit = vt.size();
    if(limit > vu.size())
        limit = vu.size();

    decltype(vt[0]*vu[0]) sum = 0;
    for(size_t i = 0; i < limit; ++i)
        sum += vt[i]*vu[i];

    return sum;
}

struct division_by_zero{};

template<typename T>
class Number{
    public:
        Number(T val = T()): num{val} {}

        T value() const {return num;}

    private:
        T num;
};

template<typename T, typename U>
auto operator+(const Number<T>& lsi, const Number<U>& rsi)
{
    return Number<decltype(lsi.value()+rsi.value())>{lsi.value() + rsi.value()};
}

template<typename T, typename U>
auto operator-(const Number<T>& lsi, const Number<U>& rsi)
{
    return Number<decltype(lsi.value()-rsi.value())>{lsi.value() - rsi.value()};
}

template<typename T, typename U>
auto operator*(const Number<T>& lsi, const Number<U>& rsi)
{
    return Number<decltype(lsi.value()*rsi.value())>{lsi.value() * rsi.value()};
}

template<typename T, typename U>
auto operator/(const Number<T>& lsi, const Number<U>& rsi)
{
    if(rsi.value() != 0)
        return Number<decltype(lsi.value()/rsi.value())>{lsi.value() / rsi.value()};

    throw division_by_zero{};
}

template<typename T, typename U>
auto operator%(const Number<T>& lsi, const Number<U>& rsi)
{
    if(rsi.value() != 0)
        return Number<decltype(lsi.value()+rsi.value())>{fmod(lsi.value(),rsi.value())};

    throw division_by_zero{};
}

Number<int> operator%(const Number<int>& lsi, const Number<int>& rsi)
{
    if(rsi.value() != 0)
        return Number<int>{lsi.value() % rsi.value()};

    throw division_by_zero{};
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Number<T>& rsi){return os << rsi.value();}

template<typename T>
std::istream& operator>>(std::istream& is, Number<T>& rsi)
{
    T temp;
    is >> temp;
    rsi = Number<T>{temp};
    return is;
}

int main(void)
{
    Number<int> v{5};
    Number<int> y{3};
    Number<long double> t{3.3};
    Number<double> g{7.7};
    Number<double> h;
    std::vector<long int> te{1,2,3,4,5};
    std::vector<long double> tyy{1.1,2.2,3.3,4.49};
    std::cout << f(te,tyy);

    return 0;
}
