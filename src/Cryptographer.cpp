#include "../include/Cryptographer.h"
#define EXTRA_DATA 9
#define CHUNK_LENGTH 64

#define zeroize(data, start, end) \
for (int __i = start; __i <= end; __i++) { \
    data[__i] = 0;\
}
#define leftrotate(value, n) ((value << (n)) | (value >> (32 - (n))))

void Cryptographer::processSha1Chunk(Sha1Values *values, unsigned char *chunk)
{
    unsigned int *words = (unsigned int *)chunk;
    for (int i = 16; i < 80; i++)
    {
        words[i] = leftrotate(words[i - 3] ^ words[i - 8] ^ words[i - 14] ^ words[i-16], 1);
    }

    uint a = values->h0;
    uint b = values->h1;
    uint c = values->h2;
    uint d = values->h3;
    uint e = values->h4;

    uint f, k, temp;

    for (int i = 0; i < 80; i++)
    {
        switch(i / 20)
        {
            case 0:
                f = (b & c) | ((~b) & d);
                k = 0x5A827999;
                break;
            case 1:
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
                break;
            case 2:
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
                break;
            case 3:
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
                break;
        }

        temp = leftrotate(a, 5) + f + e + k + words[i];
        e = d;
        d = c;
        c = leftrotate(b, 30);
        b = a;
        a = temp;
    }

    values->h0 += a;
    values->h1 += b;
    values->h2 += c;
    values->h3 += d;
    values->h4 += e;
}

unsigned char *Cryptographer::getSha1(istream *data, unsigned long byteCount)
{
    Sha1Values state;

    long chunks = byteCount / CHUNK_LENGTH;
    unsigned char buffer[320];
    int i = 0;

    for(;i < chunks; i++)
    {
        data->read((char *)buffer, CHUNK_LENGTH);

        int read = data->gcount();
        if (read == CHUNK_LENGTH)
        {
            processSha1Chunk(&state, buffer);
        }
        else
        {
            byteCount = i * CHUNK_LENGTH + read;
            break;
        }
    }

    int position = byteCount % CHUNK_LENGTH;
    if (i == chunks && (position != 0))
    {
        data->read((char *)buffer, byteCount % CHUNK_LENGTH);
    }

    if (position > CHUNK_LENGTH - EXTRA_DATA)
    {
        buffer[position] = 128;
        zeroize(buffer, position + 1, CHUNK_LENGTH - 1)
        processSha1Chunk(&state, buffer);
        position = 0;
    }
    else
    {
        buffer[position] = 128;
        position++;
    }

    unsigned long bitCount = byteCount * 8;

    zeroize(buffer, position, CHUNK_LENGTH - 9);
    for (int i = 0; i < 8; i++)
    {
        buffer[CHUNK_LENGTH - 8 + i] = ((unsigned char *)&bitCount)[7 - i];
    }

    processSha1Chunk(&state, buffer);

    unsigned char *result = new unsigned char[20];
    memcpy(result, &state, 20);

    return result;
}
