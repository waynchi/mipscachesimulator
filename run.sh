#! /bin/bash
clear
echo "==================================================================="
echo ""
echo "                       MIPS CACHE SIMULATOR                        "
echo "                            run script"
echo ""
echo "                     Danny Gale, Crhis Messick"
echo "                         ECEN4593, F2010"
echo ""
echo "==================================================================="
if [ $# -gt 2 ]
then
   echo "Proper use: ./run.sh CONFIGFILE TRACEFILE"
   exit 1
fi
echo "Cleaning project..."
make clean
echo "Building MIPS cache simulator..."
makeval= make
if [ $makeval -eq ]
then
   echo "Make was successful. Running MIPS cache simulator:"
   more traces/I10 | ./cachesim
fi
