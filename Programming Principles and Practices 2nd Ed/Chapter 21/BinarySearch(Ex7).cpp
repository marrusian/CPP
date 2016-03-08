#include<iostream>
#include<iterator>

template<typename BDIter, typename T>
BDIter Binary_Search(BDIter first, BDIter last, const T& val, std::bidirectional_iterator_tag)
{
    BDIter failure = last;
    BDIter mid{};

    while(first!=mid && mid!=last){
        mid = first;
        std::advance(mid,std::distance(first,last)/2);

        if(*mid>val){
            last = mid;
            --last;
        }
        else if(*mid<val){
            first = mid;
            ++first;
        }
        else return mid;
    }

    return failure;
}

template<typename Iter, typename T, typename Iter_Category>
Iter Binary_Search(Iter first, Iter last, const T& val, Iter_Category)
{
    Iter failure = last;
    Iter mid{};

    while(first!=mid && mid!=last){
        mid = first;
        std::advance(mid,std::distance(first,last)/2);

        if(*mid>val){
            last = first;
            std::advance(last,std::distance(first,mid)-1);
        }
        else if(*mid<val){
            first = mid;
            ++first;
        }
        else return mid;
    }

    return failure;
}

template<typename Iter, typename T>
Iter Binary_Search(Iter first, Iter last, const T& val)
{
    return Binary_Search(first, last, val,
                         typename std::iterator_traits<Iter>::iterator_category());
}

int main(void)
{



    return 0;
}
