#include "../include/BString.h"

BString::BString(string value)
{
    this->value = value;
    this->type = Type;
}

void BString::encodeInto(stringstream *stream)
{
    *stream << (int)value.length() << ":" << value.c_str();
}

BString *BString::parse(istream *input)
{
    if(input->peek() == ':')
    {
        throw 42;
    }

    char nextChar;
    int length = 0;
    while((nextChar = input->get()) != ':')
    {
        if(nextChar < '0' || nextChar > '9')
            throw 42;

        length = length * 10 + (nextChar - '0');
    }

    char *value = new char[length];
    input->read(value, length);
    int temp = input->gcount();
    if(temp != length)
    {
        delete value;
        throw 42;
    }

    BString *bstring = new BString(string(value, length));
    delete value;

    return bstring;
}

BString *BString::cast(BObject *obj)
{
    if(obj->type != BString::Type)
    {
        throw 42;
    }

    return (BString *)obj;
}

void BString::toStringInternal(int level, stringstream *stream)
{
    *stream << value;
}
