#include <iostream>

template <typename InputIter, typename T>
InputIter f164(InputIter beg, InputIter end, const T& val)
{
    while(beg != end){
        if(*beg == val)
            return beg;
        ++beg;
    }

    return end;
}

template <typename T, size_t N>
void f165(const T (&arr)[N])
{
    for(size_t i=0; i != N; ++i)
        std::cout << arr[i] << " ";
}

template <typename T, size_t N>
inline constexpr T* f166_beg(T (&arr)[N])
{
    return arr;
}
template <typename T, size_t N>
inline constexpr T* f166_end(T (&arr)[N])
{
    return arr+N;
}

template <typename T, size_t N>
inline constexpr size_t f167(const T (&)[N]) {return N;}

int main(void)
{
    

    return 0;
}