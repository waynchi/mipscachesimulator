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

      // MEMBER FUNCTIONS
      cacheLine * write(unsigned addr);
      cacheLine * read(unsigned addr);
 
      void set_blockSize(unsigned newSize) { blockSize = newSize; }
      void set_cacheSize(unsigned newSize) { cacheSize = newSize; }
      void set_assoc(unsigned newAssoc); // re-allocate dynamic array of sets
      void set_tHit(unsigned newtHit) { tHit = newtHit; }
      void set_tMiss(unsigned newtMiss) {tMiss = newtMiss; }
      void set_tTransfer(unsigned newtTransfer) {tTransfer = newtTransfer; }
      void set_busWidth(unsigned newbusWidth) { busWidth = newbusWidth; }

      void incr_wr() { writeRequests++; requests++; }
      void incr_rr() { readRequests++; requests++; }
      void incr_wm() { writeMisses++; misses++; }
      void incr_rm() { readMisses++; misses++; }
      void incr_wh() { writeHits++; hits++; }
      void incr_rh() { readHits++; hits++; }

   private:
      set * sets; // array created at runtime after configuration file is read

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
      unsigned wordsPerBlock;

      // statistics
      unsigned writeRequests;
      unsigned readRequests;
      unsigned requests;
      unsigned writeMisses;
      unsigned readMisses;
      unsigned misses;
      unsigned writeHits;
      unsigned readHits;
      unsigned hits;
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
