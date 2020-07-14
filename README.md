# Abif
A command line tool to read Applied Biosystems Genetic Analysis Data File Format.

A command line tool to read [ABIF file](http://www6.appliedbiosystems.com/support/software_community/ABIF_File_Format.pdf) for Genetic Analysis. This application can read *.ab1 and *.fsa file . 

# Compilation 
Abif is a C++11 application.
TCLAP is the only one depedency.

    sudo apt-get install libtclap-dev.

# Compilation

    make
    ./abif --version

# Howto 
##Display all keys 

    abif -l example.fsa
    
    NAME    NUMBER  ELEMENT TYPE    ELEMENT SIZE    NUM ELEMENTS    DATA SIZE       DATA OFFSET     DATA HANDLE
    CTID.1  1       19      1       22      22      75479   0
    CTNM.1  1       19      1       22      22      75501   0
    CTOw.1  1       19      1       3       3       1936392192      0

  
## Display value from key

    abif -k DATA.1 example.fsa 
    
    -3
    1
    -7
    -2
    -5

