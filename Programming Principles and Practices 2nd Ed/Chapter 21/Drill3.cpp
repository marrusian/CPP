#include<iostream>
#include<fstream>
#include<iterator>
#include<vector>
#include<algorithm>
#include<numeric>
#include<stdexcept>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    os.precision(static_cast<size_t>(10));
    for(const auto& x : vec)
        os << x << '\n';
    return os;
}

int main(void)
{
    std::ifstream fin{"Floats.txt"};
    if(!fin) throw std::runtime_error("Cannot open input file.");
    fin.peek();
    if(fin.eof()) throw std::runtime_error("Input file is empty.");

    std::vector<double> vd {std::istream_iterator<double>{fin},
                            std::istream_iterator<double>{}};
    fin.close();

    std::cout << vd << '\n';

    std::vector<int> vi(vd.size());
    std::copy(vd.begin(),vd.end(),vi.begin());

    double vdsum = std::accumulate(vd.begin(),vd.end(), 0.0);
    std::cout << "Vd sum: " << vdsum << '\n';
    std::cout << "Vdsum - Visum: "
              << vdsum - static_cast<double>(std::accumulate(vi.begin(), vi.end(), 0))
              << '\n';

    std::reverse(vd.begin(),vd.end());
    std::cout << vd << '\n';

    std::cout << "VD mean value: " << vdsum/vd.size() << '\n';

    return 0;
}
