// cacheentry.h
// a class for each entry in the cache and main memory
//
// ECEN4593, F2010
// Danny Gale, Chris Messick
//
// REVISION HISTORY:
// 11/4/2010   Danny Gale  created
// 11/4/2010   Danny Gale  removed support for data. not needed
//

#ifndef _CACHELINE_H_
#define _CACHELINE_H_

using namespace std;

class cacheLine
{
   public:
      // CONSTRUCTORS AND DESTRUCTOR
      cacheLine();
      cacheLine(bool v, bool d, unsigned tagval);

      // CONSTANT MEMBER FUNCTIONS
      bool get_valid() const { return valid; }
      bool get_dirty() const { return valid; }
      unsigned get_tag() const { return tag; }

      // MEMBER FUNCTIONS
      void set_valid(bool value) { valid = value; }
      void set_dirty(bool value) { dirty = value; }
      void set_tag(unsigned value) { tag = value; }
      void set_all(bool v, bool d, unsigned t) { valid = v; dirty = d; tag = t; }

   private:
      bool valid;
      bool dirty;
      unsigned tag;

};

#endif
