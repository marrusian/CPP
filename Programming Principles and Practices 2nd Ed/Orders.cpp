#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <vector>
#include <stdexcept>
#include <algorithm>

std::string read_data(std::istream& is, char delimiter, bool include_delim = false)
{
    std::string temp;
    char w;

    while(is.get(w) && isspace(w)){}
    is.unget();

    while(is.get(w) && w != delimiter)
        temp += w;

    while(isspace(temp.back())) temp.pop_back();

    if(include_delim) temp += w;
    else is.unget();

    return temp;
}

void putback_string(std::istream& is, const std::string& str)
{
    for(auto iter = str.end()-1, iterBeg = str.begin(); iter >= iterBeg; --iter)
        is.putback(*iter);
}

void check_syntax(std::istream& is, const std::string& member, const std::string& message, bool do_throw = true)
{
    if(is.fail()) throw std::runtime_error("Bad input data.");

    std::string temp = read_data(is,'>',true);
    if(temp != member){
        if(do_throw)
             throw std::runtime_error(message);
        else{
            putback_string(is, temp);
            is.clear(std::ios_base::failbit);
        }
    }
}

template<typename T>
std::istream& operator>>(std::istream& is, std::vector<T>& vec)
{
    for(T temp{}; is >> temp; vec.push_back(temp)){}
    return is;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for(const auto& x : vec)
        os << x << '\n';

    return os;
}

// ####################################################################################################

class Order;
class Purchase
{
    friend class Order;
    friend std::istream& operator>>(std::istream&, Purchase&);
    friend std::ifstream& operator>>(std::ifstream&, Purchase&);

    public:
        Purchase() = default;
        Purchase(std::string name, double up, size_t c): nm{name}, unit_price{up}, count{c} {}

        const std::string& name() const {return nm;}
        double price() const {return unit_price;}
        size_t units() const {return count;}

    private:
        std::string nm;
        double unit_price;
        size_t count;
};

std::istream& operator>>(std::istream& is, Purchase& pch)
{
    Purchase temp{};
    is >> temp.nm >> temp.unit_price >> temp.count;
    if(!is) return is;

    pch = temp;
    return is;
}

std::ifstream& operator>>(std::ifstream& is, Purchase& pch)
{
    check_syntax(is, "<pname>", "Bad product name entry tag.", false);
    if(!is) return is;

    Purchase temp{};
    temp.nm = read_data(is,'<');
    check_syntax(is, "</pname>","Bad product name exit tag.");

    check_syntax(is, "<pprice>", "Bad product price entry tag.");
    is >> temp.unit_price;
    check_syntax(is, "</pprice>", "Bad product price exit tag.");

    check_syntax(is, "<pquantity>", "Bad product quantity entry tag.");
    is >> temp.count;
    check_syntax(is, "</pquantity>", "Bad product quantity exit tag.");

    pch = temp;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Purchase& pch)
{
    return os << "Product name:  " << pch.name() << '\n'
              << "Product price: " << pch.price() << '\n'
              << "Units:         " << pch.units();
}

class Order
{
        friend std::istream& operator>>(std::istream&, Order&);
        friend std::ifstream& operator>>(std::ifstream&, Order&);

    public:
        Order() = default;
        Order(std::string name, std::string adrs, std::vector<Purchase> buylist)
            : nm{name}, addr{adrs}, p{buylist} {}

        const std::string& name() const {return nm;}
        const std::string& address() const {return addr;}
        const std::vector<Purchase>& products() const {return p;}

    private:
        std::string nm;
        std::string addr;
        std::vector<Purchase> p;
};

std::istream& operator>>(std::istream& is, Order& od)
{
    Order temp{};
    is >> od.nm >> od.addr >> od.p;
    if(!is) return is;

    od = temp;
    return is;
}

std::ifstream& operator>>(std::ifstream& is, Order& od)
{
    check_syntax(is, "<oname>", "Bad order name entry tag.", false);
    if(!is) return is;

    Order temp{};
    temp.nm = read_data(is,'<');
    check_syntax(is, "</oname>","Bad order name exit tag.");

    check_syntax(is, "<oaddr>", "Bad order address entry tag.");
    temp.addr = read_data(is,'<');
    check_syntax(is, "</oaddr>", "Bad order address exit tag.");

    check_syntax(is, "<oproduct>", "Bad order product entry tag.");
    for(Purchase p{}; is >> p; temp.p.push_back(p)){}
    is.clear();
    check_syntax(is, "</oproduct>", "Bad order product exit tag.");

    od = temp;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Order& od)
{
    os << "Customer name:     " << od.name()    << '\n'
       << "Customer address:  " << od.address() << '\n'
       << "Customer Shopcart:\n";

    size_t width = sizeof("Customer Shopcart: ");
    for(const auto& x : od.products()){
        os << std::setw(width) << "Product name:  " << x.name()  << '\n'
           << std::setw(width) << "Product price: " << x.price() << '\n'
           << std::setw(width) << "Units:         " << x.units() << "\n\n";
    }

    return os;
}

int main(void)
{
    std::vector<int> v{3,5,6,7};
    std::cout << v;
    std::vector<Purchase> prh;
    prh.push_back(Purchase{"TV", 255.5, 10});
    prh.push_back(Purchase{"Microwave", 65.33, 5});

    Order od1{"Andrew", "North Dakota, P543", prh};
    std::cout << od1;

    std::ifstream fin{"Orders.txt"};
    fin.exceptions(std::ios_base::badbit);
    if(!fin) throw std::runtime_error("Cannot open input file.");
    fin.peek();
    if(fin.eof()) throw std::runtime_error("Input file is empty,");

    std::vector<Order> orders;
    for(Order t{}; fin >> t; orders.push_back(t)){}

    for(const auto& x : orders)
        std::cout << x << '\n';
    return 0;
}
