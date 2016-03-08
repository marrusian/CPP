#include<iostream>
#include<fstream>
#include<iomanip>
#include<vector>
#include<string>
#include<iterator>
#include<algorithm>
#include<stdexcept>

struct Item{
    Item() = default;
    Item(const std::string& s, int id, double val): name{s}, iid{id}, value{val} {}

    std::string name;
    int iid;
    double value;
};

struct ItemByName{
    bool operator()(const Item& itm1, const Item& itm2) const
        {return itm1.name<itm2.name;}
};

struct ItemByID{
    bool operator()(const Item& itm1, const Item& itm2) const
        {return itm1.iid<itm2.iid;}
};

struct ItemByVal{
    bool operator()(const Item& itm1, const Item& itm2) const
        {return itm1.value<itm2.value;}
};

class FindID{
        int id;
    public:
        FindID(int idn): id{idn} {}
        bool operator()(const Item& x) const {return x.iid==id;}
};

class FindName{
        std::string nm;
    public:
        FindName(const std::string& s): nm{s} {}
        bool operator()(const Item& x) const {return x.name==nm;}
};

std::istream& operator>>(std::istream& is, Item& it)
{
    Item temp{};
    std::getline(is,temp.name);
    is >> temp.iid >> temp.value;

    if(!is) return is;

    it = temp;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Item& it)
{
    return os << '{'  << std::setw(10) << it.name  << ", "
                      << std::setw(5)  << it.iid   << ", "
                      << std::setw(5)  << it.value
              << '}';
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for(const auto& x : vec)
        os << x << '\n';
    return os;
}

int main(void)
{
    std::ifstream fin{"Items.txt"};
    if(!fin) throw std::runtime_error("Cannot open input file.");
    fin.peek();
    if(fin.eof()) throw std::runtime_error("Input file is empty.");

    std::vector<Item> vi{std::istream_iterator<Item>{fin},
                         std::istream_iterator<Item>{}};
    fin.close();

    std::cout << vi << '\n';

    std::stable_sort(vi.begin(), vi.end(), ItemByName{});
    std::cout << vi << '\n';
    std::stable_sort(vi.begin(), vi.end(), ItemByID{});
    std::cout << vi << '\n';
    std::stable_sort(vi.begin(), vi.end(), ItemByVal{});
    for(size_t i = vi.size(); i; --i)
        std::cout << vi[i-1] << '\n';

    std::cout << '\n';
    auto p = std::find_if(vi.begin(), vi.end(), FindID{5});
    if(p!=vi.end())
        vi.erase(p);
    p = std::find_if(vi.begin(), vi.end(), FindID{9});
    if(p!=vi.end())
        vi.erase(p);

    std::cout << vi << '\n';

    p = std::find_if(vi.begin(), vi.end(), FindName{"Dagger"});
    if(p!=vi.end())
        vi.erase(p);
    p = std::find_if(vi.begin(), vi.end(), FindName{"Helmet"});
    if(p!=vi.end())
        vi.erase(p);

    std::cout << vi << '\n';

    return 0;
}
