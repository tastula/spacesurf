#ifndef SURF_HELPERS_HH
#define SURF_HELPERS_HH

#include <random>

template <typename T>

T random_interval(T min, T max)
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<T> uni(min, max);
    T number = uni(rng);

    return number;
}

#endif // SURF_HELPERS_HH
