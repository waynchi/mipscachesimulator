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
#include <cmath>

#include "cxxcache.h"
#include "cacheline.h"
#include "set.h"
#include "defines.h"

cache::cache()
{
   cout << endl << "ERROR: UNINITIALIZED CACHE TYPE" << endl;
   exit(ES_UNINITIALIZED_CACHE);
}

cache::cache(cache_t cacheType)
{
   unsigned i;

   if (cacheType == CACHETYPE_L1)
   {
      blockSize = L1_DEFAULT_BLOCK_SIZE;
      cacheSize = L1_DEFAULT_CACHE_SIZE;;
      assoc = L1_DEFAULT_ASSOC;
      tHit = L1_DEFAULT_tHIT;
      tMiss = L1_DEFAULT_tMISS;;
      tTransfer = 0;
      busWidth = 0;
      
      numSets = cacheSize / (assoc * blockSize);
      bytesPerBlock = blockSize / 8;

      sets = new set[numSets];

      for (i = 0; i < numSets; i++)
	 sets[i].set_associativity(assoc);

      indexBits = log2(numSets);
      byteBits = log2(bytesPerBlock);
      tagBits = 32 - byteBits - indexBits;
   }
   else if (cacheType == CACHETYPE_L2)
   {
      blockSize = L2_DEFAULT_BLOCK_SIZE;
      cacheSize = L2_DEFAULT_CACHE_SIZE;;
      assoc = L2_DEFAULT_ASSOC;
      tHit = L2_DEFAULT_tHIT;
      tMiss = L2_DEFAULT_tMISS;;
      tTransfer = L2_DEFAULT_tTRANSFER;
      busWidth = L2_DEFAULT_BUSWIDTH;

      numSets = cacheSize / (assoc * blockSize);
      bytesPerBlock = blockSize / 8;

      sets = new set[numSets];

      for (i = 0; i < numSets; i++)
	 sets[i].set_associativity(assoc);

      indexBits = log2(numSets);
      byteBits = log2(bytesPerBlock);
      tagBits = 32 - byteBits - indexBits;
   }
   else
   {
      cout << "ERROR: invalid cache type: " << cacheType << endl;
      exit(ES_INVALID_CACHE_TYPE);
   }

   writes = 0;
   reads = 0;
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

// remove and resize dynamic array
void cache::set_assoc(unsigned value)
{
   assoc = value;
   set_numSets(cacheSize / (assoc * blockSize));

   for (unsigned i = 0; i < numSets; i++)
   {
      sets[i].set_associativity(assoc);
   }
}

void cache::set_blockSize(unsigned newSize)
{
   blockSize = newSize;
   set_numSets(cacheSize / (assoc * blockSize));
   set_bytesPerBlock(blockSize / 8);
}

void cache::set_cacheSize(unsigned newSize)
{
   cacheSize = newSize;
   set_numSets(cacheSize / (assoc * blockSize) );
}

void cache::set_numSets(unsigned n)
{
   numSets = n;
   indexBits = log2(numSets);
   tagBits = 32 - indexBits - byteBits;
}

void cache::set_bytesPerBlock(unsigned n)
{
   bytesPerBlock = n;
   byteBits = log2(bytesPerBlock);
   tagBits = 32 - indexBits - byteBits;
}

// searches the cache for a given address
// returns a pointer to the block if it's found
cacheLine * cache::hit(unsigned index, unsigned tag)
{
#ifdef _DEBUG_CACHE_HIT_
   cout << "_DEBUG_CACHE_HIT_\tInside cache::hit using index " << index << " and tag " << tag << endl;
#endif

   // index to the set, go through the set and see if the data is there
   // find_line() returns 0 if the line is not found or is not valid, 
   // or a pointer to it if it is found & valid
   cacheLine * ptr = sets[index].find_line(tag);
#ifdef _DEBUG_CACHE_HIT_
   cout << "_DEBUG_CACHE_HIT_\tptr has been set to " << ptr << endl << "_DEBUG_CACHE_HIT_\tReturning ptr" << endl;
#endif

   return ptr;
}

// updates the cacheLine so that it is in true LRU order
cacheLine * cache::read(unsigned index, unsigned tag)
{
   cacheLine * ptr = 0;

   ////////////////////////
   // update the statistics
   ////////////////////////

   // go find the line in the set
   ptr = sets[index].find_line(tag);

   if (ptr) // ptr will be non-zero if the tag was found
   {  // found it
      // update the LRU
      sets[index].update_LRU(ptr);

      ////////////////////////
      // update the statistics
      ////////////////////////
      readHits++;
      hits++;
   }
   else
   {  // didn't find it
      ////////////////////////
      // update the statistics
      ////////////////////////
      readMisses++;
      misses++;
   }

   return ptr;
}

// NOT A WRITE REQUEST, JUST A WRITE
// do not search for valid block with the right tag,
// just write into the cache, replacing the least recently
// used line
cacheLine * cache::write(unsigned index, unsigned tag)
{
   cacheLine * ptr = 0;

   // writing, not a write request
   ////////////////////////
   // update the statistics
   ////////////////////////
   writes++;

   ptr = new cacheLine(tag, 0);

   return sets[index].update_LRU(ptr);
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
