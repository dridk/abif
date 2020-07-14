#include <iostream>
#include <fstream>
#include <byteswap.h>
#include <tclap/CmdLine.h>
#include "abif.h"
using namespace std;

int main(int argc, char** argv)
{

    TCLAP::CmdLine cmd("ABIF reader", ' ', "0.1");
    TCLAP::SwitchArg listArg("l","list","list all keys");
    TCLAP::ValueArg<std::string> keyArg("k","key","get value from key",false,"","string");
    TCLAP::UnlabeledValueArg<std::string> fileArg( "filename", "abi file", true, "", "filename");

    cmd.xorAdd( keyArg, listArg );
    cmd.add( fileArg );

    cmd.parse( argc, argv );

    std::string key  = keyArg.getValue();
    std::string filename = fileArg.getValue();

    bool isList  = listArg.getValue();


    Abif file = Abif(filename);

    if (isList)
        file.showList();

    else
        cout<<file.value(key).c_str()<<endl;




    return 0;
}

