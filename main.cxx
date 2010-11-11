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
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

// PROJECT INCLUDES
#include "cxxcache.h"

// GLOBAL VARIABLES
cache IL1(CACHETYPE_L1);
cache DL2(CACHETYPE_L1);
cache L2(CACHETYPE_L2);
main_memory mem;

unsigned long long cc; // cycle count
unsigned long long ic; // instruction count

extern void get_config (string filename);
extern void printParameters();

unsigned fetch(unsigned addr);

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

   // initialize cycle and instruction counts
   cc = 0;
   ic = 0;
   
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

	 case 'B':   // branch. one cycle to execute

	    break;
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

// returns time taken to fetch 
unsigned fetch(unsigned addr)
{
   unsigned delay = 0;

   if (L1.hit(addr))
   {
      delay += L1.get_tHit(); // L1 hit
   }
   else
   {  // L1 miss
      delay += L1.get_tMiss();

      // FETCH, add time accordingly
      if (L2.hit(addr))
      {
         delay += L2.get_tHit();  // L2 hit
         
         // now need to write to L1
         // number of transfers = L1.blockSize / L2.busWidth
         delay += L2.get_tTransfer() * (L1.get_blockSize() / L2.get_busWidth());

         // WRITE TO L1
      }
      else
      {
         delay += L2.get_tMiss();	  // L2 miss
         // fetch from main memory
         // send address, wait for memory to be ready
         delay += mem.get_tSendAddr() + mem.get_tReady();	  
         // calculate number of chunks, multiply by tChunk
         delay += mem.get_tChunk() * (L2.get_blockSize() / mem.get_chunkSize());

         // WRITE TO L2
         
         // WRITE TO L1
      }
   }

   return delay;
}
