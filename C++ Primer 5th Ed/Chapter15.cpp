#include <iostream>
#include <string>

using std::cout; using std::cin; using std::endl;

class Quote
{
public:
    Quote() = default;
    Quote(const std::string& book, double sales_price) :
                    price(sales_price), bookNo(book) {  }
    virtual ~Quote() = default;

    const std::string& isbn() const {return bookNo;}
    virtual double net_price(std::size_t n) const {return n*price;}

protected:
    double price = 0.0;

private:
    std::string bookNo;
};

class BulkQuote : public Quote
{
public:
    BulkQuote() = default;
    BulkQuote(const std::string& book, double p,
              std::size_t qty, double disc) :
                    Quote(book, p), minQty{qty}, discount{disc} {  }

    double net_price(std::size_t) const override;

private:
    std::size_t minQty = 0;
    double discount = 0.0;
};

double BulkQuote::net_price(std::size_t cnt) const
{
    return cnt>=minQty? cnt*(1-discount)*price : cnt*price;
}

double print_total(std::ostream& os, const Quote &item, size_t n)
{
    double ret = item.net_price(n);
    os << "ISBN: "   << item.isbn()
       << " #sold: " << n
       << " total due: " << ret
       << endl;

    return ret;
}

int main(void)
{

    return 0;
}