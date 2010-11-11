/* set.cxx
 * implementaiton of the set class for the cache simulator
 *
 * ECEN 4593, Fall 2010
 * Danny Gale, Chris Messick
 *
 * REVISION HISTORY:
 * 11/8/2010   Danny Gale  created
 *
 */

using namespace std;

// COMPILER INCLUDES
#include <iostream>

// PROJECT INCLUDES
#include "set.h"
#include "cacheline.h"
#include "defines.h"

set::set()
{
   associativity = 1;
}

set::~set()
{
}


void set::add_line()
{
   if (lines.size >= associativity)
   {
      cerr << "Set (line) trying to increase beyond associativity. Exiting.";
      exit(ES_SET_SIZE);
   }
   else if (LRU.size >= associativity)
   {
      cerr << "Set (LRU) trying to increase beyond associativity. Exiting.";
      exit(ES_SET_SIZE);
   } 
   else
   {
      cacheLine * newLine = new cacheLine;
      // add to lines
      lines.push_back(newLine);
      // add to LRU
      LRU.push_back(newLine);
   }
}

void set_associativity(unsigned assoc)
{
   lines.clear();
   LRU.clear();

}

void set::update_LRU(cacheLine * mostRecent)
{
   // find any and all (should only be one) instances
   // of mostRecent in LRU
   LRU.remove(mostRecent);
   LRU.push_back(mostRecent);
   if (LRU.size() > associativity)
   {
      cerr << "LRU size exceeds associativity" << endl;
      exit(ES_LRU_OVERSIZE);
   }
   if (lines.size() > associativity)
   {
      cerr << "lines size exceeds associativity" << endl;
      exit(ES_LINES_OVERSIZE);
   }
}
