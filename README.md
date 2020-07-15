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
## Display all keys 

    abif -l example.fsa
    
    NAME    NUMBER  ELEMENT TYPE    ELEMENT SIZE    NUM ELEMENTS    DATA SIZE       DATA OFFSET     DATA HANDLE
    CTID.1  1       19      1       22      22      75479   0
    CTNM.1  1       19      1       22      22      75501   0
    CTOw.1  1       19      1       3       3       1936392192      0

  
## Display value from key

    abif -k DATA.1 example.fsa 
    
    0,2,-4,2,-1,-6,-3,0,-3,-2,-1,-1,-2,-3,-8,-2,-4,3,0,1,0,0,-3,0,3,-4,-1,-1,-4,-4,-2,-3,-2,1,-1,-2,-3,-5,0,0,0,-2,-4,-2,0,-2,-3,0,-8,-2,-1,-2,-6,-2,-4,2,-2,2,-6,0,-5,-4,-3,1,-6,0,-3,-3,-3,-4,-2,-5,-1,-5,-4,-2,-3,-1,-3,-6,-4,-5,-6,-3,-1,-3,-3,-1,-2,-4,-3,-1,-2,-3,-7,-5,0,-4,-3,-1,-4,-6,-5,-9,-6,-2,-3,-7,-3,-6,-9,-8,-3,-3,-4,-7,-3,-8,-3,-7,-1,-4,-6,-4,-5,0,-4,-2,0,-3,-1,-3,-9,-3,-4,-2,-7,-8,-4,-5,-3,-7,1,-5,0,-4,-9,-6,-9,0,-6,-4,-6,-4,-9,-8,-6,-9,-6,-4,-5,0,-3,-4,-5,-7,-4,0,-6,-2,-3,-6,-4,-4,-6,-3,-6,-6,-4,-3,-2,-8,-5,-7,-5,-5,-4,-4,-2,-8,-10,-3,-2,-2,-4,-5,-3,-6,-8,-3,-9,-5,-7,-6,-10,-8,-8,-4,-4,-2,-5,-5,-4,-10,-1,-8,-6,-7,-6,-4,-3,-4,-8,-1,-4,-4,-4,-5,-3,-4,-6,-3,0,-6,-5,-4,-5,-6,-4,-1,-6,-5,-4,-9,-3,-4,-5,-5,-4,-4,-3,-7 ...
    
## Plot trace with gnuplot 

     ./abif -k DATA.1 ../CutePeaks/examples/A_forward.ab1 | tr "," "\n"|gnuplot -p -e 'plot "/dev/stdin" using 0:1 with lines'







