#include<iostream>
#include<map>
#include<string>
#include<numeric>
#include<functional>

// Named Function
inline double weighted_value(const std::pair<std::string,double>& a,
                             const std::pair<std::string,double>& b)
{return a.second*b.second;}

// Function Object (functor)
struct Weight{
    double operator()(const std::pair<std::string,double>& a,
                      const std::pair<std::string,double>& b)
    {return a.second*b.second;}
};

int main(void)
{
    std::map<std::string,double> dow_price = {
        {"MMM", 81.86},
        {"AA", 34.69},
        {"MO", 54.45}
    };

    std::map<std::string,double> dow_weight = {
        {"MMM", 5.8549},
        {"AA", 2.4808},
        {"MO", 3.8940}
    };

    std::map<std::string,std::string> dow_name = {
        {"MMM", "3M Co."},
        {"AA", "Alcoa Inc."},
        {"MO", "Altria Group Inc."}
    };

    for(const auto& x : dow_price){
        std::cout << x.first << '\t'
                  << x.second << '\t'
                  << dow_name[x.first] << '\n';
    }


    double dji_index = std::inner_product(dow_price.begin(), dow_price.end(),
                                          dow_weight.begin(), 0.0,
                                          std::plus<double>{}, weighted_value);
    std::cout << dji_index << '\n';


    return 0;
}
