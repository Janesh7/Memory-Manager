#ifndef MEMORY_MGR_HPP
#define MEMORY_MGR_HPP

#include "memory_pool.hpp"

// Chunks of memory for testing custom/system malloc/free
constexpr size_t SIZE_CHUNK_UNDER_8   = 7;
constexpr size_t SIZE_CHUNK_UNDER_16  = 16;
constexpr size_t SIZE_CHUNK_UNDER_32  = 31;
constexpr size_t SIZE_CHUNK_UNDER_64  = 60;
constexpr size_t SIZE_CHUNK_UNDER_128 = 120;
constexpr size_t SIZE_CHUNK_UNDER_256 = 220;
constexpr size_t SIZE_CHUNK_UNDER_512 = 550;
constexpr size_t SIZE_CHUNK_ABOVE_MAX = 887;

constexpr size_t BIG_NUM              = 1000000;

#ifdef  USE_MEMORY_MGR

// Memory manager class responsible for allocating and freeing memory using memory pools.
class MemoryMgr {

  public:

                         MemoryMgr           ();
            void *       MemAlloc            (size_t pSize);
            void         MemFree             (void * pPtr);

  private:

            MemoryPool * vMemoryPools [MAX_MEMPOOLS];

};

extern MemoryMgr gMemoryMgr;

#define Malloc(pSize)   gMemoryMgr.MemAlloc   (pSize)
#define Free(pPtr)      gMemoryMgr.MemFree     (pPtr)


#else

#define Malloc(pSize)      malloc (pSize)
#define Free(pPtr)         free   (pPtr)

#endif // USE_MEMORY_MGR

#endif // !MEMORY_MGR_HPP
