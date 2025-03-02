#include "memory_pool.hpp"
#include <stdio.h>

#ifdef USE_MEMORY_MGR

size_t gLookUp[MAX_ELEM_SIZE + 1];

// Initializes the lookup table to assign pool IDs based on allocation size.
void InitializeLookUp ()
{
        size_t j = 0;

    for (size_t i = 1; i <= MAX_ELEM_SIZE;) {

        while (i <= sPoolElemSize[j]) {

            gLookUp[i] = j;
            i++;

        }

        j++;
    }
}

// Constructor: Initializes memory pool for a specific block size bsaed on ID.
MemoryPool::MemoryPool (char pID) : vFreeListHead (nullptr), vBlockSize (sPoolElemSize[pID]), 
                                    vBlockNum (sPoolNumElems[pID]), vBufferSize ((vBlockSize + 1) * vBlockNum)
{
    vID.uBlockID = pID;
    vID.uIsFreed = true;
    GrowPool ();
}

// Allocates a memory block from the pool, growing the pool if necessary.
void * MemoryPool::Alloc ()
{
         tID * temp = nullptr;

    if (*(void **) vFreeListHead == nullptr) {

        GrowPool ();
    }

    void * allocated_block = vFreeListHead;

    temp = (tID *) allocated_block - 1;

    temp->uIsFreed = false;                      // Memory in use
    vFreeListHead  = *(void **) (vFreeListHead);  // Move to the next free block

    return allocated_block;

}

// Frees a memory block and adds it back to the free list (at head).
void MemoryPool::FreeMem (void * pBuffer)
{
    // Add the freed memory back to the free list
    if (pBuffer != nullptr) {

        *(void **) (pBuffer) = vFreeListHead;
        vFreeListHead = pBuffer;

    }
}

// Expands the pool by allocating more memory blocks and linking them.
void MemoryPool::GrowPool ()
{
        char * current     = nullptr;
        char * start       = nullptr;
        void * new_block   = nullptr;
        void * last_block  = nullptr;
        size_t grow_size;


    if (vFreeListHead == nullptr) {

        new_block = malloc (vBufferSize);
        grow_size = vBufferSize;

    } else {

        new_block = malloc (vBufferSize * GROW_SIZE);
        grow_size = (vBufferSize * (GROW_SIZE - 1)) / vBlockSize;

    }

    if (new_block == nullptr) {

        exit (MEM_FAILURE);      // Gracefull exit
    }

    start   = (char *) (new_block);
    current = start;
    current += 1;

    // excluding the last one
    for (size_t i = 0; i < vBlockNum - 1; ++i) {

        // Set the ID at the start of the block (vID)
        *(tID *) (current - 1) = vID;

        // Point to the next block (leave space for ID)
        *(void **) (current) = current + (vBlockSize + 1);

        // Move the current pointer to the next block
        current += vBlockSize + 1;
    }

    // Handle the last block
    *(tID *) (current - 1) = vID;       // Set the ID for the last block
    *(void **) (current)   = nullptr;     // Set the pointer to nullptr for the last block

    start += 1;                         // Point to the block which can be given to user 

    // Link the new block of memory to the free list
    if (vFreeListHead != nullptr) {

        *(void **) (current) = vFreeListHead;
        vFreeListHead = start;

    } else {

        vFreeListHead = start;
    }
}

#endif // USE_MEMORY_MGR
