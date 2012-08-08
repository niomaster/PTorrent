#include "../include/TorrentMetaData.h"

TorrentMetaData::TorrentMetaData()
{
    files = new list<FileInfo *>();
    pieces = new list<string>();
}

TorrentMetaData *TorrentMetaData::create(BDictionary *dictionary)
{
    TorrentMetaData *data = new TorrentMetaData();
    BDictionary *info = BDictionary::cast(dictionary->get("info"));

    data->announce = BString::cast(dictionary->get("announce"))->value;
    data->createdBy = dictionary->findString("created by");
    data->creationDate = dictionary->findInt("creation date");
    data->comment = dictionary->findString("comment");
    data->encoding = dictionary->findString("encoding");
    data->pieceLength = BInt::cast(info->get("piece length"))->value;

    string pieces = BString::cast(info->get("pieces"))->value;
    int piecesCount = pieces.size() / 20;
    for(int i = 0; i < piecesCount; i++)
    {
        data->pieces->push_back(pieces.substr(i * 20, 20));
    }

    data->isPrivate = dictionary->findInt("private") == 1;
    data->name = BString::cast(info->get("name"))->value;

    if(info->contains("files"))
    {
        BList *files = BList::cast(info->get("files"));

        for(list<BObject *>::iterator i = files->begin(); i != files->end(); ++i)
        {
            BDictionary *fileInfo = BDictionary::cast(*i);
            FileInfo *file = new FileInfo();

            BList *pathList = BList::cast(fileInfo->get("path"));
            file->path = "";
            for(list<BObject *>::iterator i = pathList->begin(); i != pathList->end(); ++i)
            {
                file->path.append(BString::cast(*i)->value);
            }

            file->length = BInt::cast(fileInfo->get("length"))->value;
            file->md5sum = fileInfo->findString("md5sum");

            data->files->push_back(file);
        }
    }
    else
    {
        FileInfo *file = new FileInfo();
        file->path = data->name;
        file->length = BInt::cast(info->get("length"))->value;
        file->md5sum = info->findString("md5sum");
        data->files->push_back(file);
    }

    return data;
}

TorrentMetaData::~TorrentMetaData()
{
    delete files;
    delete pieces;
}
