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
#include "set.h"
#include "defines.h"

cache::cache()
{
   cout << endl << "Error: UNINITIALIZED CACHE TYPE" << endl;
   exit(ES_UNINITIALIZED_CACHE);
}

cache::cache(cache_t cacheType)
{
   unsigned i;

   if (cacheType == CACHETYPE_L1)
   {
      blockSize = 32;
      cacheSize = 8192;
      assoc = 1;
      tHit = 1;
      tMiss = 1;
      tTransfer = 0;
      busWidth = 0;
      
      numLines = cacheSize / (assoc * blockSize);

      sets = new set[numLines];

      for (i = 0; i < numLines; i++)
	 sets[i].set_associativity(assoc);
   }
   else if (cacheType == CACHETYPE_L2)
   {
      blockSize = 64;
      cacheSize = 65536;
      assoc = 1;
      tHit = 4;
      tMiss = 6;
      tTransfer = 6;
      busWidth = 16;

      numLines = cacheSize / (assoc * blockSize);

      sets = new set[numLines];

      for (i = 0; i < numLines; i++)
	 sets[i].set_associativity(assoc);
   }
   else
   {
      cout << "ERROR: invalid cache type" << cacheType << endl;
      exit(ES_INVALID_CACHE_TYPE);
   }
   writeRequests = 0;
   readRequests = 0;
   requests = 0;
   writeMisses = 0;
   readMisses = 0;
   misses = 0;
   writeHits = 0;
   readHits = 0;
   hits = 0;
}

cache::~cache()
{
   // free dynamic array
   delete [] sets;
}

cacheLine * cache::hit(unsigned address)
{
   // go through the cache and see if the data is there
   //for (unsigned i = 0; i < numLines; i++)
      //if (get_entry(i).get_tag()
   return 0;
}

// remove and resize dynamic array
void cache::set_assoc(unsigned value)
{
   delete [] sets;
   sets = new set[value];
}


main_memory::main_memory()
{
   tSendAddr = 20;
   tReady = 100;
   tChunk = 30;
   chunkSize = 16;
}

main_memory::~main_memory()
{

}
