#include <iostream>
#include <initializer_list>
#include <memory>
#include <vector>
#include <stdexcept>
#include <iterator>
#include <functional>
#include <map>
#include <set>
#include <fstream>
#include <sstream>

using std::cout; using std::cin; using std::endl;

template <typename T>
class BlobPtr;

template <typename T>
class Blob
{
public:
    friend class BlobPtr<T>;

    using size_type = typename std::vector<T>::size_type;

    Blob();
    Blob(std::initializer_list<T> il);

    // Capacity
    size_type size() const {return data->size();}
    bool empty() const {return data->empty();}

    // Modifiers
    void push_back(const T& t) {data->push_back(t);}
    void pop_back();

    // Access
    const T& front() const;
    T& front();
    const T& back() const;
    T& back();

    // Pointers
    BlobPtr<T> begin() {return BlobPtr<T>(*this);}
    BlobPtr<T> end() {return BlobPtr<T>(*this, data->size());}

private:
    std::shared_ptr<std::vector<T>> data;
    void check(size_type i, const std::string &msg) const;
};

template <typename T>
Blob<T>::Blob() : data(std::make_shared<std::vector<T>>()) {}

template <typename T>
Blob<T>::Blob(std::initializer_list<T> il) :
     data(std::make_shared<std::vector<T>>(il)) {}

template <typename T>
void Blob<T>::check(size_type i, const std::string &msg) const
{
    if(i >= data->size())
        throw std::out_of_range(msg);
}

template <typename T>
const T& Blob<T>::front() const
{
    return const_cast<Blob*>(this)->front();
}

template <typename T>
T& Blob<T>::front()
{
    check(0, "front() on empty Blob");
    return data->front();
}

template <typename T>
const T& Blob<T>::back() const
{
    return const_cast<Blob*>(this)->back();
}

template <typename T>
T& Blob<T>::back()
{
    check(0, "back() on empty Blob");
    return data->back();
}

template <typename T>
void Blob<T>::pop_back()
{
    check(0, "pop_back() on empty Blob");
    return data->pop_back();
}

template <typename T>
std::vector<T>* f126a(void)
{
    return new std::vector<T>;
}

template <typename T>
std::vector<T>* f126b(std::vector<T>* pvec)
{
    std::iostream::iostate oldState = cin.rdstate();
    cin.clear();

    std::istream_iterator<T> isit(cin), eof;
    pvec->insert(pvec->begin(), isit, eof);

    cin.clear(oldState);
    return pvec;
}

template <typename T>
void f126c(std::vector<T>* pvec)
{
    std::ostream_iterator<T> osit(cout, " ");
    std::copy(pvec->begin(), pvec->end(), osit);
    cout << endl;

    delete pvec;
}

template <typename T>
std::shared_ptr<std::vector<T>> f127a(void)
{
    return std::make_shared<std::vector<T>>();
}

template <typename T>
std::shared_ptr<std::vector<T>> f127b(std::shared_ptr<std::vector<T>> spvec)
{
    std::iostream::iostate oldState = cin.rdstate();
    cin.clear();

    std::istream_iterator<T> isit(cin), eof;
    spvec->insert(spvec->begin(), isit, eof);

    cin.clear(oldState);
    return spvec;
}

template <typename T>
void f127c(std::shared_ptr<std::vector<T>> spvec)
{
    std::ostream_iterator<T> osit(cout, " ");
    std::copy(spvec->begin(), spvec->end(), osit);
    cout << endl;
}

template <typename T>
void process(std::shared_ptr<T> sptr)
{
    cout << sptr.use_count() << endl;
}

template <typename T>
class BlobPtr
{
public:
    BlobPtr() : curr(0) { }
    BlobPtr(Blob<T> &a, size_t sz = 0) : 
        wptr(a.data), curr(sz) { }

    T& operator*() const;
    T* operator->() const;

    BlobPtr& operator++();
    BlobPtr operator++(int);
    BlobPtr& operator--();
    BlobPtr operator--(int);

private:
    std::weak_ptr<std::vector<T>> wptr;
    std::size_t curr;

    std::shared_ptr<std::vector<T>>
        check(std::size_t, const std::string&) const;
};

template <typename T>
std::shared_ptr<std::vector<T>>
BlobPtr<T>::check(std::size_t i, const std::string &msg) const
{
    auto ret = wptr.lock();
    if(!ret)
        throw std::runtime_error("Unbound BlobPtr");

    if(i >= ret->size())
        throw std::out_of_range(msg);

    return ret;
}

template <typename T>
T& BlobPtr<T>::operator*() const
{
    auto p = check(curr, "Dereference past end");
    return (*p)[curr];
}

template <typename T>
T* BlobPtr<T>::operator->() const
{
    return &this->operator*(); // return &(**this);
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator++()
{
    check(curr, "Increment past end of BlobPtr");
    ++curr;

    return *this;
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator--()
{
    --curr;
    check(curr, "Decrement past begin of BlobPtr");

    return *this;
}

template <typename T>
BlobPtr<T> BlobPtr<T>::operator++(int)
{
    BlobPtr temp = *this;
    ++*this;

    return temp;
}

template <typename T>
BlobPtr<T> BlobPtr<T>::operator--(int)
{
    BlobPtr temp = *this;
    --*this;

    return temp;
}

void f1223a(const char* str1, const char* str2)
{
    size_t new_size = 0;

    for(auto temp = str1; *temp; ++temp)
        ++new_size;
    for(auto temp = str2; *temp; ++temp)
        ++new_size;

    char *new_str = new char[new_size+1];
    auto temp = new_str;

    while(*str1)
        *temp++ = *str1++;
    while(*str2)
        *temp++ = *str2++;
    *temp = '\0';

    cout << new_str << endl;
}

void f1223b(const std::string& str1, const std::string& str2)
{
    cout << str1+str2 << endl;
}

void f1224(void)
{
    std::iostream::iostate oldState = cin.rdstate();
    cin.clear();

    size_t size = 10;
    char *str = new char[size+1];

    char ch = '\0';
    size_t i = 0;
    while(cin.get(ch)){
        if(i == size){
            char *str_new = new char[(size *= 2) + 1];
            std::copy(str, str+size, str_new);
            delete[] str;
            str = str_new;
        }

        str[i++] = ch;
    }
    str[i] = '\0';

    cout << str << endl;

    cin.clear(oldState);
}

class QueryResult
{
    friend std::ostream& operator<<(std::ostream&, const QueryResult&);
public:
    using line_no = std::vector<std::string>::size_type;

    QueryResult(std::string s,
                std::shared_ptr<std::set<line_no>> p,
                std::shared_ptr<std::vector<std::string>> f):
        sought(s), lines(p), file(f) {}
private:
    std::string sought;
    std::shared_ptr<std::set<line_no>> lines;
    std::shared_ptr<std::vector<std::string>> file;
};

std::ostream& operator<<(std::ostream& os, const QueryResult &qr)
{
    os << qr.sought << " occurs " << qr.lines->size() << " "
       << " time(s)" << endl;

    for(auto num : *qr.lines)
        os << "\t(line " << num+1 << ") "
           << (*qr.file)[num] << endl;

    return os;
}

class TextQuery
{
public:
    using line_no = std::vector<std::string>::size_type;

    TextQuery(std::ifstream&);
    QueryResult query(const std::string&) const;

private:
    std::shared_ptr<std::vector<std::string>> file;
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

TextQuery::TextQuery(std::ifstream& ifs) :
     file(new std::vector<std::string>)
{
    std::string text;
        
    while(getline(ifs, text)){
        file->emplace_back(text);
        auto n = file->size() - 1;
        std::istringstream line(text);
        std::string word;
        while(line >> word){
            auto &lines = wm[word];
            if(!lines)
                lines.reset(new std::set<line_no>);
            lines->emplace(n);
        }
    }
}

QueryResult TextQuery::query(const std::string& sought) const
{
    static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);

    auto loc = wm.find(sought);
    if(loc == wm.end())
        return QueryResult(sought, nodata, file);
    else
        return QueryResult(sought, loc->second, file);
}

void runQueries(std::ifstream &inFile)
{
    TextQuery tq(inFile);

    std::string choice;

    cout << "Enter word to look for, or q to quit: ";
    while(cin >> choice && choice != "q") {
        cout << tq.query(choice);
        cout << "Enter word to look for, or q to quit: ";
    }
}

int main(void)
{
    const Blob<int> p{2,3,5};
    cout << p.back() << " " << p.front() << endl;

    f126c(f126b(f126a<int>()));
    f127c(f127b(f127a<int>()));

    std::unique_ptr<int> u1(new int(52));

    std::shared_ptr<int> pi(new int());
    std::weak_ptr<int> w(pi);

    f1223a("Scandura ", "Beata");
    f1223b("Scandura ", "Beata");
    f1224();

    std::ifstream ifs("Chapter12.cpp");
    runQueries(ifs);

    return 0;
}