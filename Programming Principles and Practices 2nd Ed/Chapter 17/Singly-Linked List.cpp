#include<iostream>
#include<sstream>
#include<string>

//  - insert: insert before an element;
//  - add: insert after an element;
//  - erase: remove an element;
//  - find: find a Link with a given value;
//  - advance: get the n-th succesor.

class Node
{
  public:
    Node(std::string s, Node* nd = nullptr): m_Name{s}, m_pNext{nd}{}
    const std::string& name() const{return m_Name;}
    Node* next() const{return m_pNext;}

    void set_name(const std::string& name){m_Name = name;}

  private:
    std::string m_Name;
    Node* m_pNext;

    friend class SingleList;
};

class SingleList
{
  public:
    SingleList(Node* nd1 = nullptr):p_mHead{nd1}, p_mTail{nd1}{}
    ~SingleList(){clear();}

    const Node* front() const {return p_mTail;}
    bool empty() const {return p_mHead == nullptr;}

    Node* begin() {return p_mTail;}
    const Node* cbegin() const {return p_mTail;}

    Node* end() {return p_mHead->m_pNext;}
    const Node* cend() const {return p_mHead->m_pNext;}

    Node* insert_after(Node*, const std::string&);
    Node* erase_after(Node*, Node*);
    Node* erase_after(Node*);
    void push_front(const std::string&);
    void pop_front();
    void remove(const std::string&);
    void clear();

  private:
    Node* p_mHead;
    Node* p_mTail;
};

void SingleList::push_front(const std::string& name)
{
  Node* pNewNode = new Node{name};

  if(!p_mHead)
  {
    p_mHead = pNewNode;
    p_mTail = p_mHead;
  }
  else
  {
    pNewNode->m_pNext = p_mTail;
    p_mTail = pNewNode;
  }
}

void SingleList::pop_front()
{
  if(p_mTail)
  {
        Node* pTemp = p_mTail;
        p_mTail = p_mTail->m_pNext;
        delete pTemp;
  }
  else if(p_mHead)
    p_mHead = nullptr;
}

void SingleList::clear(){while(p_mHead) pop_front();}

void SingleList::remove(const std::string& args)
{
  Node* prev = nullptr;
  for(Node* l = p_mTail; l ; prev = l, l = l->m_pNext)
    if(l->m_Name == args){
        prev->m_pNext = l->m_pNext;
        delete l;
        break;
     }
}

Node* SingleList::erase_after(Node* nd)
{
  Node* pTemp = nd->m_pNext;
  nd->m_pNext = pTemp->m_pNext;
  delete pTemp;
  return nd->m_pNext;
}

Node* SingleList::erase_after(Node* nd1, Node* nd2)
{
  nd1->m_pNext = nd2;
  for(Node* pTemp = nd1->m_pNext; pTemp != nd2; pTemp = pTemp->m_pNext)
    delete pTemp;

  return nd2;
}

Node* SingleList::insert_after(Node* n, const std::string& val)
{
  Node* pNewNode = new Node{val};

  pNewNode->m_pNext = n->m_pNext;
  n->m_pNext = pNewNode;

  return pNewNode;
}

int main(void)
{

  SingleList norse_gods{new Node{"Thor"}};
  norse_gods.push_front("Odin");
  norse_gods.push_front("Zeus");
  norse_gods.push_front("Freia");

  SingleList greek_gods{new Node{"Hera"}};
  greek_gods.push_front("Athena");
  greek_gods.push_front("Mars");
  greek_gods.push_front("Poseidon");

  greek_gods.push_front("Zeus");
  norse_gods.remove("Zeus");

  for(Node* l = norse_gods.begin(); l ; l = l->next())
    std::cout << l->name() << '\n';

  std::cout << std::endl;

  for(Node* l = greek_gods.begin(); l ; l = l->next())
    std::cout << l->name() << '\n';


  return 0;
}
