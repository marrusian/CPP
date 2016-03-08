#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<stdexcept>

using Line_iter = std::vector<std::string>::const_iterator;

class Message{  // Points to the first and last lines of a message
    public:
        explicit Message(Line_iter p1, Line_iter p2): first{p1}, last{p2} {}

        Line_iter begin() const {return first;}
        Line_iter end() const {return last;}

    private:
        Line_iter first;
        Line_iter last;
};

std::ostream& operator<<(std::ostream& os, const Message& m)
{
    for(const std::string& s : m)
        os << s << '\n';
    return os;
}

using Mess_iter = std::vector<Message>::const_iterator;

struct Mail_file{                   // Holds all lines from a file and
                                      // simplifies access to messages
    std::string name;               // file name
    std::vector<std::string> lines; // the lines in order
    std::vector<Message> m;         // the messages in order

    Mail_file(const std::string& n);// read file n into lines

    Mess_iter begin() const {return m.begin();}
    Mess_iter end() const {return m.end();}
};

Mail_file::Mail_file(const std::string& n): name{n}
{
    std::ifstream fin{n};
    fin.exceptions(std::ios_base::badbit);
    if(!fin) throw std::runtime_error("Cannot open input file " + n);
    if(fin.peek()==EOF) throw std::runtime_error("Input file " + n + " is empty.");

    for(std::string temp; std::getline(fin,temp); lines.push_back(temp)){}

    auto mstart = lines.begin();
    for(auto it = lines.begin(); it != lines.end(); ++it){
        if(*it=="----"){
            m.push_back(Message{mstart,it});
            mstart = it+1;
        }
    }
}

size_t is_prefix(const std::string& s, const std::string& p)
{
    size_t n = p.size();
    if(s.substr(0, n) == p) return n;
    return 0;
}

// Find the name of the sender in a Message
// and store it in s.
bool find_from_addr(const Message* m, std::string& s)
{
    for(const std::string& x : *m)
        if(size_t n = is_prefix(x, "From: ")){
            s = x.substr(n);
            return true;
        }

    return false;
}

// Return the subject of the Message, if any.
std::string find_subject(const Message* m)
{
    for(const std::string& x : *m)
        if(size_t n = is_prefix(x, "Subject: ")){
            return x.substr(n);
        }

    return "";
}

int main(void)
{
    Mail_file mf{"mailfile.txt"};

    std::multimap<std::string, const Message*> sender;

    for(const auto& m : mf){
        std::string s;
        if(find_from_addr(&m, s))
            sender.insert(std::make_pair(s,&m));
    }

    auto pp = sender.equal_range("John Doe <jdoe@machine.example>");
    for(auto p = pp.first; p!=pp.second; ++p)
        std::cout << find_subject(p->second) << '\n';

    return 0;
}
