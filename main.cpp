#include "include/BInt.h"
#include "include/BString.h"
#include "include/BList.h"
#include "include/BDictionary.h"
#include "include/TorrentMetaData.h"
#include "include/Cryptographer.h"

using namespace std;
#include <iostream>
#include <fstream>
#include <map>
#include <stdlib.h>

#include <stdio.h>

void assertEquals(int a, int b, string testname)
{
    if(a != b)
    {
        cout << "Test \"" << testname << "\"failed: " << a << " != " << b << endl;
        exit(1);
    }
    else
    {
        cout << "Test \"" << testname << "\" passed. (" << a << ")" << endl;
    }
}

void assertEquals(string a, string b, string testname)
{
    if(a != b)
    {
        cout << "Test \"" << testname << "\" failed: " << endl << a << endl << " != " << endl << b << endl;
        exit(1);
    }
    else
    {
        cout << "Test \"" << testname << "\" passed. (" << a << ")" << endl;
    }
}

void testBInt() { assertEquals((new BInt(3))->encode(), "i3e", "BInt test 1"); }
void testBInt2() { assertEquals((new BInt(-12))->encode(), "i-12e", "BInt test 2"); }

void testBString() { assertEquals((new BString("bacon"))->encode(), "5:bacon", "BString test 1"); }
void testBString2() { assertEquals((new BString(""))->encode(), "0:", "BString test 2"); }

void testBList()
{
    BList *list = new BList();
    list->push_back(new BInt(3));
    list->push_back(new BString("and eggs!"));
    list->push_back(new BInt(-42));

    assertEquals(list->encode(), "li3e9:and eggs!i-42ee", "BList test 1");
}

void testBDictionary()
{
    BDictionary *dict = new BDictionary();
    dict->insert(pair<string, BObject *>("publisher", new BString("bob")));
    dict->insert(pair<string, BObject *>("publisher-webpage", new BString("www.example.com")));
    dict->insert(pair<string, BObject *>("publisher.location", new BString("home")));

    assertEquals(dict->encode(),
        "d9:publisher3:bob17:publisher-webpage15:www.example.com18:publisher.location4:homee",
        "BDictionary test 1");
}

void testBNested()
{
    BDictionary *dict = new BDictionary();
    BList *dict_list = new BList();
    BDictionary * dict_list_dict = new BDictionary();
    (*dict_list_dict)["hoi"] = new BString("hallo");
    dict_list->push_back(dict_list_dict);
    dict_list->push_back(new BInt(3142));
    (*dict)["goedenavond"] = new BString("slaap lekker");
    (*dict)["goeiemorgen"] = dict_list;
    (*dict)["'; DROP TABLE *;--"] = new BInt(0);

    assertEquals(dict->encode(),
        "d18:'; DROP TABLE *;--i0e11:goedenavond12:slaap lekker11:goeiemorgenld3:hoi5:halloei3142eee",
        "Nested BObject test");
}

void testBParseInt()
{
    stringstream *stream = new stringstream();
    *stream << "i3e5:12345";
    assertEquals(BInt::parse(stream)->value, 3, "BParse Int test");
}

void testBParseString()
{
    stringstream *stream = new stringstream();
    *stream << "5:12345i4e";
    assertEquals(BString::parse(stream)->value, "12345", "BParse String test");
}

void testBParseList()
{
    stringstream *stream = new stringstream();
    *stream << "li3ei-3e5:bacon4:eggse";
    assertEquals(BObject::parse(stream)->encode(), "li3ei-3e5:bacon4:eggse", "BParse List test");
}

void testBParseDictionary()
{
    stringstream *stream = new stringstream();
    *stream << "d3:cow3:moo7:awesomel6:pieter4:teunee";
    assertEquals(BObject::parse(stream)->encode(),
        "d7:awesomel6:pieter4:teune3:cow3:mooe",
        "BParse Dictionary test");
}

char toHexit(char byte)
{
    return byte < 10 ? '0' + byte : 'a' + (byte - 10);
}

string toHexString(unsigned char* data, int byteCount)
{
    stringstream *stream = new stringstream();
    for(int i = 0; i < byteCount; i++)
    {
        *stream << toHexit(data[i] / 16) << toHexit(data[i] % 16);
    }

    return stream->str();
}

void testToHex()
{
    assertEquals("2120414dabcd", toHexString((unsigned char *)"! AM\xab\xcd", 6), "Hex test");
}

void testSha1()
{
    stringstream *stream = new stringstream();
    /**stream << "The quick brown fox jumps over the lazy dog";
    assertEquals(toHexString(Cryptographer::getSha1(stream, 43), 20),
                 "2fd4e1c67a2d28fced849ee1bb76e7391b93eb12",
                 "Sha1 test");*/
    *stream << "abc";
    assertEquals(toHexString(Cryptographer::getSha1(stream, 3), 20),
                 "2fd4e1c67a2d28fced849ee1bb76e7391b93eb12",
                 "Sha1 test");
}

void testTorrentMetaDataRead(string filename)
{
    ifstream fileStream;
    fileStream.open(filename.c_str());
    BDictionary *dictionary = BDictionary::parse(&fileStream);
    fileStream.close();

    //cout << dictionary->toStringPWRT();

    TorrentMetaData *metaData = TorrentMetaData::create(dictionary);
    delete dictionary;
    time_t copy = metaData->getCreationDate();
    tm *time = localtime(&copy);
    char data[100];
    strftime((char *)data, 99, "%d-%m-%Y %H:%M:%S", time);
    cout << endl << "Torrent created by " << metaData->getCreatedBy() << " on " << data << endl
         << "Announce: " << metaData->getAnnounce() << endl
         << "Encoding: " << metaData->getEncoding() << endl
         << "Comment: \"" << metaData->getComment() << "\"" << endl
         << metaData->getFiles()->size() << " Files in " << metaData->getPieces()->size() << " pieces" << endl << endl;
    delete metaData;
}

#define TEST
#undef BTEST
#undef FIDDLE

int main()
{
    #ifdef BTEST
    testBInt();
    testBInt2();
    testBString();
    testBString2();
    testBList();
    testBDictionary();
    testBNested();

    testBParseInt();
    testBParseString();
    testBParseList();
    testBParseDictionary();
    #endif

    #ifdef TEST
    testToHex();
    testSha1();
    #endif

    #ifdef FIDDLE
    testTorrentMetaDataRead("/home/pieter/test2.torrent");
    #endif

    cout << "All tests passed. Yay! ^_^" << endl;
    return 0;
}
