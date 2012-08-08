#ifndef BINT_H
#define BINT_H

#include "BObject.h"

class BInt : public BObject
{
    public:
        static const int Type = 0;
        int value;
        BInt(int value);
        virtual void encodeInto(stringstream *stream);
        static BInt *parse(istream *input);
        static BInt *cast(BObject *obj);
    protected:
        void toStringInternal(int level, stringstream *stream);
    private:
};

#endif // BINT_H
