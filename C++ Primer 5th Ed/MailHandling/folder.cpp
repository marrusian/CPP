#include "folder.h"
#include "message.h"

#include <iostream>

void Folder::move_Messages(Folder* f)
{
    messages = std::move(f->messages);
    for(auto m : messages){
        m->remFld(f);
        m->addFld(this);
    }
    f->messages.clear();
}

void Folder::add_to_Messages(const Folder& f)
{
    for(auto m : f.messages)
        m->addFld(this);
}

void Folder::remove_from_Messages()
{
    for(auto m : messages)
        m->remFld(this);
}

Folder::Folder(const Folder& f) :
    messages(f.messages)
{
    add_to_Messages(f);
}

Folder::Folder(Folder&& f)
{
    move_Messages(&f);
}

Folder& Folder::operator=(const Folder& rhs)
{
    remove_from_Messages();

    messages = rhs.messages;

    add_to_Messages(rhs);

    return *this;
}

Folder& Folder::operator=(Folder&& rhs)
{
    if(this != &rhs){
        remove_from_Messages();
        move_Messages(&rhs);
    }

    return *this;
}

Folder::~Folder()
{
    remove_from_Messages();
}

void Folder::save(Message &m)
{
    messages.emplace(&m);
    m.addFld(this);
}

void Folder::remove(Message &m)
{
    messages.erase(&m);
    m.remFld(this);
}

void Folder::addMsg(Message* msg)
{
    messages.emplace(msg);
}

void Folder::remMsg(Message* msg)
{
    messages.erase(msg);
}

std::ostream& operator<<(std::ostream& os, const Folder& f)
{
    for(auto x : f.messages)
        std::cout << *x << "\n";

    return os;
}