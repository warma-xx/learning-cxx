#include "../exercise.h"

// READ: 析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>
// READ: RAII <https://learn.microsoft.com/zh-cn/cpp/cpp/object-lifetime-and-resource-management-modern-cpp?view=msvc-170>

/// @brief 任意缓存容量的斐波那契类型。
/// @details 可以在构造时传入缓存容量，因此需要动态分配缓存空间。
class DynFibonacci {
    size_t *cache;
    int cached;

public:
    // TODO: 实现动态设置容量的构造器
    DynFibonacci(int capacity): capacity(capacity), cached(0) {
    if (capacity < 2) {
        throw std::invalid_argument("Capacity must be at least 2");
    }
    cache = new size_t[capacity]; // 动态分配缓存空间
    cache[0] = 0; // 初始化第一个斐波那契数
    cache[1] = 1; // 初始化第二个斐波那契数
    cached = 2;   // 已经缓存了两个数
}
    // TODO: 实现析构器，释放缓存空间
    ~DynFibonacci() {
    delete[] cache; // 释放动态分配的缓存空间
}
    // TODO: 实现正确的缓存优化斐波那契计算
size_t get(int i) {
    if (i < 0) {
        throw std::invalid_argument("Index must be non-negative");
    }
    if (i >= capacity) {
        throw std::out_of_range("Index exceeds cache capacity");
    }
    // 如果 i 大于当前已缓存的数量，继续计算并缓存
    while (cached <= i) {
        cache[cached] = cache[cached - 1] + cache[cached - 2];
        ++cached;
    }
    return cache[i];
}

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
