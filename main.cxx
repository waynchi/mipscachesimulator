// main.c
// main file for cachesim project
// ECEN4593 F2010
//
// Danny Gale, Chris Messick
//
// Revision History:
// 11/2/2010   Danny Gale  created
// 11/2/2010   Danny Gale  converted to C++

using namespace std;

// COMPILER INCLUDES
//#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

// PROJECT INCLUDES
#include "cxxcache.h"

// GLOBAL VARIABLES
L1_cache L1;
L2_cache L2;
main_memory mem;
unsigned long long cc; // cycle count

// DEFINES
// #define strlen 80 //shouldn't be necessary in C++ when using string type

extern void get_config (string filename);
extern void printParameters();

int main(int argc, char * argv[])
{
   int i = 0;
   int addr;
   int exec;
   char op;
   ifstream configFile;
   string str;

   // print info
   cout << "====================" << endl << "MIPS Cache Simulator" << endl << "ECEN4593, F2010" << endl;
   cout << "University of Colorado at Boulder" << endl << "Danny Gale, Chris Messick" << endl << "====================" << endl << endl;

   // initialize cycle count
   cc = 0;
   
   // check for too many parameters
   if (argc > 2)
      cerr << "Proper usage: zcat <tracefile> | ./cachesim <configfile>" << endl;
   // use default config values if no config file specified
   else if (argc == 1)
   {
      cout << "No config file. Using default parameters" << endl;
   }
   // get values from config file
   else
   {
      str = argv[1];
      get_config(str);

      ///////
      //THIS IS WRONG
      //SHOULD BE FOR STDIN, NOT CONFIG FILE
      //while (!configFile.eof())
	 //configFile >> op >> hex >> addr >> hex >> exec;
   }
   printParameters();


   // BEGIN ACCEPTING TRACE CODE HERE
   cout << endl << "=============";
   cout << "Begin Trace";
   cout << "==============" << endl;
   while (!cin.eof())
   {
      cin >> op >> hex >> addr >> hex >> exec;
      cout << "op: " << op << "\taddr: " << setw(8) << hex << addr << "\texec: " << setw(8) << hex << exec << endl;
   }

   return 0;
}
