// cxxcache.cxx
// implementation of the L1 and L2 caches, and main memory
// ECEN4593 cache simulator project
// F2010
// Danny Gale and Chris Messick
//
// REVISION HISTORY:
// 11/2/2010   Danny Gale  created
// 11/5/2010   Danny Gale  consolidated L1 and L2 cache classes into single class
//

using namespace std;

#include <iostream>

#include "cxxcache.h"
#include "cacheline.h"

cache::cache()
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

cache::cache(cache_t cacheType)
{
   if (cacheType == CACHETYPE_L1)
   {
      blockSize = 32;
      cacheSize = 8192;
      assoc = 1;
      tHit = 1;
      tMiss = 1;
      tTransfer = 0;
      busWidth = 0;
   }
   else if (cacheType == CACHETYPE_L2)
   {
      blockSize = 64;
      cacheSize = 65536;
      assoc = 1;
      tHit = 4;
      tMiss = 6;
      tTransfer = 10;
      busWidth = 16;
   }
   else
   {
      cout << "ERROR: invalid cache type" << cacheType << endl;
      exit(2);
   }
}

cache::~cache()
{
   // free dynamic array
}

cacheLine * cache::hit(unsigned address)
{
   // go through the cache and see if the data is there
   //for (unsigned i = 0; i < numLines; i++)
      //if (get_entry(i).get_tag()
   return 0;
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
