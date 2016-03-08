#include<iostream>
#include<stdexcept>
#include"Matrix11.h"
#include"MatrixIO11.h"
#include<cmath>
#include<random>
#include<functional>
#include<vector>

using Index  = Numeric_lib::Index;

Vector random_vector(Index n)
{
    Vector v(n);
    std::default_random_engine rand{};
    std::uniform_real_distribution<> ureal{0,10};

    for(Index i = 0; i<n; ++i)
        v(i) = ureal(rand);

    return v;
}

int main(void)
{
    std::cout << random_vector(8) << '\n';

    auto gen = std::bind(std::normal_distribution<double>{15,5.0},
                         std::default_random_engine{});

    std::vector<int> hist(2*15);
    for(size_t i{}; i<800; ++i)
        ++hist[static_cast<int>(std::round(gen()))];

    for(size_t i{}; i!=hist.size(); ++i){
        std::cout << i << '\t';
        for(ssize_t j{}; j!=hist[i]; ++j)
            std::cout << '*';
        std::cout << '\n';
    }

    return 0;
}
