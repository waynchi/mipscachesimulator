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
      cacheLine(bool v, unsigned tagval);
      ~cacheLine();

      // CONSTANT MEMBER FUNCTIONS
      bool get_valid() const { return valid; }
      unsigned get_tag() const { return tag; }

      // MEMBER FUNCTIONS
      void set_valid(bool value) { valid = value; }
      void set_tag(unsigned value) { tag = value; }

   private:
      bool valid;
      unsigned tag;

};

#endif
