#ifndef BLIST_H
#define BLIST_H

using namespace std;
#include "BObject.h"
#include <list>

class BList : public BObject, public list<BObject *>
{
    public:
        static const int Type = 2;
        BList();
        virtual void encodeInto(stringstream *stream);
        static BList *parse(istream *input);
        static BList *cast(BObject *obj);
    protected:
        void toStringInternal(int level, stringstream *stream);
    private:
};

#endif // BLIST_H
