/* defines.h
 * global defines for cachesim project
 *
 *
 * REVISION HISTORY
 * 11/8/2010   Danny Gale  created
 *
 */
#ifndef _DEFINES_H_
#define _DEFINES_H_

// DEFAULT VALUES
#define L1_DEFAULT_BLOCK_SIZE 32
#define L1_DEFAULT_CACHE_SIZE 8192
#define L1_DEFAULT_ASSOC      1
#define L1_DEFAULT_tHIT	      1
#define L1_DEFAULT_tMISS      1

#define L2_DEFAULT_BLOCK_SIZE 64
#define L2_DEFAULT_CACHE_SIZE 65536
#define L2_DEFAULT_ASSOC      1
#define L2_DEFAULT_tHIT	      4
#define L2_DEFAULT_tMISS      6
#define L2_DEFAULT_tTRANSFER  6
#define L2_DEFAULT_BUSWIDTH   16

// CACHE REQUEST TYPE
enum op_type { READ, WRITE };

// DEBUG STATEMENTS AND CONDITIONAL COMPILATION
//#define _DEBUG_CACHE_WRITE_
//#define _DEBUG_FETCH_
//#define _DEBUG_L1_STRUCTURE_
//#define _DEBUG_L1_STRUCTURE_FAKEDATA_
//#define _DEBUG_L1_STRUCTURE_VERBOSE_
//#define _DEBUG_L2_STRUCTURE_
//#define _DEBUG_CACHE_HIT_
//#define _DEBUG_SET_FINDLINE_
//#define _DEBUG_SET_UPDATELRU_

#define _OUTPUT_
//#define _OUTPUT_FILE_
#define _OUTPUT_TRACE_STATS_
#define _OUTPUT_CACHE_STATS_
//#define _OUTPUT_CACHE_I_
//#define _OUTPUT_CACHE_D_
//#define _OUTPUT_CACHE_L2_

// EXIT STATUSES
#define ES_UNINITIALIZED_CACHE	 0
#define ES_INVALID_CACHE_TYPE	 1
#define ES_SET_SIZE		 2
#define ES_LRU_OVERSIZE		 3
#define ES_LINES_OVERSIZE	 4
#define ES_FETCH_ERROR		 5
#define ES_INVALID_OPERATION	 6
#define ES_INVALID_INSTRUCTION	 7

#endif
