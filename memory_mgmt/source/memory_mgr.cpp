#include "memory_mgr.hpp"

#ifdef USE_MEMORY_MGR

MemoryMgr gMemoryMgr;

// Constructor: Initializes memory pools and lookup table.
MemoryMgr::MemoryMgr ()
{
    for (size_t i = 0; i < MAX_MEMPOOLS; i++) {

        vMemoryPools[i] = new MemoryPool (i);
    }

    InitializeLookUp ();
}

// Allocates memory from the appropriate pool or system malloc for larger sizes.
void * MemoryMgr::MemAlloc (size_t pSize)
{
        char id;

    if (pSize == 0) {

        return nullptr;
    }

    if (pSize > MAX_ELEM_SIZE) {

        return malloc (pSize);
    }

    id = gLookUp [pSize];

    return vMemoryPools[id]->Alloc ();
}

// Frees memory from respective memory pool by using the ID in previous byte.
// This can handle double free case.
// NOTE: ID byte (info before the returned ptr) should not be corrputed.
void MemoryMgr::MemFree (void * pPtr)
{
        tID  * id   = nullptr;
        void * ptr  = nullptr;

    id = ((tID *) pPtr - 1);

    if (id->uBlockID > MAX_MEMPOOLS) {

        free (pPtr);
    }

    if (id->uBlockID < MAX_MEMPOOLS) {

        // handle double free
        if (id->uIsFreed == true) {

            return;
        }

        vMemoryPools[id->uBlockID]->FreeMem (pPtr);
        id->uIsFreed = true;

    }

}

#endif // USE_MEMORY_MGR
