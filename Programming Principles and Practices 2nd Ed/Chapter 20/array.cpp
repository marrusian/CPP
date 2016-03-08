#include<iostream>
#include<array>
template<typename T, size_t N>
struct array{
        struct out_of_range{};

        using value_type = T;
        using size_type = size_t;
        using reference = T&;
        using const_reference = const T&;
        using pointer = T*;
        using const_pointer = const T*;
        using iterator = T*;
        using const_iterator = const T*;

        T elems[N];

        iterator begin() {return elems;}
        const_iterator begin() const {return elems;}
        const_iterator cbegin() const {return elems;}
        iterator end() {return elems+N;}
        const_iterator end() const {return elems+N;}
        const_iterator cend() const {return elems+N;}

        size_type size() const {return N;}
        size_type max_size() const {return (size_t)-1/sizeof(T);}
        bool empty() const {return !static_cast<bool>(N);}

        reference operator[](size_type n) {return elems[n];}
        const_reference operator[](size_type n) const {return elems[n];}

        reference at(size_type n);
        const_reference at(size_type n) const;

        reference front() {return *elems;}
        const_reference front() const {return *elems;}
        reference back() {return elems[N-1];}
        const_reference back() const {return elems[N-1];}

        pointer data() {return elems;}
        const_pointer data() const {return elems;}
};

template<typename T, size_t N>
typename array<T,N>::reference array<T,N>::at(size_type n)
{
    if(0<n || N<=n) throw out_of_range{};
    return elems[n];
}

template<typename T, size_t N>
typename array<T,N>::const_reference array<T,N>::at(size_type n) const
{
    if(0<n || N<=n) throw out_of_range{};
    return elems[n];
}

// Helper Functions
template<typename T, size_t N>
bool operator==(const array<T,N>& lhs, const array<T,N>& rhs)
{
    for(typename array<T,N>::size_type i = 0; i < N; ++i)
        if(lhs[i] != rhs[i]) return false;

    return true;
}

template<typename T, size_t N>
bool operator!=(const array<T,N>& lhs, const array<T,N>& rhs) {return !(lhs==rhs);}

template<typename T, size_t N>
bool operator<(const array<T,N>& lhs, const array<T,N>& rhs)
{
    for(typename array<T,N>::size_type i = 0; i < N; ++i)
        if(lhs[i] >= rhs[i]) return false;

    return true;
}

template<typename T, size_t N>
bool operator>=(const array<T,N>& lhs, const array<T,N>& rhs) {return !(lhs<rhs);}

template<typename T, size_t N>
bool operator>(const array<T,N>& lhs, const array<T,N>& rhs) {return (rhs<lhs);}

template<typename T, size_t N>
bool operator<=(const array<T,N>& lhs, const array<T,N>& rhs) {return !(rhs<lhs);}


int main(void)
{



    return 0;
}
