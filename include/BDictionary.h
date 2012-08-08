#ifndef BDICTIONARY_H
#define BDICTIONARY_H

using namespace std;
#include "BObject.h"
#include "BString.h"
#include <map>

class BDictionary : public BObject, public map<string, BObject *>
{
    public:
        static const int Type = 3;
        BDictionary();
        virtual void encodeInto(stringstream *stream);
        BObject *get(string key);
        string findString(string key);
        int findInt(string key);
        BDictionary *findDictionary(string key);
        bool contains(string key);
        static BDictionary *parse(istream *input);
        static BDictionary *cast(BObject *obj);
    protected:
        void toStringInternal(int level, stringstream *stream);
    private:
};

#endif // BDICTIONARY_H
