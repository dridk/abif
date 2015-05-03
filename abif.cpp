#include "abif.h"
#include <cstring>
#include <iomanip>
Abif::Abif(const std::string& filename)
{
    mFile = new ifstream(filename, ios::binary|ios::in);

    if (mFile->is_open())
    {
        char abif[4];

        // read Abif
        mFile->seekg(0);
        mFile->read(abif,4);


        // read version
        mFile->seekg(4);
        mFile->read((char*)(&mVersion), sizeof(short));
        mVersion = __bswap_16(mVersion);

        // Read root dir
        mFile->seekg(6);
        mFile->read((char*)(&mRootDir), sizeof(AbifDir));
        mRootDir = swap(mRootDir);


        // Read all dirs
        for (int i=0; i<mRootDir.numElements; ++i)
        {
            AbifDir  dir;
            mFile->seekg(mRootDir.dataOffset + sizeof(AbifDir) * i);
            mFile->read((char*)(&dir), sizeof(AbifDir));
            dir = swap(dir);

            // remove \0
            string key = dir.name;
            key.erase(key.size()-1, 1);
            key = key + string(".") + std::to_string(dir.number);
            mDirs[key] = dir;
        }
    }
}

Abif::~Abif()
{
    mFile->close();
    delete mFile;
}

void Abif::showList()
{
    map<string, AbifDir>::iterator it;

    //print header
    cout<<"NAME"<<"\t" //
        <<"NUMBER"<<"\t"//
        <<"ELEMENT TYPE"<<"\t"
        <<"ELEMENT SIZE"<<"\t"
        <<"NUM ELEMENTS"<<"\t"
        <<"DATA SIZE"<<"\t"
        <<"DATA OFFSET"<<"\t"
        <<"DATA HANDLE"<<"\t"
        <<endl;

    for(it = mDirs.begin();it != mDirs.end(); ++it)
    {
        AbifDir d = it->second;
        cout<<it->first <<"\t"
        <<d.number<<"\t"
        <<d.elementType<<"\t"
        <<d.elementsize<<"\t"
        <<d.numElements<<"\t"
        <<d.dataSize<<"\t"
        <<d.dataOffset<<"\t"
        <<d.dataHandle<<"\t"
        <<endl;
    }

}
string Abif::value(const string &key)
{
    if (mDirs.count(key) >= 1) {
        AbifDir dir = mDirs[key];
        char * bytes = new char[dir.dataSize];
        //        cout<<"name:\t"<<dir.name<<endl;
        //        cout<<"type:\t"<<dir.elementType<<endl;
        //        cout<<"e.size:\t"<<dir.elementsize<<endl;
        //        cout<<"size:\t"<<dir.dataSize<<endl;
        //        cout<<"offset:\t"<<dir.dataOffset<<endl;

        if (dir.dataSize <=4)
        {
            int32_t tmp = __bswap_32(dir.dataOffset);
            std::memcpy(bytes,&tmp,dir.dataSize);
        }

        else
        {
            mFile->seekg(dir.dataOffset);
            if(!mFile->read(bytes,dir.dataSize))
                cout<<"cannot read file"<<endl;
        }


        // check types...........
        if (dir.elementType == PString){
            string out = string(bytes);
            return out;
        }

        if (dir.elementType == CString){
            string out = string(bytes);
            return out;
        }

        if (dir.elementType == Byte)
            return convert<unsigned char>(dir.numElements,bytes);

        if (dir.elementType == Char)
            return convert<char>(dir.numElements,bytes);

        if (dir.elementType == Word)
            return convert<uint16_t>(dir.numElements,bytes);

        if (dir.elementType == Short)
            return convert<short>(dir.numElements,bytes);

        if (dir.elementType == Long)
            return convert<int32_t>(dir.numElements,bytes);

        if (dir.elementType == Float)
            return convert<float>(dir.numElements,bytes);

        if (dir.elementType == Double)
            return convert<double>(dir.numElements,bytes);

        return "cannot decode";

    }
    return "key not present";
}
AbifDir Abif::swap(AbifDir dir)
{
    dir.number        = __bswap_32(dir.number);
    dir.elementType   = __bswap_16(dir.elementType);
    dir.elementsize   = __bswap_16(dir.elementsize);
    dir.numElements   = __bswap_32(dir.numElements);
    dir.dataSize      = __bswap_32(dir.dataSize);
    dir.dataOffset    = __bswap_32(dir.dataOffset);
    dir.dataHandle    = __bswap_32(dir.dataHandle);

    return dir;
}



template <class T>
string Abif::convert(int numElements, char *bytes)
{
    string out;
    for (int i=0; i<numElements; i+=sizeof(T))
    {
        T value;
        std::memcpy(&value, &bytes[i], sizeof(T));

        if (sizeof(T) == 2)
            value = __bswap_16(value);

        if (sizeof(T) == 4)
            value = __bswap_32(value);

        if (sizeof(T) == 8)
            value = __bswap_64(value);

        out += i == 0 ? "" : ",";
        out += std::to_string(value);
    }
    return out;
}
