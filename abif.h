#ifndef ABIF_H
#define ABIF_H
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <byteswap.h>

using namespace std;

struct AbifDir{
   char name[4];
   int32_t number;
   int16_t elementType;
   int16_t elementsize;
   int32_t numElements;
   int32_t dataSize;
   int32_t dataOffset;
   int32_t dataHandle;

};

class Abif
{
public:
    enum Type {
        Byte    = 1,
        Char    = 2,
        Word    = 3,
        Short   = 4,
        Long    = 5,
        Float   = 7,
        Double  = 8,
        Date    = 10,
        Time    = 11,
        PString = 18,
        CString = 19,
        Thumb   = 12,
        Bool    = 13,
        User    = 1024
    };

    Abif(const std::string& filename);
    ~Abif();

    void showList();
    void showAll();
    string value(const string& key) ;

    template <class T>
    string convert(int numElements, char * bytes);


protected:
    AbifDir swap(AbifDir dir);


   private:
    bool mIsAbif;
    short mVersion;
    ifstream * mFile;
    AbifDir mRootDir;
    map<string,AbifDir> mDirs;


};

#endif // ABIF_H
