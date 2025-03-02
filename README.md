# Memory Manager

A custom memory manager designed for faster and more efficient memory allocation using segregated free list memory management.

## Overview

This memory manager optimizes memory allocations and deallocations by utilizing segregated memory pools. The idea behind this approach is to group memory blocks of similar sizes into different pools, making allocation and deallocation more efficient. This ensures that the system does not spend unnecessary time searching for free memory blocks and that memory fragmentation is minimized. 

The memory pools are managed in such a way that each pool can efficiently allocate and free memory blocks of a specific size in constant time, \( O(1) \). The pools dynamically grow when required and handle scenarios such as double-free errors effectively.

## Features and Optimizations

### 1. **Segregated Memory Pools**

- The memory manager organizes memory into multiple pools, each dedicated to a specific block size (ranging from 8 bytes to 512 bytes).
- These pools allow for quick allocation and deallocation of memory, ensuring that the manager can allocate memory blocks in constant time \( O(1) \) for getting the required memory. (No searching for the correct memort pool due to lookup table)
- The size of each pool is defined at compile time and is optimized for typical allocation sizes.

### 2. **Efficient Memory Lookup**

- A lookup table is used to quickly determine which memory pool to allocate from based on the requested size. This enables fast memory allocation without scanning through multiple pools.

### 3. **Memory Pool Growth**

- Memory pools dynamically grow as required. If the free list of a pool becomes exhausted, the pool grows by allocating additional blocks of memory.
- New blocks are linked to the existing free list, allowing quick allocation from the newly expanded pool. This ensures that memory usage remains efficient even as demands increase.
  
### 4. **Memory Allocation and Deallocation**

- **Allocations:** When a memory block is requested, the manager first checks the lookup table to identify the correct pool based on the size. It then allocates the memory from the appropriate pool or, if necessary, falls back to the system's `malloc` for larger requests.
  
- **Deallocation:** When memory is freed, the manager checks the block’s ID to ensure it was previously allocated and has not been freed already. The manager effectively prevents double-free errors by marking freed blocks and checking their status before freeing them again.
  
- The manager also handles memory blocks' metadata (such as block ID and freed status) in a special identifier structure (`tID`), which helps track the status of each block and manage the free list properly.

### 5. **Prevention of Double Free**

- To avoid double-free errors, the memory manager keeps track of the allocation status of memory blocks through a `tID` structure. This structure stores the block ID and a "freed" flag, which is checked before freeing memory. If the block has already been freed, the manager ignores the request to free it again, thus preventing undefined behavior and crashes.

### 6. **Block Linking**

- Each block in a memory pool contains a pointer to the next free block in the pool (implemented as a linked list). When a block is freed, it is added back to the free list, allowing subsequent allocations to use it without requiring a system call.

### 7. **Optimized for multiple Allocations**

- This memory manager is particularly efficient for multiple allocations, as for the traditional method each memory call would have a system call overhead. It uses a compact layout with minimal metadata (space) overhead, allowing for faster memory operations compared to general-purpose memory managers.

### 8. **Fallback to System Memory**

- For allocations larger than 512 bytes (the maximum pool size), the memory manager falls back to using the system's `malloc` and `free` functions. This ensures that memory allocation remains flexible and scalable for larger objects or dynamic memory requirements.

## How It Works

### Memory Pool Structure

- Memory pools are defined for different block sizes (8, 16, 32, 64, 128, 256, and 512 bytes).
- When an allocation request is made, the lookup table is used to identify the corresponding memory pool.
- If the requested size fits within a pool's block size, the memory manager allocates memory from that pool.
- If the requested memory size exceeds the maximum pool size, the memory manager falls back to system-level allocation (using `malloc`).

### Dynamic Growth

- When all memory blocks in a pool are allocated, the pool is dynamically expanded by requesting additional memory from the heap.
- New memory blocks are linked to the free list of the pool to ensure that the next allocation can proceed without waiting for other blocks to be freed.

### Memory Identification

- Every block of memory in the pool has an associated identifier (`tID`), which stores the block ID and the freed status.
- This helps track which blocks belong to which pool and ensures safe deallocation by preventing double frees and other memory errors.

### Configuration

To enable the custom memory manager, define `USE_MEMORY_MGR` before including `memory_mgr.hpp`. If `USE_MEMORY_MGR` is not defined, the manager will fall back to using the standard `malloc` and `free` functions.

```cpp
#define USE_MEMORY_MGR
#include "memory_mgr.hpp"
```
