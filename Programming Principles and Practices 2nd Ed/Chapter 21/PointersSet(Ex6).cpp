#include<iostream>
#include<string>
#include<set>

struct Fruit{
    Fruit() = default;
    Fruit(const std::string& nm, size_t c, double up): name{nm}, count{c}, unit_price{up} {}
    std::string name;
    size_t count;
    double unit_price;
    //...
};

struct Fruit_order{
    bool operator()(const Fruit* f1, const Fruit* f2) const {return f1->name < f2->name;}
};

int main(void)
{
    std::set<Fruit*, Fruit_order> inventory;
    inventory.insert(new Fruit{"quince",5,0.66});
    inventory.insert(new Fruit{"apple",200,0.37});

    return 0;
}
