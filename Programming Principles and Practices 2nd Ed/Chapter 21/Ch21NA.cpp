#include<iostream>
#include<vector>
#include<numeric>

struct Record{
    explicit Record (double p = 0.0, int u = 0):unit_price{p}, units{u} {}
    double unit_price;
    int units;
};

inline double price(double v, const Record& r) {return v + r.unit_price*r.units;}

struct Price{
    double operator()(double v, const Record& r) const {return v + r.unit_price*r.units;}
};

int main(void)
{

    std::vector<Record> v{Record{55.25, 100}, Record{25.99, 10},
                          Record{75.99, 1000}, Record{100, 5}};

    std::cout << std::accumulate(v.begin(), v.end(), 0.0, price) << '\n';
    std::cout << std::accumulate(v.begin(), v.end(), 0.0, Price{}) << '\n';
    std::cout << std::accumulate(v.begin(), v.end(), 0.0,
                                 [](double v, const Record& r) {return v + r.unit_price*r.units;});


    return 0;
}
