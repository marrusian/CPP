#include <iostream>
#include <type_traits>

using std::cout; using std::cin; using std::endl;

template <typename U, typename T>
class F1434
{
public:
    T& operator()(const U& expr, T& p1, T& p2) const;
    const T& operator()(const U& expr, const T& p1, const T& p2) const;

private:
    T& ternary(std::true_type, const U& expr, T& p1, T& p2) const;
    const T& ternary(std::true_type, const U& expr, const T& p1, const T& p2) const;
};

template <typename U, typename T>
T& F1434<U,T>::ternary(std::true_type, const U& expr, T& p1, T& p2) const
{
    return expr? p1 : p2;
}

template <typename U, typename T>
const T& F1434<U,T>::ternary(std::true_type, const U& expr, const T& p1, const T& p2) const
{
    return expr? p1 : p2;
}

template <typename U, typename T>
T& F1434<U,T>::operator()(const U& expr, T& p1, T& p2) const
{
    return ternary(typename std::is_convertible<U,bool>::type(), expr, p1, p2);
}

template <typename U, typename T>
const T& F1434<U,T>::operator()(const U& expr, const T& p1, const T& p2) const
{
    return ternary(typename std::is_convertible<U,bool>::type(), expr, p1, p2);
}

#include <vector>
#include <algorithm>
#include <utility>
#include <functional>

using namespace std::placeholders;

void f1443(int val, const std::vector<int>& v)
{
    auto it = std::find_if_not(v.cbegin(), v.cend(), std::bind(std::modulus<int>(), val, _1));
    if(it != v.cend())
        cout << *it << endl;
}

int main(void)
{
    int i=2, j=3, k=4;

    F1434<int, int> test;
    test(k,i,j);

    f1443(5, std::vector<int>{2,5,6,1,2,7,8,9,5});


    return 0;
}