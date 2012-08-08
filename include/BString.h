#ifndef BSTRING_H
#define BSTRING_H

#include "BObject.h"

#include <stdlib.h>

class BString : public BObject
{
    public:
        static const int Type = 1;
        string value;
        BString(string value);
        virtual void encodeInto(stringstream *stream);
        static BString *parse(istream *input);
        static BString *cast(BObject *obj);
    protected:
        void toStringInternal(int level, stringstream *stream);
    private:
};

#endif // BSTRING_H
