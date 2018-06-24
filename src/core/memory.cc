#include "memory.h"
#include <algorithm>
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
MemoryArena::MemoryArena () :
  block_size_             (262144),
  current_block_position_ (0),
  current_allocate_size_  (0),
  current_block_          (nullptr)
{}
/*
// ---------------------------------------------------------------------------
*/
MemoryArena::MemoryArena (size_t block_size) :
  block_size_             (block_size),
  current_block_position_ (0),
  current_allocate_size_  (0),
  current_block_          (nullptr)
{}
/*
// ---------------------------------------------------------------------------
*/
MemoryArena::~MemoryArena ()
{
  FreeAligned (current_block_);
  for (auto &block : used_blocks_)      { FreeAligned (block.second); }
  for (auto &block : available_blocks_) { FreeAligned (block.second); }
}
/*
// ---------------------------------------------------------------------------
*/
auto MemoryArena::Allocate (size_t num_bytes) -> void*
{
  // Round up _nBytes_ to minimum machine alignment
#if __GNUC__ == 4 && __GNUC_MINOR__ < 9
  // gcc bug: max_align_t wasn't in std:: until 4.9.0
  const int align = alignof (::max_align_t);
#else
  const int align = alignof (std::max_align_t);
#endif
  num_bytes = (num_bytes + align - 1) & ~(align - 1);

  if (current_block_position_ + num_bytes > current_allocate_size_)
  {
    // Add current block to _used_blocks__ list
    if (current_block_)
    {
      used_blocks_.push_back
        (std::make_pair (current_allocate_size_, current_block_));
      current_block_ = nullptr;
      current_allocate_size_ = 0;
    }

    // Get new block of memory for _MemoryArena_

    // Try to get memory block from _available_blocks__
    for (auto iter = available_blocks_.begin ();
         iter != available_blocks_.end (); ++iter)
    {
      if (iter->first >= num_bytes)
      {
        current_allocate_size_ = iter->first;
        current_block_ = iter->second;
        available_blocks_.erase(iter);
        break;
      }
    }

    if (!current_block_)
    {
      current_allocate_size_ = std::max (num_bytes, block_size_);
      current_block_         = AllocAligned <uint8_t> (current_allocate_size_);
    }
    current_block_position_ = 0;
  }

  void *ret = current_block_ + current_block_position_;
  current_block_position_ += num_bytes;
  return ret;
}
/*
// ---------------------------------------------------------------------------
*/
auto MemoryArena::Reset () -> void
{
  current_block_position_ = 0;
  available_blocks_.splice (available_blocks_.begin (), used_blocks_);
}
/*
// ---------------------------------------------------------------------------
*/
auto MemoryArena::TotalAllocated () const -> size_t
{
  size_t total = current_allocate_size_;
  for (const auto &alloc : used_blocks_)      { total += alloc.first; }
  for (const auto &alloc : available_blocks_) { total += alloc.first; }
  return total;
}
/*
// ---------------------------------------------------------------------------
// Function
// ---------------------------------------------------------------------------
*/
// Memory Allocation Functions
void *AllocAligned(size_t size)
{
#if defined(NIEPCE_BUILD_TARGET_IS_WIN32)
    return _aligned_malloc(size, 16);
#else
    void *ptr;
    if (posix_memalign (&ptr, 16, size) != 0) ptr = nullptr;
    return ptr;
    // #else
    // return memalign(64, size);
#endif
}
/*
// ---------------------------------------------------------------------------
*/
void FreeAligned (void *ptr)
{
  if (!ptr) return ;
#if defined (NIEPCE_BUILD_TARGET_IS_WIN32)
    _aligned_free (ptr);
#else
    free (ptr);
#endif
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
