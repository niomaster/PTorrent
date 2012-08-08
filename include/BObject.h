#ifndef BOBJECT_H
#define BOBJECT_H

using namespace std;
#include <string>
#include <sstream>
#include <map>

class BObject
{
    public:
        virtual void encodeInto(stringstream *stream) = 0;
        string encode();
        static BObject *parse(istream *input);
        int type;
        string toString();
        virtual void toStringInternal(int level, stringstream *stream) = 0;
    protected:
        static void indent(int level, stringstream *stream);
    private:
};

#include "BInt.h"
#include "BString.h"
#include "BList.h"
#include "BDictionary.h"

#endif // BOBJECT_H
