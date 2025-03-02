#ifndef MEMORY_POOL_HPP
#define MEMORY_POOL_HPP

#define USE_MEMORY_MGR

#include <stdlib.h>

#ifdef  USE_MEMORY_MGR

#pragma pack (push, 1)

// Memory block identifier with block ID and freed status.
struct tID {

    unsigned char   uBlockID : 7;
    bool            uIsFreed : 1;

};

#pragma pack (pop)

constexpr           long   MEM_FAILURE                      = 1;
constexpr           size_t ID_SIZE                          = 1;
constexpr           size_t GROW_SIZE                        = 2;
constexpr           size_t MAX_ELEM_SIZE                    = 512;
constexpr           size_t MAX_MEMPOOLS                     = 7;
constexpr static    size_t sPoolElemSize[MAX_MEMPOOLS]      = {8, 16, 32, 64, 128, 256, MAX_ELEM_SIZE};

constexpr           size_t POOL_NUM_ELEM_8                  = (512);
constexpr           size_t POOL_NUM_ELEM_16                 = (512);
constexpr           size_t POOL_NUM_ELEM_32                 = (512);
constexpr           size_t POOL_NUM_ELEM_64                 = (512);
constexpr           size_t POOL_NUM_ELEM_128                = (128);
constexpr           size_t POOL_NUM_ELEM_256                = (128);
constexpr           size_t POOL_NUM_ELEM_MAX_ELEM_SIZE      = (16);

constexpr static    size_t sPoolNumElems[MAX_MEMPOOLS]      = {
                                                                POOL_NUM_ELEM_8,
                                                                POOL_NUM_ELEM_16,
                                                                POOL_NUM_ELEM_32,
                                                                POOL_NUM_ELEM_64,
                                                                POOL_NUM_ELEM_128,
                                                                POOL_NUM_ELEM_256,
                                                                POOL_NUM_ELEM_MAX_ELEM_SIZE,
                                                              };

// Look up table for getting the memory pool id from the requested size in constant time.
extern              size_t gLookUp[MAX_ELEM_SIZE + 1];     // + 1 , coz for sizes 1-MAX

                    void   InitializeLookUp         ();    // Function to initialize Look Up table


// Memory pool class that manages a specific block size pool for fast allocation.
class MemoryPool {
 
  public:
    
            MemoryPool      (char pID);
 
    void *  Alloc           ();
    void    FreeMem         (void * pBuffer);

  private:


    void    GrowPool        ();

    // Data members
    tID     vID;             // ID to idetify which block of pool and check for freed status
    void *  vFreeListHead;
    size_t  vBlockSize;
    size_t  vBlockNum;
    size_t  vBufferSize;

};

#endif // USE_MEMORY_MGR

#endif // !MEMORY_POOL_HPP
