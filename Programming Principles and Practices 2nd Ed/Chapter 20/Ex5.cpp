#include<iostream>
#include<vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for(const T& x : vec)
        std::cout << x << '\n';

    return os;
}

template<typename T>
std::istream& operator>>(std::istream& is, std::vector<T>& vec)
{
    for(T temp = T(); is >> temp; vec.push_back(temp)){}
    is.clear();

    return is;
}

int main(void)
{

    std::vector<double> v{2.2,3.3,4.4};
    std::cout << v;

    std::vector<int> g;
    std::cin >> g;
    std::cout << g;


    return 0;
}
