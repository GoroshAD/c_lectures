#include <iostream>
#include <memory>

template <typename T, typename K=T>
class NewAllocator {
public:
    typedef T value_type;
    NewAllocator() noexcept {}

    template <class H>
    NewAllocator(const NewAllocator<H> &) noexcept {}

    T* allocate(size_t n) {
        std::cout << "NewAllocator allocate" << std::endl;
        return static_cast<T*>(K::operator new(n * sizeof(T)));
    }

    void deallocate(T* p, size_t n) {
        std::cout << "NewAllocator deallocate" << std::endl;
        K::operator delete(p, sizeof(T) * n);
    }
};

class A {
public:
    static void* operator new(size_t size) {
        std::cout << "operator new!" << std::endl;
        return ::operator new(size);
    }

    static void operator delete(void* p, size_t size) {
        std::cout << "operator delete!" << std::endl;
        return ::operator delete(p);
    }
};

int main() {
    auto sp = std::allocate_shared<A>(NewAllocator<A>()); 
    return 0;
}

