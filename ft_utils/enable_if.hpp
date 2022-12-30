#include "is_integral.hpp"

template <bool Condition, typename T = void>
struct enable_if{};

template <typename T>
