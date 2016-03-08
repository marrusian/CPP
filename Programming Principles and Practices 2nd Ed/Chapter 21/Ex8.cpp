#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include<stdexcept>
#include<algorithm>

struct bySize{
  bool operator()(const std::pair<std::string,size_t>& p1,
                  const std::pair<std::string,size_t>& p2) const
  {return p1.second>p2.second;}
};

int main(void)
{
  std::map<std::string,size_t> freq;

  std::ifstream fin{"FileFreq.txt"};
  if(!fin) throw std::runtime_error("Cannot open input file.");
  fin.peek();
  if(fin.eof()) throw std::runtime_error("Input file is empty");

  for(std::string temp; fin >> temp; ++freq[temp]){}

  std::vector<std::pair<std::string,size_t> > vp(freq.size());
  std::copy(freq.begin(),freq.end(), vp.begin());
  std::stable_sort(vp.begin(),vp.end(), bySize{});

  for(const auto& x : vp)
    std::cout << x.second << ": " << x.first << '\n';

  return 0;
}
