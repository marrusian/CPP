#ifndef MESSAGE_H
#define MESSAGE_H

#include <iosfwd>
#include <set>
#include <string>

class Folder;
class Message
{
    friend class Folder;
    friend void swap(Message& lhs, Message& rhs);
    friend std::ostream& operator<<(std::ostream&, const Message&);

public:
    explicit Message(const std::string& str = std::string()) :
        contents(str) { }

    Message(const Message&);
    Message(Message&&);
    ~Message();

    Message& operator=(const Message&);
    Message& operator=(Message&&);

    void save(Folder&);
    void remove(Folder&);

    void addFld(Folder*);
    void remFld(Folder*);

private:
    std::string contents;
    std::set<Folder*> folders;

    void move_Folders(Message*);
    void add_to_Folders(const Message&);
    void remove_from_Folders();
};

#endif