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
#include <iomanip>

// PROJECT INCLUDES
#include "set.h"
#include "cacheline.h"
#include "defines.h"

// CONSTRUCTOR
set::set()
{
   associativity = 1;
   size = 0;
}

// DESTRUCTOR
set::~set()
{
   cacheLine * cursor = head;
   cacheLine * temp = head;

   while (cursor != 0)
   {
      temp = cursor;
      cursor = cursor->get_next();
      delete temp;
   }
}

// insert a new, empty, invalid line into the cache
// INCREASES SIZE BY 1
void set::add_line()
{
   cacheLine * temp;
   if (size >= associativity)
   {
      cerr << "Set trying to increase beyond associativity. Exiting.";
      exit(ES_SET_SIZE);
   }
   else
   {
      // add to lines
      temp = head;
      head = new cacheLine;
      head->set_next(temp);
      size++;
   }
}

// returns a pointer to a block
cacheLine * set::get_block(unsigned i)
{
   cacheLine * it;
   unsigned j = 0;
   
   if (head == 0)
      cout << "Set is empty" << endl;
   else
   {
      it = head;
      for(j = 0; j < i; j++)
      {
	 it = it->get_next();
	 if (it == 0)
	    return it;
      }
   }
   cout << "returning block # " << j << " from get_block" << endl;
   return it;
}

// resizes the dynamic array
// DELETES THE CONTENTS OF THE SET
void set::set_associativity(unsigned assoc)
{
   cacheLine * cursor = head;
   cacheLine * temp;
   unsigned i;

   // delete the old array of lines
   while(cursor != 0)
   {
      temp = cursor;
      cursor = cursor->get_next();
      delete temp;
   }

   // update the associativity
   associativity = assoc;

   head = new cacheLine;
   cursor = head;
   for(i = 0; i < associativity - 1; i++)
   {
      temp = new cacheLine;
      cursor->set_next(temp);
      cursor = temp;
   }
   cursor->set_next(0);
}


// returns a cacheLine * if one was evicted
cacheLine * set::update_LRU(cacheLine * mostRecent)
{
   cacheLine * cursor, *temp, *oldHead;

   temp = head;

   // check the set to see if it's currently there
   for (cursor = head; cursor != 0; cursor = cursor->get_next())
   {
      if (cursor == mostRecent)
      {	 // found it
	 if (cursor == head) // it's already the head
	    return 0;
	 else
	 {
	    // if it's not already the head
	    // move it to the head 
	    temp->set_next(cursor->get_next());
	    cursor->set_next(head);
	    head = cursor;
	    return 0;
	 }
      }
      temp = cursor;
   }

   // ok, we didn't find it
   // we need to evict the least recently used one
   // which is currently pointed to by cursor

   // set temp as the tail
   temp->set_next(0);

   // and add the new one to the head
   oldHead = head;
   head = mostRecent;
   head->set_next(oldHead);

   return cursor;
}


// searches the list of lines for a given tag
// if the tag is found and the valid bit is set,
// a pointer to the block is returned
// otherwise 0 is returned
cacheLine * set::find_line(unsigned t)
{
#ifdef _DEBUG_SET_FINDLINE_
   cout << "Inside set::find_line looking for tag " << t << endl;
#endif
   cacheLine * it = 0;

   if (head == 0)
   {
      cout << "Empty set. exiting" << endl;
      exit(0);
   }
#ifdef _DEBUG_SET_FINDLINE_
   cout << "set not empty" << endl;
#endif

   for (it = head; it != 0; it = it->get_next())
   {
#ifdef _DEBUG_SET_FINDLINE_
      cout << "it = " << it << " tag = " << it->get_tag() << " valid = " << it->get_valid() << endl;
#endif
      if (it->get_tag() == t && it->get_valid() == true)
      {
#ifdef _DEBUG_SET_FINDLINE_
	 cout << "returning it: " << it << endl;
#endif
	 return it;
      }
   }
   return 0;
}


void set::output_blocks()
{
#ifdef _DEBUG_SET_OUTPUTBLOCKS_
   cout << "assoc = " << associativity << ". size = " << size << " ";
#endif
   cacheLine * it;

   for (it = head; it != 0; it = it->get_next())
   {
      cout << setw(8) << hex << it->get_tag() << " ";
   }
}

