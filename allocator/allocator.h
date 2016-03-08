#ifndef MYALLOCATOR_H
#define MYALLOCATOR_H

#include <cstddef>
#include <utility>

template <typename T>
class MyAllocator
{
public:
    using value_type      = T;
    using pointer         = T*;
    using reference       = T&;
    using const_pointer   = const T*;
    using const_reference = const T&;
    using size_type       = size_t;
    using difference_type = ptrdiff_t;

    MyAllocator() noexcept = default;
    MyAllocator(const MyAllocator& alloc) noexcept = default;

    pointer address(reference x) const noexcept;
    const_pointer address(const_reference x) const noexcept;

    pointer allocate(size_type n);
    void deallocate(pointer p, size_type n) noexcept;

    size_type max_size() const noexcept;

    template <typename... Args>
        void construct(pointer p, Args&&... args);
    void destroy(pointer p);
};

#endif