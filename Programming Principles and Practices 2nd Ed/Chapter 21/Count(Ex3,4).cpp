#include<iostream>
#include<vector>
#include<cstdlib>
#include<algorithm>
#include<iterator>

/*
* The reasoning behind Input_Iterator::difference_type vs size_t is as follows:
*
*   As long as the underlying system architecture supports it, we could
* theoretically have a sequence whose length(i.e. size) would be far
* greater than the maximum value of the size_t implementation.
*
*   Given that, we could avoid a size_t overflow by defining a custom
* difference:type for our Iterator.
*/

template<typename Iter, typename T>
  typename std::iterator_traits<Iter>::difference_type
  Count(Iter first, Iter last, const T& val)
{
    typename std::iterator_traits<Iter>::difference_type count{};
    while(first!=last){
        if(*first==val) ++count;
        ++first;
    }
    return count;
}

template<typename Iter, typename UnaryPredicate>
   typename std::iterator_traits<Iter>::difference_type
   Count_if(Iter first, Iter last, UnaryPredicate pred)
{
    typename std::iterator_traits<Iter>::difference_type count{};
    while(first!=last){
        if(pred(*first)) ++count;
        ++first;
    }
    return count;
}


int main(void)
{
    constexpr size_t SIZE = 100;
    constexpr int UPPER_BOUND = 100;

    std::vector<int> vi;

    srand(static_cast<size_t>(time(NULL)));
    for(size_t i{SIZE}; i; --i)
        vi.push_back((rand() / (RAND_MAX+1.0)) * UPPER_BOUND);

    std::stable_sort(vi.begin(),vi.end());
    std::cout << Count_if(vi.begin(),vi.end(),[](int x){return !(x%2);});

    return 0;
}
