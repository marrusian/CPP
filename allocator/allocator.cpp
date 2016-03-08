#include "allocator.h"

template <typename T>
inline typename MyAllocator<T>::pointer MyAllocator<T>::allocate(size_type n)
{
    return static_cast<pointer>(::operator new(n*sizeof(value_type)));
}

template <typename T>
inline void MyAllocator<T>::deallocate(pointer p, size_type n) noexcept
{
    ::operator delete(p, n);
}

template <typename T>
inline typename MyAllocator<T>::pointer
 MyAllocator<T>::address(reference x) const noexcept
{
    return &x;
}

template <typename T>
inline typename MyAllocator<T>::const_pointer
 MyAllocator<T>::address(const_reference x) const noexcept
{
    return &x;
}

template <typename T>
inline typename MyAllocator<T>::size_type
 MyAllocator<T>::max_size() const noexcept
{
    return static_cast<size_type>(-1) / sizeof(value_type);
}

template <typename T>
template <typename... Args>
inline void MyAllocator<T>::construct(pointer p, Args&&... args)
{
    ::new(p) value_type(std::forward<Args>(args)...);
}

template <typename T>
inline void MyAllocator<T>::destroy(pointer p)
{
    p->~value_type();
}