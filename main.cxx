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
#include "defines.h"

// GLOBAL VARIABLES
cache I(CACHETYPE_L1);
cache D(CACHETYPE_L1);
cache L2(CACHETYPE_L2);
main_memory mem;

unsigned long long cc = 0; // cycle count
unsigned long long ic = 0; // instruction count
unsigned branch, compute, load, store = 0;   // keep track of types of instructions

// EXTERNAL FUNCTIONS
extern void get_config (string filename);
extern void printParameters();

// LOCAL FUNCTIONS
unsigned fetch(cache * thisCache, unsigned addr, op_type op);

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
   

#ifdef _DEBUG_L1_STRUCTURE_
   unsigned i;

#ifdef _DEBUG_L1_STRUCTURE_FAKEDATA_
   unsigned j, val;
   // put some fake data in the instruction cache
   cout << endl << "putting some fake data into L1" << endl;
   for (i = 0; i < I.get_numSets(); i++)
   {
      for (j = 0; j < I.get_set(i)->get_associativity(); j++)
      {
	 val = 0xFFFFFFFF - (i + j);
#ifdef _DEBUG_L1_STRUCTURE_VERBOSE_
	 cout << "setting tag for set " << i << " block " << j << " to " << val << endl;
#endif
	 I.get_set(i)->get_block(j)->set_tag(val);
      }
   }
#endif

   cout << endl << "CACHE L1 STRUCTURE" << endl;
   for (i = 0; i < I.get_numSets(); i++)
   {
      cout << endl;
      cout << dec << "Set#: " << setw(4) << i << " | ";
      I.get_set(i)->output_blocks();
   }
   cout << endl;
#endif
#ifdef _DEBUG_L2_STRUCTURE_
   unsigned k, l;
   cout << endl << "CACHE L2 STRUCTURE" << endl;
   for (k = 0; k < L2.get_numSets(); k++)
   {
      cout << endl;
      cout << "Set#: " << setw(4) << k << " | ";
      for (l = 0; l < L2.get_set(k)->get_associativity(); l++)
      {
	 cout << " " << setw(4) << l;
      }
   }
   cout << endl;
#endif

   // BEGIN ACCEPTING TRACE CODE HERE
   cout << endl << "=============";
   cout << "Begin Trace";
   cout << "==============" << endl;
   while (!cin.eof())
   {
      cout << endl;


      ic++; // increment instruction count

      // GET AN INSTRUCTION
#ifdef _DEBUG_FETCH_
      cout << "========== FETCHING INSTRUCTION ==========" << endl;
#endif
      cin >> op >> hex >> addr >> hex >> exec;
      cout << "inst #:\t" << setw(8) << dec << ic << "\top: " << op << "\taddr: " << setw(8) << hex << addr << "\texec: " << setw(8) << hex << exec << endl;

      cc += fetch(&I, addr, READ);

      cc++; // one cycle to process the instruction itself
      switch (op)
      {
	 case 'B':   // branch. one cycle to execute
	    cc++;
	    branch++;
#ifdef _DEBUG_FETCH_
	    cout << "Branch instruction. No data fetch." << endl;
#endif
	    break;
	 case 'C':   // computation. exec contains latency information
	    cc += exec;
	    compute++;
#ifdef _DEBUG_FETCH_
	    cout << "Computation instruction. No data fetch." << endl;
#endif
	    break;
	 case 'L':   // load. exec contains address of requested data
#ifdef _DEBUG_FETCH_
      cout << "Load instruction." << endl << "========== FETCHING DATA ==========" << endl;
#endif
	    cc += fetch(&D, exec, READ);
	    load++;
	    break;
	 case 'S':   // store. exec contains address of data to be written
#ifdef _DEBUG_FETCH_
      cout << "Store instruction." << endl << "========== FETCHING DATA ==========" << endl;
#endif
	    cc += fetch(&D, exec, WRITE);
	    store++;
	    break;
	 default:
	    cout << "ERROR: INVALID INSTRUCTION TYPE" << endl;
	    exit(ES_INVALID_INSTRUCTION);
	    break;
      }
   }

#ifdef _OUTPUT_CACHES_
   //unsigned m, n = 0;

   cout << endl << "CACHE \"I\" FINAL STATE" << endl;
   for (i = 0; i < I.get_numSets(); i++)
   {
      cout << endl;
      cout << dec << "Set#: " << setw(4) << i << " | ";
      I.get_set(i)->output_blocks();
   }
   cout << endl;
#endif

   return 0;
}

// returns time taken to fetch 
unsigned fetch(cache * thisCache, unsigned addr, op_type operation)
{
#ifdef _DEBUG_FETCH_
   cout << "========== BEGIN _DEBUG_FETCH_ ==========" << endl;
#endif
   unsigned fetchTime = 0;
   unsigned index = thisCache->make_index(addr);
   unsigned tag = thisCache->make_tag(addr);
   cacheLine * ptr = 0;

   // ptr will point to the found block, or will be zero if
   // the block was not found in L1
#ifdef _DEBUG_FETCH_
   cout << "Checking L1 for address " << addr << " using index " << index << " and tag " << tag << endl;
#endif
   ptr = thisCache->hit(index, tag);

   if(ptr)
   {  // L1 hit
      fetchTime += thisCache->get_tHit();
#ifdef _DEBUG_FETCH_
      cout << "address " << addr << " was found in L1" << endl;
      cout << "fetchTime += L1.get_tHit() = " << dec << fetchTime << endl;
#endif
      switch (operation)
      {
	 case READ:
#ifdef _DEBUG_FETCH_
	    cout << "reading " << addr << " from L1" << endl;
#endif
	    thisCache->read(index, tag);
	    break;
	 case WRITE:
#ifdef _DEBUG_FETCH_
	    cout << "writing " << addr << " into L1" << endl;
#endif
	    thisCache->write(index, tag);
	    break;
	 default:
	    cerr << "INVALID CACHE OPERATION" << endl;
	    exit(ES_INVALID_OPERATION);
	    break;
      }
   }
   else
   {  // L1 miss ///////////////////////////////////////////////////
      fetchTime += thisCache->get_tMiss(); 

#ifdef _DEBUG_FETCH_
      cout << "address " << addr << " was NOT found in L1. Going to L2" << endl;
      cout << "fetchTime += L1.get_tMiss = " << dec << fetchTime << endl;
#endif

      // ptr will point to the found block, or will be zero if
      // the block was not found in L2
      ptr = L2.hit(index, tag);

      ///////////////////
      // L2 MISS
      if (!ptr)	  // L2 miss
      {
	 // add time for L2 miss
	 fetchTime += L2.get_tMiss();

	 // add time to read main memory
	 fetchTime += mem.get_tChunk() * (L2.get_blockSize() / mem.get_chunkSize());

#ifdef _DEBUG_FETCH_
      cout << "address " << addr << " was NOT found in L2. Going to main memory" << endl;
      cout << "fetchTime += L2.get_tMiss + mem->L2 transfer = " << dec << fetchTime << endl;
#endif

	 // write the "data" to L2
	 ptr = L2.write(index, tag);
	 //    if a line is evicted, valid, and dirty, write it back to main mem
	 if (ptr && ptr->get_valid() == true && ptr->get_dirty() == true)
	 {
	    // add time to write to main memory
	    fetchTime += mem.get_tChunk() * (L2.get_blockSize() / mem.get_chunkSize());
#ifdef _DEBUG_FETCH_
	    cout << "A line (tag " << ptr->get_tag() << ") was evicted and written back to main memory" << endl;
	    cout << "fetchTime += L2->main mem = " << dec << fetchTime << endl;
#endif
	 }
 
      }
      fetchTime += L2.get_tHit();

#ifdef _DEBUG_FETCH_
      cout << "Address found in L2" << endl;
      cout << "fetchTime += L2.get_tHit = " << dec << fetchTime << endl;
#endif

      ////////////////////
      // WRITE L1 from L2
      ptr = thisCache->write(index, tag);
      // add time for transfer from L2 to L1
      fetchTime += L2.get_tTransfer() * ( thisCache->get_blockSize() / L2.get_busWidth() );
#ifdef _DEBUG_FETCH_
      cout << "Writing L1 from L2" << endl;
      cout << "fetchTime += L2->L1 transfer = " << dec << fetchTime << endl;
#endif

      // if a line is evicted from L1
      if (ptr && ptr->get_valid() && ptr->get_dirty()) 
      {
	 // write it to L2
	 ptr = L2.write(index, tag);
	 // add time for transfer
	 fetchTime += L2.get_tTransfer() * ( thisCache->get_blockSize() / L2.get_busWidth() );
#ifdef _DEBUG_FETCH_
	 cout << "A line was evicted from L1 when it was written to. Writing back to L2" << endl;
	 cout << "fetchTime += L1->L2 writeback = " << dec << fetchTime << endl;
#endif
	 // if a line is evicted from L2, write to main mem
	 if (ptr && ptr->get_valid() && ptr->get_dirty())
	 {
	    fetchTime += mem.get_tChunk() * (L2.get_blockSize() / mem.get_chunkSize());
#ifdef _DEBUG_FETCH_
	    cout << "A line was evicted from L2 when it was written to. Writing back to main mem" << endl;
	    cout << "fetchTime += L2->main mem writeback = " << dec << fetchTime << endl;
#endif
	 }
      }
      
      switch(operation)
      {
	 case READ:
	    // if operation is a read
	    // read L1, then done
	    fetchTime += thisCache->get_tHit();
#ifdef _DEBUG_FETCH_
	    cout << "Operation is a read. Reading L1." << endl;
	    cout << "fetchTime += L1.get_tHit = " << dec << fetchTime << endl;
#endif
	    break;
	 case WRITE:
	    // if operation is a write
	    // done
#ifdef _DEBUG_FETCH_
	    cout << "Operation is a write. Updating L1." << endl;
	    //cout << "fetchTime += L1.get_tHit = " << dec << fetchTime << endl;
#endif
	    break;
	 default:
	    cout << "ERROR: INVALID OPERATION TYPE IN FETCH: " << operation << endl;
	    exit(ES_INVALID_OPERATION);
      }
   }
#ifdef _DEBUG_FETCH_ 
   cout << "Final fetchTime: " << fetchTime << endl;
   cout << "========== END OF _DEBUG_FETCH_ ==========" << endl;
#endif

   return fetchTime;
}

