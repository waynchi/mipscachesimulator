/* set.h
 * header file for a set class
 * contains a number of cachelines depending on the associativity of the cache
 *
 * ECEN4593, Fall 2010
 * Danny Gale, Chris Messick
 *
 * REVISION HISTORY:
 * 11/8/2010   Danny Gale  created
 *
 */
#ifndef _SET_H_
#define _SET_H_

using namespace std;

// COMPILER INCLUDES
#include <list>

// PROJECT INCLUDES
#include "cacheline.h"

class set 
{
   public:
      // CONSTRUCTORS AND DESTRUCTOR
      set();
      ~set();
      
      // NON-CONSTRUCTOR INITIALIZATION
      void add_line();	// adds an element to "lines." 
   
      // CONSTANT MEMBER FUNCTIONS
      unsigned get_associativity() { return associativity; }
      
      // MEMBER FUNCTIONS
      void set_associativity();
      void set_associativity(unsigned assoc);
      void update_LRU (cacheLine * mostRecent);

      // places the new block into the cache. returns a pointer to 
      // a cacheLine if one had to be evicted.
      // If a line was returned (and thus evicted) it MUST BE WRITTEN
      // BACK TO L2 and MAIN MEMORY
      cacheLine * put_line(cacheLine * newLine); 

   private:
      list<cacheLine *> LRU;
      list<cacheLine *> lines;
      unsigned associativity;
};

#endif
