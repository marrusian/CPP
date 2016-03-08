#include "message.h"
#include "folder.h"

#include <iostream>

void Message::move_Folders(Message* msg)
{
    folders = std::move(msg->folders);
    for(auto f : folders){
        f->remMsg(msg);
        f->addMsg(this);
    }
    msg->folders.clear();
}

void Message::add_to_Folders(const Message& msg)
{
    for(auto f : msg.folders)
        f->addMsg(this);
}

void Message::remove_from_Folders()
{
    for(auto f : folders)
        f->remMsg(this);
}

Message::Message(const Message& msg) :
    contents(msg.contents), folders(msg.folders)
{
    add_to_Folders(msg);
}

Message::Message(Message&& msg) : 
    contents(std::move(msg.contents))
{
    move_Folders(&msg);
}

Message& Message::operator=(const Message& msg)
{
    remove_from_Folders();

    contents = msg.contents;
    folders  = msg.folders;

    add_to_Folders(msg);

    return *this;
}

Message& Message::operator=(Message&& msg)
{
    if(this != &msg){
        remove_from_Folders();
        contents = std::move(msg.contents);
        move_Folders(&msg);
    }

    return *this;
}

Message::~Message()
{
    remove_from_Folders();
}

void Message::save(Folder& f)
{
    folders.emplace(&f);
    f.addMsg(this);
}

void Message::remove(Folder& f)
{
    folders.erase(&f);
    f.remMsg(this);
}

void Message::addFld(Folder* f)
{
    folders.emplace(f);
}

void Message::remFld(Folder* f)
{
    folders.erase(f);
}

void swap(Message& lhs, Message& rhs)
{
    using std::swap;

    lhs.remove_from_Folders();
    rhs.remove_from_Folders();

    swap(lhs.contents, rhs.contents);
    swap(lhs.folders, rhs.folders);

    lhs.add_to_Folders(lhs);
    rhs.add_to_Folders(rhs);
}

std::ostream& operator<<(std::ostream& os, const Message& msg)
{
    return os << msg.contents;
}