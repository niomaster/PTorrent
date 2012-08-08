#include "../include/BInt.h"

BInt::BInt(int value)
{
    this->value = value;
    this->type = Type;
}

void BInt::encodeInto(stringstream *stream)
{
    *stream << "i" << value << "e";
}

BInt *BInt::parse(istream *input)
{
    if(input->get() != 'i')
    {
        throw 42;
    }

    int sign = 1;
    if(input->peek() == '-')
    {
        input->get();
        sign = -1;
    }

    if(input->peek() == 'e')
    {
        throw 42;
    }

    char nextChar;
    int value = 0;
    while((nextChar = input->get()) != 'e')
    {
        if(nextChar < '0' || nextChar > '9')
            throw 42;

        value = value * 10 + (nextChar - '0');
    }

    return new BInt(sign * value);
}

BInt *BInt::cast(BObject *obj)
{
    if(obj->type != BInt::Type)
    {
        throw 42;
    }

    return (BInt *)obj;
}

void BInt::toStringInternal(int level, stringstream *stream)
{
    *stream << value;
}
