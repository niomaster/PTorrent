#ifndef TORRENTMETADATA_H
#define TORRENTMETADATA_H

using namespace std;
#include <string>
#include <list>
#include "FileInfo.h"
#include "BDictionary.h"

class TorrentMetaData
{
    public:
        ~TorrentMetaData();

        string getAnnounce() { return announce; }
        time_t getCreationDate() { return creationDate; }
        string getComment() { return comment; }
        string getCreatedBy() { return createdBy; }
        string getEncoding() { return encoding; }
        int getPieceLength() { return pieceLength; }
        list<string> *getPieces() { return pieces; }
        bool getIsPrivate() { return isPrivate; }
        string getName() { return name; }
        list<FileInfo *> *getFiles() { return files; }

        static TorrentMetaData *create(BDictionary *dictionary);
    protected:
    private:
        TorrentMetaData();

        string announce;
        time_t creationDate;
        string comment;
        string createdBy;
        string encoding;
        int pieceLength;
        list<string> *pieces;
        bool isPrivate;
        string name;
        list<FileInfo *> *files;
};

#endif // TORRENTMETADATA_H
