#include<iostream>
#include<vector>
#include<algorithm>
#include<type_traits>

template<typename T>
void heapify(T&, size_t);

//template<typename T>
//void siftUp(T&, size_t, size_t = 0);

template<typename T>
void siftDown(T& arr, size_t, size_t);

template<typename T>
void heapify(T& arr, size_t sz)
{
    long int i = (sz-2)/2;   // Parent of the last element
    while(i >= 0){
        siftDown(arr, i, sz-1);
        --i;
    }
}

/*
template<typename T>
void siftUp(T& arr, size_t node, size_t root = 0)
{
    size_t child = node;
    size_t parent;
    while(child > root){
        parent = (child-1)/2;
        if(arr[parent] < arr[child]){
            std::swap(arr[parent],arr[child]);
            child = parent;
        }
        else return;
    }
}
*/

template<typename T>
void heap_sort(T& arr, size_t sz)
{
    heapify(arr,arr.size());
    size_t i = sz-1;
    while(i){
        std::swap(arr[i],arr[0]);   // 0 is the root
        --i;
        siftDown(arr, 0, i);
    }
}

template<typename T>
void siftDown(T& arr, size_t start, size_t end)
{
    size_t root = start;
    size_t child = root*2+1;
    size_t swid = root;
    while(child <= end){

        if(arr[swid] < arr[child])
            swid = child;
        if(child+1 <= end && arr[swid] < arr[child+1])
            swid = child+1;

        if(swid != root){
            std::swap(arr[root], arr[swid]);
            root = swid;
        }
        else return;

        child = root*2+1;
    }
}

template<typename Iter>
void insertion_sort(Iter first, Iter last, size_t dec = 1)
{
    Iter j;
    auto x = *first;
    for(Iter i = first; i != last; ++i){
        j = i;
        x = *i;
        while(j >= first && *(j-dec) > x){
            j -= dec;
            *(j+dec) = *j;
        }
        *j = x;
    }
}

template<typename T>
void shell_sort(T& arr, size_t sz)
{
    size_t h = 1;
    while(h<sz) h = 3*h+1;
    while(h){
        h /= 3;
        insertion_sort(arr.begin()+h, arr.end(), h);
    }
}


/* Almost sorted data-oriented implementation.
template<typename T>
void insertion_sort(T& arr, size_t sz)
{
    size_t j;
    typename std::remove_reference<decltype(arr[0])>::type x;
    for(size_t i = 1; i < sz; ++i){
        if(arr[i-1] > arr[i]){
            j = i;
            x = arr[i];
            do{
                --j;
                arr[j+1] = arr[j];
            } while(j && arr[j-1] > x);

            arr[j] = x;
        }
    }
}
*/

int main(void)
{
    constexpr size_t N = 100000000;
    std::vector<int> v{62, 83, 18, 53, 7, 17, 95, 86, 47, 69, 25, 28, 5, 76, 71, 0, 33};

    shell_sort(v, v.size());
    insertion_sort(v.begin(), v.end());
    heap_sort(v,v.size());

    return 0;
}
