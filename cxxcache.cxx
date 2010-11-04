// cxxcache.cxx
// implementation of the L1 and L2 caches, and main memory
// ECEN4593 cache simulator project
// F2010
// Danny Gale and Chris Messick
//
// REVISION HISTORY:
// 11/2/2010   Danny Gale  created
//

using namespace std;

#include "cxxcache.h"


// ***TO DO*** need to create a dynamically allocated array of cache entries
//	       for both L1 and L2, and equivalent for main memory
// ***TO DO*** create class for cache entry/memory data

L1_cache::L1_cache()
{
   blockSize = 32;
   cacheSize = 8192;
   assoc = 1;
   tHit = 1;
   tMiss = 1;

   // need dynamic array here
}

L1_cache::~L1_cache()
{
   // free dynamic array
}



L2_cache::L2_cache()
{
   blockSize = 64;
   cacheSize = 65536;
   assoc = 1;
   tHit = 4;
   tMiss = 6;
   tTransfer = 10;
   busWidth = 16;

   // need dynamic array here
}

L2_cache::~L2_cache()
{
   // free dynamic array
}



main_memory::main_memory()
{
   tSendAddr = 20;
   tReady = 100;
   tChunk = 30;
   chunkSize = 16;

   // need dynamic array here
}

main_memory::~main_memory()
{
   // free dynamic array
}
