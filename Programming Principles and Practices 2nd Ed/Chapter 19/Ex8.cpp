#include<iostream>
#include<cstdlib>
#include<memory>

struct bad_alloc{};

template<typename T>
class Allocator{
    public:
        Allocator() {}
        template<typename U>
        Allocator(const Allocator<U>&) {}

        T* allocate(size_t n);
        void deallocate(T* p, size_t n = 0) {free(p);}
        template<typename U>
        void construct(U* p, const U& val) {new(p) U{val};}
        template<typename U>
        void destroy(U* p) {p->~U();}

        T* address(T& x) const {return &x;}
        const T* address(const T& x) const {return &x;}

        size_t max_size() const {return ((size_t)-1)/sizeof(T);}
};

template<typename T>
T* Allocator<T>::allocate(size_t n)
{
    void* temp = malloc(n*sizeof(T));
    if(!temp)
        throw bad_alloc{};

    return static_cast<T*>(temp);
}

int main(void)
{



    return 0;
}
