// cache.h
// holds classes for the L1 and L2 caches, and main memory
// ECEN4593 cache simulator project
// F2010
// Danny Gale, Chris Messick
//
// Revision History:
// 11/2/2010   created	Danny Gale
// 11/2/2010   converted from C structs to C++ classes	 Danny Gale
//

class L1_cache
{
   public:
      // CONSTRUCTOR AND DESTRUCTOR
      L1_cache();
      ~L1_cache();

      // MEMBER FUNCTIONS
//      bool write();
//      bool read();

      unsigned get_blockSize() const { return blockSize; }
      unsigned get_cacheSize() const { return cacheSize; }
      unsigned get_assoc() const { return assoc; }
      unsigned get_tHit() const { return tHit; }
      unsigned get_tMiss() const { return tMiss; }

      void set_blockSize(unsigned newSize) { blockSize = newSize; }
      void set_cacheSize(unsigned newSize) { cacheSize = newSize; }
      void set_assoc(unsigned newAssoc) { assoc = newAssoc; }
      void set_tHit(unsigned newtHit) { tHit = newtHit; }
      void set_tMiss(unsigned newtMiss) {tMiss = newtMiss; }

   private:
      unsigned blockSize;
      unsigned cacheSize;
      unsigned assoc;
      unsigned tHit;
      unsigned tMiss;
};


class L2_cache
{
   public:
      // CONSTRUCTOR AND DESTRUCTOR
      L2_cache();
      ~L2_cache();

      // MEMBER FUNCTIONS
 //     bool write();
 //     bool read();

      unsigned get_blockSize() const { return blockSize; }
      unsigned get_cacheSize() const { return cacheSize; }
      unsigned get_assoc() const { return assoc; }
      unsigned get_tHit() const { return tHit; }
      unsigned get_tMiss() const { return tMiss; }
      unsigned get_tTransfer() const { return tTransfer; }
      unsigned get_busWidth() const { return busWidth; }

      void set_blockSize(unsigned newSize) { blockSize = newSize; }
      void set_cacheSize(unsigned newSize) { cacheSize = newSize; }
      void set_assoc(unsigned newAssoc) { assoc = newAssoc; }
      void set_tHit(unsigned newtHit) { tHit = newtHit; }
      void set_tMiss(unsigned newtMiss) {tMiss = newtMiss; }
      void set_tTransfer(unsigned newtTransfer) {tTransfer = newtTransfer; }
      void set_busWidth(unsigned newbusWidth) { busWidth = newbusWidth; }

   private:
      unsigned blockSize;
      unsigned cacheSize;
      unsigned assoc;
      unsigned tHit;
      unsigned tMiss;
      unsigned tTransfer;
      unsigned busWidth;
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

