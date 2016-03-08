#include<iostream>
#include<list>
#include<vector>
#include<type_traits>
#include<algorithm>

template<typename Iter>
auto copy_to_vector(Iter bg, Iter end)
{
    std::vector<typename std::remove_reference<decltype(*bg)>::type> v;
    while(bg!=end){
        v.push_back(*bg);
        ++bg;
    }

    return v;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    for(const auto& x : v)
        os << x << '\n';

    return os;
}

int main(void)
{
    std::list<int> lst{5,4,3,2,5,6,7,8,9};
    std::vector<int> vec = copy_to_vector(lst.begin(), lst.end());
    std::stable_sort(vec.begin(), vec.end());
    std::cout << vec;
    return 0;
}
