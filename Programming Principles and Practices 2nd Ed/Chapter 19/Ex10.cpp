#include<iostream>
#include<type_traits>

template<typename T>
class Default_Delete{
    public:
        Default_Delete() noexcept = default;
        void operator()(T* ptr) const {delete ptr;}
};

template<typename T>
class Default_Delete<T[]>{
    public:
        Default_Delete() noexcept;
        void operator()(T* ptr) const {delete[] ptr;}
};

template<typename T, typename D = Default_Delete<T>>
class Unique_Ptr{
    public:
        explicit Unique_Ptr(T* p = nullptr) noexcept : point{p} {}

        Unique_Ptr(T* p,
            typename std::conditional<std::is_reference<D>::value, D, const D&> del) noexcept
            : point{p}, del_type{del} {}

        Unique_Ptr(T* p, typename std::remove_reference<D>::type&& del) noexcept
            : point{p}, del_type{del} {}

        ~Unique_Ptr() {del_type(point);}

        Unique_Ptr(const Unique_Ptr&) = delete;
        Unique_Ptr& operator=(const Unique_Ptr&) = delete;

        Unique_Ptr(Unique_Ptr&& x) noexcept : point{x.point} {x.point = nullptr;}
        Unique_Ptr& operator=(Unique_Ptr&& x) noexcept
        { del_type(x); point = x.point; x.point = nullptr; return *this;}

        Unique_Ptr& operator=(decltype(nullptr)) {point = nullptr; return *this;}

        T& operator*() const {return *point;}
        T* operator->() const noexcept {return point;}

        explicit operator bool() const noexcept {return point == nullptr;}

        T* get() const noexcept {return point;}
        D& get_deleter() noexcept {return del_type;}
        const D& get_deleter() const noexcept {return del_type;}

        T* release() noexcept {T* temp = point; point = nullptr; return temp;}
        void reset(T* p = nullptr) noexcept {this->~Unique_Ptr(); point = p;}

    private:
        D del_type;
        T* point;
};


int main(void)
{


    return 0;
}
