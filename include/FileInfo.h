#ifndef FILEINFO_H
#define FILEINFO_H

using namespace std;
#include <string>

class FileInfo
{
    public:
        FileInfo();
        long long length;
        string md5sum;
        string path;
    protected:
    private:
};

#endif // FILEINFO_H
