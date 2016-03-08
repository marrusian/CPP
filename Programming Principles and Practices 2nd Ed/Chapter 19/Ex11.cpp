#include<iostream>
#include<memory>

template<typename T, typename A = std::allocator<T>>
class Counted_Ptr{
    public:
        explicit Counted_Ptr(size_t n, T def = T())
        {
            elemc = n;
            usec = new size_t{1};
            point = alloc.allocate(n);
            for(size_t i = 0; i < n; ++i)
                alloc.construct(&point[i], def);
        }

        Counted_Ptr(Counted_Ptr& ptr): alloc{ptr.alloc}, point{ptr.point},
            elemc{ptr.elemc}, usec{ptr.usec}
            {
                ++*usec;
                //std::cout << "copy-constr" << std::flush;
            }
        Counted_Ptr& operator=(Counted_Ptr& ptr)
        {
            //std::cout << "copy-assig";
            --*usec;
            this->~Counted_Ptr();
            alloc = ptr.alloc;
            point = ptr.point;
            elemc = ptr.elemc;
            usec = ptr.usec;
            ++*usec;
            return *this;
        }

        Counted_Ptr(Counted_Ptr&& ptr): alloc{ptr.alloc}, point{ptr.point},
            elemc{ptr.elemc}, usec{ptr.usec}
            {/*std::cout << "move-constr" << std::flush;*/}
        Counted_Ptr& operator=(Counted_Ptr&& ptr)
        {
           // std::cout << "move-assign" << std::flush;
            --*usec;
            this->~Counted_Ptr();
            alloc = ptr.alloc;
            point = ptr.point;
            elemc = ptr.elemc;
            usec = ptr.usec;
            return *this;
        }

        ~Counted_Ptr()
        {
            if(!(*usec)){
                for(size_t i = 0; i < elemc; ++i)
                    alloc.destroy(&point[i]);
                alloc.deallocate(point, elemc);
               // std::cout << "BYE_BYE!" << '\n';
            }
        }

        size_t count() const {return *usec;}
        size_t size() const {return elemc;}

        T& operator*() const {return *point;}
        T* operator->() const {return point;}

        T& operator[](size_t i) {return *(point+i);}
        const T& operator[](size_t i) const {return *(point+i);}

        T* operator+(size_t i) const {return point+i;}
        T* operator-(size_t i) const {return point-i;}

        explicit operator bool() {return point == nullptr;}

    private:
        A alloc;
        T* point;
        size_t elemc;
        size_t* usec;
};

Counted_Ptr<int> f(Counted_Ptr<int> r)
{
    r = Counted_Ptr<int>(55);
    return r;
}

int main(void)
{
    Counted_Ptr<int> p(2);
    p = f(p);
    std::cout << p.count();
    std::cout << '\n' << p.size();

    return 0;
}
