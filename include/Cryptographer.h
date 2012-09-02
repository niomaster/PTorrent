#ifndef CRYPTOGRAPHER_H
#define CRYPTOGRAPHER_H

typedef unsigned int uint;
typedef struct Sha1Values
{
    Sha1Values() : h0(0x67452301), h1(0xEFCDAB89), h2(0x98BADCFE), h3(0x10325476), h4(0xC3D2E1F0){}
    uint h0;
    uint h1;
    uint h2;
    uint h3;
    uint h4;
} Sha1Values;

#include <iostream>
#include <string.h>

using namespace std;

class Cryptographer
{
    public:
        // Generates SHA1 hash for the next ´length' bytes of the stream (or until end of stream)
        static unsigned char *getSha1(istream *data, unsigned long byteCount);
    protected:
    private:
        static void processSha1Chunk(Sha1Values *values, unsigned char *chunk);
};

#endif // CRYPTOGRAPHER_H
