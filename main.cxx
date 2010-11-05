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
unsigned long long ic; // instruction count

// DEFINES
// #define strlen 80 //shouldn't be necessary in C++ when using string type

extern void get_config (string filename);
extern void printParameters();

int main(int argc, char * argv[])
{
   char op;
   unsigned addr;
   unsigned exec;
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

      switch (op)
      {
	 ic++;	     // one instruction
	 cc++;	     // one cycle to process the instruction itself
	 case 'C':   // computation. exec contains latency information
	    cc += exec + fetch(addr);
	    break;
	 case 'L':
	    cc += fetch(addr);
	    break;
	 case 'S':
	    break;
      }
   }

   return 0;
}

// returns time taken to fetch instruction
unsigned fetch(unsigned addr)
{
   if (L1.hit(addr))
   {
      cc += L1.get_tHit(); // L1 hit
   }
   else
   {  // L1 miss
      cc += L1.get_tMiss();

      // FETCH, add time accordingly
      if (L2.hit(addr))
      {
         cc += L2.get_tHit();  // L2 hit
         
         // now need to write to L1
         // number of transfers = L1.blockSize / L2.busWidth
         cc += L2.get_tTransfer * (L1.get_blockSize() / L2.get_busWidth);

         // WRITE TO L1
      }
      else
      {  
         cc += L2.get_tMiss();	  // L2 miss
         // fetch from main memory
         // send address, wait for memory to be ready
         cc += mem.get_tSendAddr() + mem.get_tReady();	  
         // calculate number of chunks, multiply by tChunk
         cc += mem.get_tChunk() * (L2.get_blockSize() / mem.get_chunkSize());

         // WRITE TO L2
         
         // WRITE TO L1
      }
   }
}
