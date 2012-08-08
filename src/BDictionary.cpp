#include "../include/BDictionary.h"

BDictionary::BDictionary()
{
    type = BDictionary::Type;
}

void BDictionary::encodeInto(stringstream *stream)
{
    *stream << "d";

    for(map<string, BObject *>::iterator i = begin(); i != end(); ++i)
    {
        BString *string = new BString((*i).first);
        string->encodeInto(stream);
        delete string;
        (*i).second->encodeInto(stream);
    }

    *stream << "e";
}

BDictionary *BDictionary::parse(istream *input)
{
    if(input->get() != 'd')
        throw 42;

    BDictionary *dict = new BDictionary();

    while(input->peek() != 'e')
    {
        BString *key = BString::parse(input);
        BObject *value = BObject::parse(input);
        (*dict)[key->value] = value;
        delete key;
    }

    input->get();

    return dict;
}

BObject *BDictionary::get(string key)
{
    BDictionary::iterator i = this->find(key);
    if(i == end())
        throw 42;
    return i->second;
}

string BDictionary::findString(string key)
{
    BDictionary::iterator i = this->find(key);
    if(i == end())
        return string();

    return BString::cast(i->second)->value;
}

int BDictionary::findInt(string key)
{
    BDictionary::iterator i = this->find(key);
    if(i == end())
        return 0;

    return BInt::cast(i->second)->value;
}

BDictionary *BDictionary::findDictionary(string key)
{
    BDictionary::iterator i = this->find(key);
    if(i == end())
        return 0;

    return BDictionary::cast(i->second);
}

BDictionary *BDictionary::cast(BObject *obj)
{
    if(obj->type != BDictionary::Type)
    {
        throw 42;
    }

    return (BDictionary *)obj;
}

void BDictionary::toStringInternal(int level, stringstream *stream)
{
    bool first = true;

    for(map<string, BObject *>::iterator i = begin(); i != end(); ++i)
    {
        if(!first)
            BObject::indent(level, stream);
        first = false;
        *stream << i->first << " => " << endl;
        BObject::indent(level + 1, stream);
        i->second->toStringInternal(level + 1, stream);
        *stream << endl;
    }
}

bool BDictionary::contains(string key)
{
    return find(key) != end();
}
