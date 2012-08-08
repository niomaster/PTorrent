#include "../include/BObject.h"

string BObject::encode()
{
    stringstream *stream = new stringstream();
    encodeInto(stream);
    return stream->str();
}

BObject *BObject::parse(istream *input)
{
    switch(input->peek())
    {
        case 'i':
            return BInt::parse(input);
            break;
        case '0'...'9':
            return BString::parse(input);
            break;
        case 'l':
            return BList::parse(input);
            break;
        case 'd':
            return BDictionary::parse(input);
            break;
        default:
            throw 42;
            //TODO create better exception
    }
}

void BObject::indent(int level, stringstream *stream)
{
    for(int i = 0; i < level; i++)
    {
        *stream << "  ";
    }
}

string BObject::toString()
{
    stringstream *stream = new stringstream();
    toStringInternal(0, stream);
    return stream->str();
}
