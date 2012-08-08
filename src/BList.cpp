#include "../include/BList.h"

BList::BList()
{
    type = BList::Type;
}

void BList::encodeInto(stringstream *stream)
{
    *stream << "l";

    for(list<BObject *>::iterator i = begin(); i != end(); ++i)
    {
        (*i)->encodeInto(stream);
    }

    *stream << "e";
}

BList *BList::parse(istream *input)
{
    if(input->get() != 'l')
        throw 42;

    BList *list = new BList();

    while(input->peek() != 'e')
    {
        list->push_back(BObject::parse(input));
    }

    input->get();

    return list;
}

BList *BList::cast(BObject *obj)
{
    if(obj->type != BList::Type)
    {
        throw 42;
    }

    return (BList *)obj;
}

void BList::toStringInternal(int level, stringstream *stream)
{
    *stream << "[" << endl;
    for(list<BObject *>::iterator i = begin(); i != end(); ++i)
    {
        BObject::indent(level + 1, stream);
        (*i)->toStringInternal(level + 1, stream);
        *stream << endl;
    }
    BObject::indent(level, stream);
    *stream << "]" << endl;
}
