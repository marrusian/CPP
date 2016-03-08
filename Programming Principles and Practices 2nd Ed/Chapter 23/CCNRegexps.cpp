#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<regex>
#include<stdexcept>
#include<map>
#include<iterator>

/* An ISO/IEC 7812 card number is most commonly 16 digits in length, and can be up to 19 digits.
 * The structure is as follows:
 *     - A 6-digit Issuer Identification Number (IIN) (previously called
 *     the "Bank Identification Number" - BIN) the first digit of which
 *     is the Major Industry Identifier (MII).
 *     - A variable length (up to 12 digits) individual account identifier.
 *     - A single check digit calculated using the Luhn algorithm.
 *
 * Format example of a 16-digit credit card number:
 *     MIII IIAA AAAA AAAC
 *
 *     M:   Major Industry Identifier
 *     M+I: Issuer Identification Number
 *     A:   Account number
 *     C:   Check digit
 *
 * MII digits represent the following issuer categories:
 *     0 – ISO/TC 68 and other future industry assignments
 *     1 – Airlines
 *     2 – Airlines and other future industry assignments
 *     3 – Travel and entertainment and banking/financial
 *     4 – Banking and financial
 *     5 – Banking and financial
 *     6 – Merchandising and banking/financial
 *     7 – Petroleum and other future industry assignments
 *     8 – Healthcare, telecommunications and other future industry assignments
 *     9 – National assignment
 *
 *  IIN Formats:
 *      Issuing network 	        IIN ranges 	            Active  Length  Validation      Symbol
 *      American Express 	        34, 37 	                Yes 	15 	    Luhn algorithm  AmEx
 *      China UnionPay 	            62 	                    Yes 	16-19 	No validation   CUP
 *      Diners Club Carte Blanche 	300-305 	            Yes 	14 	    Luhn algorithm  DC-CB
 *      Diners Club International 	300-305, 309,           Yes 	14 	    Luhn algorithm  DC-Int
 *                                  36, 38-39
 *      Diners Club USA & Canada 	54, 55 	                Yes 	16 	    Luhn algorithm  DC-UC
 *      Discover Card 	            6011, 64-65             Yes 	16 	    Luhn algorithm  Disc
 *      InterPaymentTM 	            636 	                Yes 	16-19 	Luhn algorithm
 *      InstaPayment 	            637-639 	            Yes 	16 	    Luhn algorithm  IPI
 *      JCB 	                    3528-3589 	            Yes 	16 	    Luhn algorithm  JCB
 *      Maestro 	                5018, 5020, 5038,       Yes 	12-19 	Luhn algorithm  Maes
 *                                  5612, 5893, 6304,
 *                                  6759, 6761, 6762,
 *                                  6763, 0604, 6390
 *      Dankort 	                5019 	                Yes 	16 	    Luhn algorithm
 *      MasterCard 	                51-55 	                Yes 	16 	    Luhn algorithm  MC
 *      Visa 	                    4 	                    Yes 	13, 16 	Luhn algorithm  Visa
 *      Visa Electron 	            4026, 417500, 4405,     Yes 	16 	    Luhn algorithm  Visa
 *                                  4508, 4844, 4913,
 *                                  4917
 *
 *  Relevant links:
 *     https://www.discovernetwork.com/merchants/images/Merchant_Marketing_PDF.pdf
 *     https://www.discovernetwork.com/value-added-reseller/images/Discover_IIN_Bulletin_April_2014.pdf
*/

template<typename Target, typename Source>
Target to(Source arg)
{
    std::stringstream interpreter;
    Target result;
    if(!(interpreter<<arg)
            || !(interpreter>>result)
            || !(interpreter>>std::ws).eof())
        throw std::runtime_error("to<>() failed.");
    return result;
}

struct Luhn
{
    /*
     *  See http://en.wikipedia.org/wiki/Luhn_algorithm for a detailed description.
     *  This implementation is designed to be compatible with all kinds of iterators
     *  by using the STL's advance and distance algorithms and providing a std::string
     *  specialization.
     *  Pre-conditions:
     *    @last is a one-past-the-checkdigit iterator.
    */

    public:
        Luhn() = default;
        template<typename Iter>
        bool operator()(Iter first, Iter last) {return luhn(first,last);}

    private:
        template<typename Iter>
        bool luhn(Iter first, Iter last);

        template<typename Iter, typename int_type>
        bool luhn(Iter first, Iter last, int_type);

        template<typename Iter>
        bool luhn(Iter first, Iter last, std::string::value_type);

        static bool is_separator(const std::string::value_type& x);
};

inline bool Luhn::is_separator(const std::string::value_type& x)
{
    if(isblank(x)||x=='-') return true;
    return false;
}

template<typename Iter>
bool Luhn::luhn(Iter first, Iter last, std::string::value_type)
{
    size_t sum{};
    size_t checkdigit{1};

    if(first!=last){
        Iter dummy{first};
        std::advance(dummy,std::distance(first,last)-1);
        checkdigit = to<size_t,std::string::value_type>(*dummy);

        size_t delims{static_cast<size_t>(std::count_if(first,last,is_separator))};

        for(size_t dist{}, temp{}; (dist = std::distance(first,last)-1) && dist>0; ++first){
            dist -= delims;
            while(is_separator(*first)){
                ++first;
                --delims;
            }
            if(dist&1){
                temp = 2*to<size_t,std::string::value_type>(*first);
                if(temp>=10)
                    sum+=temp-9;
                else
                    sum+=temp;
                }
            else
                sum += to<size_t,std::string::value_type>(*first);
        }
    }

    if(!((sum+checkdigit)%10))
        return true;

    return false;
}

template<typename Iter, typename int_type>
bool Luhn::luhn(Iter first, Iter last, int_type)
{
    size_t sum{};
    size_t checkdigit{1};

    if(first!=last){
        Iter dummy{first};
        std::advance(dummy,std::distance(first,last)-1);
        checkdigit = *dummy;

        for(size_t dist{}, temp{}; (dist = std::distance(first,last)-1) && dist>0; ++first)
            if(dist&1){
                temp = 2*(*first);
                if(temp>=10)
                    sum+=temp-9;
                else
                    sum+=temp;
                }
            else
                sum += *first;
    }

    if(!((sum+checkdigit)%10))
        return true;

    return false;
}

template<typename Iter>
bool Luhn::luhn(Iter first, Iter last)
{
    return luhn(first, last, *first);
}

struct PAN_Validator
{
    /*
     * Brief description:
     *   - Blanks and dashes are allowed, but only after the PAN's IIN.
     *   - Consecutive blanks are allowed.      (e.g. 5189  7431   0442     3923)
     *   - Consecutive dashes are NOT allowed.  (e.g. 5215--xxx)
     *   - Mixing:
     *             a. Consecutive delimiters    (e.g. 5253 - xxxx)
     *             b. Sequence delimiters       (e.g. 5123 4831-xxxx)
     *     is NOT allowed.
     *
     * Legend: PAN = Primary Account Number.
     *         IIN = Issuer Identification Number.
    */

    public:
        enum class CreditCards{AmEx, CUP, DClub, DCard, JCB, VisaE, Visa, MC, Maes, Dank, IPI, ITP, UNID};

        PAN_Validator(){init_map(); init_vector();}

        const std::regex& pan(size_t i) const {return pans[i];}
        const std::regex& pan(CreditCards i) const {return pans[static_cast<size_t>(i)];}

        const std::string& name(size_t i) const {return pan_names.at(static_cast<CreditCards>(i));}
        const std::string& name(CreditCards i) const {return pan_names.at(i);}

        size_t size() const {return pans.size();}

        template<typename Iter>
        bool validate(Iter first, Iter last) {return lhn(first,last);}

    private:
        std::vector<std::regex> pans;
        std::map<CreditCards,std::string> pan_names;
        Luhn lhn;
        void init_map();
        void init_vector();
};

void PAN_Validator::init_map()
{
    pan_names.insert
    ({
        {CreditCards::AmEx,  "American Express"},
        {CreditCards::CUP,   "China UnionPay"},
        {CreditCards::DClub, "Diners Club"},
        {CreditCards::DCard, "Discover Card"},
        {CreditCards::JCB,   "JCB"},
        {CreditCards::Visa,  "Visa"},
        {CreditCards::VisaE, "Visa Electron"},
        {CreditCards::MC,    "MasterCard"},
        {CreditCards::Maes,  "Maestro"},
        {CreditCards::Dank,  "Dankort"},
        {CreditCards::IPI,   "InstaPayment"},
        {CreditCards::ITP,   "InterPayment"},
        {CreditCards::UNID,  "Unidentified Card"}
    });
}

void PAN_Validator::init_vector()
{
    constexpr size_t PAN_REGEXPS = 13;

    std::ifstream fin{"panregexps.txt"};
    if(!fin) throw std::runtime_error("Cannot open \"panregexps.txt\".");
    if(fin.peek()==EOF) throw std::runtime_error("\"panregexps.txt\" is empty.");

    pans.resize(PAN_REGEXPS);
    size_t i{};
    for(std::string temp; std::getline(fin,temp); ++i)
        pans[i] = temp;
}

int main(void)
{
    PAN_Validator pv;
    std::regex GenericCCN{R"(\b(?:(?:\d-?){12,19}|(?:\d *){12,19})\b)"};

    std::ifstream fin{"CCNs.txt"};
    if(!fin) throw std::runtime_error("Cannot open input file.");
    if(fin.peek()==EOF) throw std::runtime_error("Input file is empty.");

    size_t linenum{1};
    size_t i{};
    for(std::string line; std::getline(fin,line); ++linenum){
        std::smatch specific_match;
        std::smatch generic_match;
        if(std::regex_search(line, generic_match, GenericCCN)){
            for(i = 0; i < pv.size() && specific_match.empty(); ++i)
                std::regex_search(generic_match.str(), specific_match, pv.pan(i));

            std::cout << pv.name(i-1) << ": " << specific_match[0];
            line = specific_match.str();
            if(pv.validate(line.begin(),line.end()))
                std::cout << " is valid.\n";
            else
                std::cout << " isn't valid.\n";
        }
    }

    return 0;
}
