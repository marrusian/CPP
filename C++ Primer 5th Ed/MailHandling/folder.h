#ifndef FOLDER_H
#define FOLDER_H

#include <iosfwd>
#include <set>

class Message;
class Folder
{
    friend std::ostream& operator<<(std::ostream&, const Folder&);
public:
    Folder() = default;

    Folder(const Folder&);
    Folder(Folder&&);
    ~Folder();

    Folder& operator=(const Folder&);
    Folder& operator=(Folder&&);

    void save(Message &m);
    void remove(Message &m);

    void addMsg(Message* msg);
    void remMsg(Message* msg);

private:
    std::set<Message*> messages;

    void move_Messages(Folder*);
    void add_to_Messages(const Folder&);
    void remove_from_Messages();
};

#endif