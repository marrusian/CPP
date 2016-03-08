#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>

using std::cout; using std::cin; using std::endl;

class HasPtr
{
    friend void swap(HasPtr&, HasPtr&);
    friend bool operator<(const HasPtr& lhs, const HasPtr& rhs);
    friend std::ostream& operator<<(std::ostream& os, const HasPtr& rhs);

public:
    HasPtr(const char *s) :
         ps(new std::string(s)), i(0) { }
    HasPtr(const std::string& s = std::string()) :
        ps(new std::string(s)), i(0) { }

    HasPtr(HasPtr&& hpc) noexcept : 
        ps(hpc.ps), i(hpc.i) {hpc.ps = nullptr;}
    HasPtr(const HasPtr& hpc) :
        ps(new std::string(*hpc.ps)), i(hpc.i) { }

    ~HasPtr() {delete ps;}

    // HasPtr& operator=(HasPtr rhs);
    HasPtr& operator=(const HasPtr& rhs);
    HasPtr& operator=(HasPtr&& rhs) noexcept;

private:
    std::string *ps;
    int i;
};

// HasPtr& HasPtr::operator=(HasPtr rhs)
// {
//     swap(*this, rhs);
//     return *this;
// }

HasPtr& HasPtr::operator=(const HasPtr& rhs)
{
    auto new_str = new std::string(*rhs.ps);
    delete ps;
    ps = new_str;
    i = rhs.i;

    return *this;
}

HasPtr& HasPtr::operator=(HasPtr&& rhs) noexcept
{
    if(this != &rhs) {
        ps = rhs.ps;
        i  = rhs.i;

        rhs.ps = nullptr;
    }

    return *this;
}

inline void swap(HasPtr& lhs, HasPtr& rhs)
{
    std::cout << "hasptr swap" << std::endl;
    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
}

bool operator<(const HasPtr& lhs, const HasPtr& rhs)
{
    if(*lhs.ps == *rhs.ps)
        return lhs.i < lhs.i;
    else
        return *lhs.ps < *rhs.ps;
}

std::ostream& operator<<(std::ostream& os, const HasPtr& rhs)
{
    return os << *rhs.ps << " | " << rhs.i;
}

class HasPtrSC
{
public:
    HasPtrSC(const std::string &s = std::string()) :
        ps(new std::string(s)), i(0), use(new size_t(1))
        {  }
    HasPtrSC(const HasPtrSC& hpc) :
        ps(hpc.ps), i(hpc.i), use(hpc.use) {++*hpc.use;}
    ~HasPtrSC() noexcept;

    HasPtrSC& operator=(const HasPtrSC& hpc) noexcept;

private:
    std::string *ps;
    int i;
    size_t *use; 
};

HasPtrSC::~HasPtrSC() noexcept
{
    if(!--*use){
        delete ps;
        delete use;
    }
}

HasPtrSC& HasPtrSC::operator=(const HasPtrSC& hpc) noexcept
{
    ++*hpc.use;
    this->~HasPtrSC();

    ps  = hpc.ps;
    i   = hpc.i;
    use = hpc.use;

    return *this;
}

class Employee
{
public:
    Employee(const std::string &str = std::string()) :
        name(str), id(++x) { }
    Employee(const Employee& emp) :
        name(emp.name), id(++x) { }

    Employee& operator=(const Employee& empl);
    size_t show_id() const {return id;}

private:
    static size_t x;
    std::string name;
    size_t id;
};

size_t Employee::x = 0;

Employee& Employee::operator=(const Employee& empl)
{
    if(this == &empl)
        return *this;

    name = empl.name;
    id = ++x;

    return *this;
}

int f() {return 5;}

void f1346(void)
{
    std::vector<int> vi(100);

    int&& r1 = f();
    int&  r2 = vi[0];
    int&  r3 = r1;
    int&& r4 = vi[0] * f();
}

int main(void)
{
    std::vector<HasPtr> vec = {"Kaluga", "Nicaragua", "Maytria", "Johhna"};
    std::sort(vec.begin(), vec.end());
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<HasPtr>(cout, "\t"));
    std::cout << std::endl;

    int&& r = f();

    return 0;
}

// --      DCONS  DES   CC   CA   MC   MA
// N/A      def   def   def  def  def  def
// ANY CS   ND    def   def  def  def  def
// DC       UD    def   def  def  def  def
// DES      def   UD    DEF  DEF  ND    ND
// CC       ND    def   UD   DEF  ND    ND
// CA       def   def   DEF  UD   ND    ND
// MC       ND    def   del  del  UD    ND
// MA       def   def   del  del  ND    UD

// The SDES is defined as deleted if the class has a member whose own DES
// is deleted/inaccessible;
// The SCC is defined as deleted if the class has a member whose own CC
// is deleted/inaccessible, if the class has a member whose DES is
// deleted/inaccessible;
// The SCA is defined as deleted if the class has a member whose own CA
// is deleted/inaccessible; if the class has a const or ref member;
// The SDC is defined as deleted if the class has a member whose own DC
// is deleted/inaccessible; if the class has a member whose own DES is
// deleted/inaccessible; if the class has a const member without a DC
// or in-class initializer; if the class has a ref member without an
// in-class initializer;
// The SMC is defined as deleted if the class has a member whose own MC
// is ND or deleted/inaccessible; if the class has a member whose own DES
// is deleted/inaccessible;
// The SMA is defined as deleted if the class has a member whose own MA
// is ND or deleted/inaccessible; if the class has a const/ref member;