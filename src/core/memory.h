#ifndef _MEMORY_H_
#define _MEMORY_H_
/*
// ---------------------------------------------------------------------------
*/
#include <cstddef>
#include <cstdlib>
#include <memory>
#include <malloc.h>
#include <list>
#include <utility>
#include <iostream>
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
// Memory Declarations
#define ARENA_ALLOC(arena, Type) new ((arena).Allocate (sizeof (Type))) Type
/*
// ---------------------------------------------------------------------------
*/
void *AllocAligned(size_t size);
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
T* AllocAligned (size_t count)
{
  return reinterpret_cast <T*> (AllocAligned (count * sizeof (T)));
}
/*
// ---------------------------------------------------------------------------
*/
void FreeAligned(void *);
/*
// ---------------------------------------------------------------------------
*/
class alignas(64) MemoryArena
{
 public:
  //! The default constructor of the class.
  MemoryArena ();

  //! The constructor takes size of block.
  MemoryArena (size_t block_size);

  //! The destructor of the class.
  ~MemoryArena ();

 private:
  //! The copy constructor of the class.
  MemoryArena (const MemoryArena& memory_arena) = delete;

  //! The move constructor of the class.
  MemoryArena (const MemoryArena&& memory_arena) = delete;

  //! The copy assignment operator of the class.
  MemoryArena& operator = (const MemoryArena& memory_arena) = delete;

  //! The move assignment operator of the class.
  MemoryArena& operator = (const MemoryArena&& memory_arena) = delete;

 public:
 /*!
  * @fn void* Allocate (size_t)
  * @brief 
  * @param[in] num_bytes
  *    The number of bytes.
  * @return pointer.
  * @exception none
  * @details
  */
  auto Allocate (size_t num_bytes) -> void*;

  template <typename T, typename ... ArgTypes>
  auto Allocate (ArgTypes&& ... arguments) -> T*;

  /*!
   * @fn void Reset ()
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  auto Reset () -> void;

  /*!
   * @fn size_t TotalAllocated () const;
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  auto TotalAllocated () const -> size_t;

 private:
  //! The size of block.
  const size_t block_size_;

  size_t   current_block_position_;
  size_t   current_allocate_size_;
  uint8_t* current_block_;

  //! Memory blocks
  std::list <std::pair <size_t, uint8_t *> > used_blocks_;
  std::list <std::pair <size_t, uint8_t *> > available_blocks_;
};
/*
// ---------------------------------------------------------------------------
*/
template <typename T, typename ... ArgTypes>
auto MemoryArena::Allocate (ArgTypes&& ... arguments) -> T*
{
  T* res = reinterpret_cast <T*> (Allocate (sizeof (T)));
  // Call constructor of the T.
  new (res) T (std::forward <ArgTypes> (arguments) ... );
  return res;
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif
