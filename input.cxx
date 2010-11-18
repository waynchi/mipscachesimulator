// input.c
// a file for reading inputs from the command line
//
// Danny Gale, Chris Messick
//
// REVISION HISTORY
// 11/1/2010   Danny Gale  created
// 11/2/2010   Danny Gale  converted to C++

//#define _DEBUG_INPUT_

// COMPILER INCLUDES
#include <string>
#include <iostream>
#include <fstream>

// PROJECT INCLUDES
#include "cxxcache.h"

using namespace std;

// EXTERNAL VARIABLES
extern cache I;
extern cache D;
extern cache L2;
extern main_memory mem;

// LOCAL FUNCTIONS
void printParameters();
void get_config(string filename);

void get_config(string filename)
{
   string param;
   unsigned int value;
   ifstream configFile (filename.c_str());

   // check for valid configuration file
   if (!configFile.is_open())
      cout << "Invalid configuration file" << endl << "Using default values" << endl;
   else
   {
      cout << "Using configuration file " << filename << endl;
      // if valid, set parameters that are present
      while ( !configFile.eof() )
      {
	 configFile >> param >> value;
	 if (param.compare("L1.blockSize") == 0)
	 {
	    I.set_blockSize(value);
	    D.set_blockSize(value);
	 }
	 else if (param.compare("L1.cacheSize") == 0)
	 {
	    I.set_cacheSize(value);
	    D.set_cacheSize(value);
	 }
	 else if (param.compare("L1.assoc") == 0)
	 {
	    I.set_assoc(value);
	    D.set_assoc(value);
	 }
	 else if (param.compare("L1.tHit") == 0)
	 {
	    I.set_tHit(value);
	    D.set_tHit(value);
	 }
	 else if (param.compare("L1.tMiss") == 0)
	 {
	    I.set_tMiss(value);
	    D.set_tMiss(value);
	 }
	 else if (param.compare("L2.blockSize") == 0)
	    L2.set_blockSize(value);
	 else if (param.compare("L2.cacheSize") == 0)
	    L2.set_cacheSize(value);
	 else if (param.compare("L2.assoc") == 0)
	    L2.set_assoc(value);
	 else if (param.compare("L2.tHit") == 0)
	    L2.set_tHit(value);
	 else if (param.compare("L2.tMiss") == 0)
	    L2.set_tMiss(value);
	 else if (param.compare("L2.tTransfer") == 0)
	    L2.set_tTransfer(value);
	 else if (param.compare("L2.busWidth") == 0)
	    L2.set_busWidth(value);
	 else if (param.compare("mem.tSendAddr") == 0)
	    mem.set_tSendAddr(value);
	 else if (param.compare("mem.tReady") == 0)
	    mem.set_tReady(value);
	 else if (param.compare("mem.tChunk") == 0)
	    mem.set_tChunk(value);
	 else if (param.compare("mem.chunkSize") == 0)
	    mem.set_chunkSize(value);
	 else
	 {
	    cout << "Invalid parameter: " << param << endl;
	 }
      }
      cout << endl << "Config file acquired" << endl;
   }
   return;
}

void printParameters()
{
   cout << endl << "CACHE PARAMETERS:\tL1:\tL2:" << endl;
   cout << "blockSize\t=\t" << I.get_blockSize() <<"\t" << L2.get_blockSize() << endl;
   cout << "cacheSize\t=\t" << I.get_cacheSize() << "\t" << L2.get_cacheSize() << endl;
   cout << "assoc\t\t=\t" << I.get_assoc() << "\t" << L2.get_assoc() << endl;
   cout << "tHit\t\t=\t" << I.get_tHit() << "\t" << L2.get_tHit() << endl;
   cout << "tMiss\t\t=\t" << I.get_tMiss() << "\t" << L2.get_tMiss() << endl;
   cout << "tTransfer\t=\t\t" << L2.get_tTransfer() << endl;
   cout << "busWidth\t=\t\t" << L2.get_busWidth() << endl;
   cout << "numSets\t\t=\t" << I.get_numSets() << "\t" << L2.get_numSets() << endl;
   cout << "bytesPerBlock\t=\t" << I.get_bytesPerBlock() << "\t" << L2.get_bytesPerBlock() << endl;
   cout << "indexBits\t=\t" << I.get_indexBits() << "\t" << L2.get_indexBits() << endl;
   cout << "byteBits\t=\t" << I.get_byteBits() << "\t" << L2.get_byteBits() << endl;
   cout << "tagBits\t\t=\t" << I.get_tagBits() << "\t" << L2.get_tagBits() << endl;

   cout << endl << "MEMORY PARAMETERS:" << endl;
   cout << "tSendAddr\t=\t" << mem.get_tSendAddr() << endl;
   cout << "tReady\t\t=\t" << mem.get_tReady() << endl;
   cout << "tChunk\t\t=\t" << mem.get_tChunk() << endl;
   cout << "chunkSize\t=\t" << mem.get_chunkSize() << endl;
}
