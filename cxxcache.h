// cxxcache.h
// holds classes for the L1 and L2 caches, and main memory
// ECEN4593 cache simulator project
// F2010
// Danny Gale, Chris Messick
//
// Revision History:
// 11/2/2010   Danny Gale  created    
// 11/2/2010   Danny Gale  converted from C structs to C++ classes
// 11/4/2010   Danny Gale  added dynamic cacheLine array to L1 and L2 caches
//			   added some numLines and wordsPerLine, calculated from given params
//
#ifndef _CXXCACHE_H_
#define _CXXCACHE_H_

using namespace std;

#include "set.h"

enum cache_t { CACHETYPE_L1, CACHETYPE_L2 };

class cache
{
   public:
      // CONSTRUCTOR AND DESTRUCTOR
      cache();
      cache(cache_t cacheType);
      ~cache();

      // CONSTANT MEMBER FUNCTIONS
      unsigned get_blockSize() const { return blockSize; }
      unsigned get_cacheSize() const { return cacheSize; }
      unsigned get_assoc() const { return assoc; }
      unsigned get_tHit() const { return tHit; }
      unsigned get_tMiss() const { return tMiss; }
      unsigned get_tTransfer() const { return tTransfer; }
      unsigned get_busWidth() const { return busWidth; }
      unsigned get_numSets() const { return numSets; }
      unsigned get_blocksPerSet() const { return blocksPerSet; }
      unsigned get_bytesPerBlock() const { return bytesPerBlock; }
      unsigned get_indexBits() const { return indexBits; }
      unsigned get_byteBits() const { return byteBits; }
      unsigned get_tagBits() const { return tagBits; }
      set * get_set(unsigned i) const { return &sets[i]; }

      // statistics
      unsigned get_writes() {return writes;}
      unsigned get_writeRequests() {return writeRequests;}
      unsigned get_writeMisses() {return writeMisses;}
      unsigned get_writeHits() {return writeHits;}

      unsigned get_reads() {return reads;}
      unsigned get_readRequests() {return readRequests;}
      unsigned get_readMisses() {return readMisses;}
      unsigned get_readHits() {return readHits;}

      unsigned get_requests() {return requests;}
      unsigned get_misses() {return misses;}
      unsigned get_hits() {return hits;}

      // MEMBER FUNCTIONS
      cacheLine * hit(unsigned index, unsigned tag);
      cacheLine * write(unsigned index, unsigned tag);
      cacheLine * read(unsigned index, unsigned tag);

      unsigned make_tag(unsigned addr);
      unsigned make_index(unsigned addr); 
 
      void set_blockSize(unsigned newSize);
      void set_cacheSize(unsigned newSize);
      void set_assoc(unsigned newAssoc); 
      void set_tHit(unsigned newtHit) { tHit = newtHit; }
      void set_tMiss(unsigned newtMiss) {tMiss = newtMiss; }
      void set_tTransfer(unsigned newtTransfer) {tTransfer = newtTransfer; }
      void set_busWidth(unsigned newbusWidth) { busWidth = newbusWidth; }
      void set_numSets(unsigned n);
      void set_bytesPerBlock(unsigned n);

      // statistics
      unsigned writes;
      unsigned writeRequests;
      unsigned writeMisses;
      unsigned writeHits;

      unsigned reads;
      unsigned readRequests;
      unsigned readMisses;
      unsigned readHits;

      unsigned requests;
      unsigned misses;
      unsigned hits;

      unsigned evictions;
      unsigned dirtyEvictions;

   private:
      set * sets; 

      // given cache parameters
      unsigned blockSize;
      unsigned cacheSize;
      unsigned assoc;
      unsigned tHit;
      unsigned tMiss;
      unsigned tTransfer;
      unsigned busWidth;
      // calculated cache parameters
      unsigned numSets;
      unsigned blocksPerSet;
      unsigned bytesPerBlock;
      unsigned indexBits;
      unsigned byteBits;
      unsigned tagBits;


};

class main_memory
{
   public:
      // CONSTRUCTOR AND DESTRUCTOR
      main_memory();
      ~main_memory();

      // MEMBER FUNCTIONS
//      bool write();
//      bool read();

      unsigned get_tSendAddr() const { return tSendAddr; }
      unsigned get_tReady() const { return tReady; }
      unsigned get_tChunk() const { return tChunk; }
      unsigned get_chunkSize() const { return chunkSize; }

      void set_tSendAddr(unsigned newval) { tSendAddr = newval; }
      void set_tReady(unsigned newval) { tReady = newval; }
      void set_tChunk(unsigned newval) { tChunk = newval; }
      void set_chunkSize(unsigned newval) { chunkSize = newval; }

   private:
      unsigned tSendAddr;
      unsigned tReady;
      unsigned tChunk;
      unsigned chunkSize;
};

#endif
