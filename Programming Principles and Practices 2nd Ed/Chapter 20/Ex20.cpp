#include<iostream>
#include<chrono>
#include<list>
#include<vector>
#include<cstdlib>
#include<fstream>
#include<stdexcept>

int main(void)
{
    size_t N = 500;
    constexpr size_t limit = 1000000;
    srand(static_cast<size_t>(time(NULL)));

    std::vector<int> v;
    std::vector<int>::iterator iter;
    std::vector<int>::iterator iterEnd;

    std::list<int> lst;
    std::list<int>::iterator iterl;
    std::list<int>::iterator iterlEnd;

    std::ofstream fout{"timingsO3V2.txt"};
    if(!fout) throw std::runtime_error("Cannot open output file");
    fout.exceptions(fout.exceptions() | std::ios_base::badbit);

    while(N <= limit){
        fout << N << " elements\n";
        v.clear();
        v.reserve(N);
        auto t1 = std::chrono::system_clock::now();
        for(size_t count = 0; count < N; ++count){
            int temp = rand() * (1.0 / (RAND_MAX+1.0)) * N;
            for(iter = v.begin(), iterEnd = v.end(); iter != iterEnd && *iter<=temp; ++iter){}
            v.insert(iter, temp);
        }
        auto t2 = std::chrono::system_clock::now();

        lst.clear();
        auto t3 = std::chrono::system_clock::now();
        for(size_t count = 0; count < N; ++count){
            int temp = rand() * (1.0 / (RAND_MAX+1.0)) * N;
            for(iterl = lst.begin(), iterlEnd = lst.end(); iterl != iterlEnd && *iterl<=temp; ++iterl){}
            lst.insert(iterl, temp);
        }
        auto t4 = std::chrono::system_clock::now();

        fout << "Vector: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count()
                                << " ms\n";
        fout << "List: " << std::chrono::duration_cast<std::chrono::milliseconds>(t4-t3).count()
                              << " ms\n";
        N *= 2;
        fout << std::endl;
}

    return 0;
}
