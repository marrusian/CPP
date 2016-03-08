#include<iostream>
#include<initializer_list>
#include<algorithm>
#include<memory>

typedef long unsigned int luint;

struct out_of_range{};

template<typename T, typename A>
struct vector_base{
    A alloc;
    T* elem;
    luint sz;
    luint space;

    vector_base(const A& a, luint n): alloc{a}, elem{alloc.allocate(n)}, sz{n}, space{n} {}
    ~vector_base(){
        for(luint i = 0; i < sz; ++i)
            alloc.destroy(&elem[i]);
        alloc.deallocate(elem,space);
    }
};

template<typename T, typename A = std::allocator<T>>
class vector : private vector_base<T,A>{
    public:
        using iterator = T*;

        explicit vector(luint s = 0, T def = T()): vector_base<T,A>(this->alloc, s)
        {
            for(luint i = 0; i < this->sz; ++i)
                this->alloc.construct(&this->elem[i], def);
        }

        vector(std::initializer_list<T> lst): vector_base<T,A>(this->alloc, lst.size())
        { std::uninitialized_copy(lst.begin(), lst.end(), this->elem); }

        vector(const vector& arg): vector_base<T,A>(this->alloc, arg.sz)
        { std::uninitialized_copy(arg.elem, arg.elem+arg.sz, this->elem); }

        vector& operator=(const vector&);

        vector(vector&& arg): vector_base<T,A>(this->alloc,arg.sz)
        { this->elem = arg.elem; arg.sz = 0; arg.elem = nullptr;}

        vector& operator=(vector&&);

        T& operator[](luint i) {return this->elem[i];}
        const T& operator[](luint i) const {return this->elem[i];}

        iterator begin() {return &this->elem[0];}
        iterator end() {return &this->elem[this->sz];}

        T& at(iterator it);
        const T& at(iterator it) const;

        iterator insert(iterator p, const T& val);
        iterator erase(iterator p);

        T& front() {return this->elem[0];}
        const T& front() const {return this->elem[0];}

        T& back() {return this->elem[this->sz-1];}
        const T& back() const {return this->elem[this->sz-1];}

        T& at(luint i);
        const T& at(luint i) const;

        luint size() const {return this->sz;}
        luint capacity() const {return this->space;}

        void reserve(luint);
        void resize(luint, T = T());
        void push_back(const T&);
};

template<typename T, typename A>
T& vector<T,A>::at(luint i)
{
    if(this->sz<0 || this->sz<i) throw out_of_range{};
    return this->elem[i];
}

template<typename T, typename A>
const T& vector<T,A>::at(luint i) const
{
    if(this->sz<0 || this->sz<i) throw out_of_range{};
    return this->elem[i];
}

template<typename T, typename A>
T& vector<T,A>::at(iterator it)
{
    if(it<begin() || end()<=it) throw out_of_range{};
    return *it;
}

template<typename T, typename A>
const T& vector<T,A>::at(iterator it) const
{
    if(it<begin() || end()<=it) throw out_of_range{};
    return *it;
}

template<typename T, typename A>
vector<T,A>& vector<T,A>::operator=(const vector<T,A>& rarg)
{
    if(this == &rarg)
        return *this;

    if(rarg.sz <= this->sz){
        std::copy(rarg.elem, rarg.elem+rarg.sz, this->elem);
        this->sz = rarg.sz;
        return *this;
    }

    vector_base<T,A> vb(this->alloc, rarg.sz);
    std::uninitialized_copy(rarg.elem, rarg.elem+rarg.sz, vb.elem);
    std::swap(this->sz, vb.sz);
    std::swap(this->elem, vb.elem);

    return *this;
}

template<typename T, typename A>
vector<T,A>& vector<T,A>::operator=(vector<T,A>&& rarg)
{
    vector_base<T,A> vb(this->alloc, this->sz);         // Rather than delete[] elem;
    vb.elem = this->elem;

    this->elem = rarg.elem;
    this->sz = rarg.sz;

    rarg.elem = nullptr;
    rarg.sz = 0;

    return *this;
}

template<typename T, typename A>
void vector<T,A>::reserve(luint newalloc)
{
    if(newalloc <= this->space) return;     // Never decrease allocation

    vector_base<T,A> vb(this->alloc, newalloc);
    std::uninitialized_copy(this->elem, this->elem+this->sz, vb.elem);
    vb.sz = this->sz;
    std::swap(this->elem, vb.elem);
    std::swap(this->space, vb.space);
}

template<typename T, typename A>
void vector<T,A>::resize(luint newsize, T val)
{
    reserve(newsize);
    for(luint i = this->sz; i < newsize; ++i)
        this->alloc.construct(&this->elem[i], val);
    for(luint i = newsize; i < this->sz; ++i)
        this->alloc.destroy(&this->elem[i]);
    this->sz = newsize;
}

template<typename T, typename A>
void vector<T,A>::push_back(const T& val)
{
    if(!this->space)
        reserve(8);
    else if(this->sz == this->space)
        reserve(2*this->space);

    this->alloc.construct(&this->elem[this->sz],val);
    ++this->sz;
}

template<typename T, typename A>
typename vector<T,A>::iterator vector<T,A>::erase(iterator p)
{
    if(p==end()) return p;

    for(auto pos = p+1; pos!=end(); ++pos)
       *(pos-1) = *pos;

    this->alloc.destroy(end()-1);
    --this->sz;

    return p;
}

template<typename T, typename A>
typename vector<T,A>::iterator vector<T,A>::insert(iterator p, const T& val)
{
    int index = p-begin();
    if(this->sz == this->space)
        reserve(this->sz==0 ? 8 : 2*this->sz);

    this->alloc.construct(this->elem+this->sz, this->elem[this->sz-1]);

    ++this->sz;
    iterator pp = begin()+index;

    for(auto pos = end()-1; pos!=pp; --pos)
    *pos = *(pos-1);

    *(begin()+index) = val;
    return pp;
}

int main(void)
{
    vector<double> v;
    vector<int> v2{1,2,3};
    vector<double> v3{2.2,5.5,6.6,7.7};
    for(int i = 0; i < v2.size(); ++i)
        std::cout << v2[i] << '\n';

    for(int i = 0; i < 100; ++i)
        v.push_back(i);

    for(double x : v)
        std::cout << x << '\n';

    return 0;
}
