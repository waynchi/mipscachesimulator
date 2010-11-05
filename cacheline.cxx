// cacheentry.cxx
// a class for each entry in the cache and main memory
//
// ECEN4593, F2010
// Danny Gale, Chris Messick
//
// REVISION HISTORY:
// 11/4/2010   Danny Gale  created
// 11/4/2010   Danny Gale  removed support for data. not needed

using namespace std;

#include "cacheline.h"

cacheLine::cacheLine()
{
   valid = false;
   tag = 0;
}

cacheLine::cacheLine(bool v, unsigned tagval)
{
   valid = v;
   tag = tagval;
}

cacheLine::~cacheLine()
{

}
