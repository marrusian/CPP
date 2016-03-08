#include<iostream>

template<typename Elem>
class List;

template<typename Elem>
struct Link{
    friend class List<Elem>;
    Link(Elem v = Elem(), Link* p = nullptr, Link* s = nullptr): val{v}, prev{p}, succ{s} {}

    Elem val;
    Link* prev;
    Link* succ;
};

template<typename Elem>
class List{
    public:
        using value_type = Elem;
        using size_type = size_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        class iterator;
        class const_iterator;

        List(Link<Elem>* def = new Link<Elem>{}): first{def}, last{def} {}
	~List() {delete first;}

        iterator begin() {return iterator{first};}
        const_iterator begin() const {return const_iterator{first};}
        const_iterator cbegin() const {return const_iterator{first};}
        iterator end() {return iterator{last};}
        const_iterator end() const {return const_iterator{last};}
        const_iterator cend() const {return const_iterator{last};}

        iterator insert(iterator p, const_reference v);
        iterator erase(iterator p);

        reference front() {return first->val;}
        const_reference front() const {return first->val;}
        reference back() {return last->prev->val;}
        const_reference back() const {return last->prev->val;}

        void push_front(const_reference v);
        void push_back(const_reference v);
        void pop_front();
        void pop_back();

        void clear() {while(first!=last) pop_front();}

        bool empty() const {return first==last;}
        size_type size() const;
        size_type max_size() const {return ((size_t)-1)/(sizeof(Link<Elem>));}

    private:
        Link<Elem>* first;
        Link<Elem>* last;       // Past-the-end Link;
};

template<typename Elem>
class List<Elem>::iterator{
    public:
        iterator(Link<Elem>* it): curr{it} {}

        reference operator*() {return curr->val;}
        pointer operator->() {return curr->val;}

        iterator operator++() {curr = curr->succ; return *this;}
        iterator operator--() {curr = curr->prev; return *this;}

        bool operator==(const iterator& b) const {return curr==b.curr;}
        bool operator!=(const iterator& b) const {return curr!=b.curr;}

    private:
        Link<Elem>* curr;
};


template<typename Elem>
class List<Elem>::const_iterator{
    public:
        const_iterator(Link<Elem>* it): curr{it} {}

        const_reference operator*() const {return curr->val;}
        const_pointer operator->() const {return curr->val;}

        const_iterator operator++() {curr = curr->succ; return *this;}
        const_iterator operator--() {curr = curr->prev; return *this;}

        bool operator==(const const_iterator& b) const {return curr==b.curr;}
        bool operator!=(const const_iterator& b) const {return curr!=b.curr;}

    private:
        Link<Elem>* curr;
};

template<typename Elem>
typename List<Elem>::size_type List<Elem>::size() const
{
    size_type sz{};
    for(auto iter = cbegin(), iterEnd = cend(); iter != iterEnd; ++iter)
        ++sz;

    return sz;
}

template<typename Elem>
void List<Elem>::push_back(const_reference v)
{
    Link<Elem>* newLink = new Link<Elem>{v};

    last->val = newLink->val;
    last->succ = newLink;
    newLink->prev = last;
    last = newLink;
}

template<typename Elem>
void List<Elem>::push_front(const_reference v)
{
    Link<Elem>* newLink = new Link<Elem>{v};

    newLink->succ = first;
    first->prev = newLink;
    first = newLink;
}

template<typename Elem>
void List<Elem>::pop_front()
{
    Link<Elem>* pTemp = first;
    first = first->succ;
    first->prev = nullptr;
    delete pTemp;
}

template<typename Elem>
void List<Elem>::pop_back()
{
    Link<Elem>* pTemp = last;
    last = last->prev;
    last->succ = nullptr;
    delete pTemp;
}


int main(void)
{
    List<int> lst;
    lst.push_front(5);

    std::cout << lst.back();



    return 0;
}
