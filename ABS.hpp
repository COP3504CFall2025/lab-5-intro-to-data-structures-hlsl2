#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
    size_t capacity;
    size_t size;
    T* arr;
    static constexpr size_t SCALE_FACTOR = 2;

    void reallocate() {
        T* temp = arr;
        capacity *= SCALE_FACTOR;
        arr = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            arr[i] = temp[i];
        }
        delete[] temp;
    }
public:
    // Big 5 + Parameterized Constructor
    ABS() : capacity(1), size(0), arr(new T[1]) {}
    explicit ABS(const size_t c) : capacity(c), size(0), arr(new T[c]) {}
    ABS(const ABS& other) {
        capacity = other.capacity;
        size = 0;
        arr = new T[capacity];
        for (size_t i = 0; i < other.size; ++i) {
            arr[i] = other.arr[i];
        }
    }
    ABS(ABS&& other) noexcept {
        capacity = other.capacity;
        size = other.size;
        arr = other.arr;
        other.capacity = 1;
        other.size = 0;
        other.arr = nullptr;
    }
    ABS& operator=(const ABS& other) {
        if (this->arr && this->arr == other.arr) {
            return *this;
        }
        delete this;
        *this = ABS(other.capacity);
        for (size_t i = 0; i < other.size; ++i) {
            this->arr[i] = other.arr[i];
        }
        return *this;
    }
    ABS& operator=(ABS&& other) noexcept {
        if (this->arr && this->arr == other.arr) {
            return *this;
        }
        *this = ABS(other.capacity);
        this->size = other.size;
        this->arr = other.arr;
        other.capacity = 1;
        other.size = 0;
        other.arr = nullptr;
        return *this;
    }
    ~ABS() noexcept {
        delete[] arr;
        arr = nullptr;
        size = 0;
        capacity = 1;
    }

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override {
        return size;
    }

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return capacity;
    }

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept {
        return arr;
    }

    // Push item onto the stack
    void push(const T& data) override {
        if (size == capacity) {
            reallocate();
        }
        arr[size] = data;
        ++size;
    }

    T peek() const override {
        if (size == 0) {
            throw std::runtime_error("Cannot access empty stack");
        }
        return arr[size];
    }

    T pop() override {
        if (size == 0) {
            throw std::runtime_error("Cannot pop empty stack");
        }
        --size;
        return arr[size];
    }
};
