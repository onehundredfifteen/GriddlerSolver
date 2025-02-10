#pragma once
#include <type_traits>

template <typename T, typename = void>
struct has_bracket_operator : std::false_type {};

template <typename T>
struct has_bracket_operator<T, std::void_t<decltype(std::declval<T>()[std::declval<typename T::size_type>()])>> 
    : std::true_type {};

template <typename T, typename std::enable_if_t<has_bracket_operator<T>::value>* = nullptr>
class Array2DWrapper {
    using UnderlyingType = typename T::value_type;

 public:
    template <typename... Args>
    Array2DWrapper(size_t _offset, Args&&... args) 
        : offset(_offset), container(std::forward<Args>(args)...)
    {}
     
    UnderlyingType& operator()(size_t row, size_t col) {
        int index = row * offset + col;
        return container[index];
    }

    const UnderlyingType& operator()(size_t row, size_t col) const {
        int index = row * offset + col;
        return container.at(index);
    }

public:
    T container;
    const int offset;
};


