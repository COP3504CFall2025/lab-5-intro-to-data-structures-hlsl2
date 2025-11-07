#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{
    size_t capacity;
    size_t size;
    T* arr;
    static constexpr size_t SCALE_FACTOR = 2;

    void reallocate(size_t c) {
        if (c < 1) c = 1;
        T* temp = arr;
        capacity = c;
        arr = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            arr[i] = temp[i];
        }
        delete[] temp;
    }
public:
    // Constructors + Big 5
    ABQ() : capacity(1), size(0), arr(new T[1]) {}
    explicit ABQ(const size_t c) : capacity(c), size(0), arr(new T[c]) {}
    ABQ(const ABQ& other) {
        capacity = other.capacity;
        size = other.size;
        arr = new T[capacity];
        for (size_t i = 0; i < other.size; ++i) {
            this->arr[i] = other.arr[i];
        }
    }
    ABQ(ABQ&& other) noexcept {
        capacity = other.capacity;
        size = other.size;
        arr = other.arr;
        other.capacity = 1;
        other.size = 0;
        other.arr = nullptr;
    }
    ABQ& operator=(const ABQ& other) {
        if (this == &other) {
            return *this;
        }
        delete[] arr;
        capacity = other.capacity;
        size = other.size;
        arr = new T[capacity];
        for (size_t i = 0; i < other.size; ++i) {
            this->arr[i] = other.arr[i];
        }
        return *this;
    }
    ABQ& operator=(ABQ&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        capacity = other.capacity;
        size = other.size;
        arr = other.arr;
        other.capacity = 1;
        other.size = 0;
        other.arr = nullptr;
        return *this;
    }
    ~ABQ() noexcept {
        delete[] arr;
    }

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override {
        return size;
    }
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return capacity;
    }
    [[nodiscard]] T* getData() const noexcept {
        return arr;
    }

    // Insertion
    void enqueue(const T& data) override {
        if (size == capacity) {
            reallocate(capacity * SCALE_FACTOR);
        }
        arr[size] = data;
        ++size;
    }

    // Access
    T peek() const override {
        if (size == 0) {
            throw std::runtime_error("Cannot access empty queue");
        }
        return arr[0];
    }

    // Deletion
    T dequeue() override {
        if (size == 0) {
            throw std::runtime_error("Cannot pop empty queue");
        }
        T val = arr[0];
        --size;
        for (size_t i = 0; i < size; ++i) {
            arr[i] = arr[i + 1];
        }
        if (size * 4 <= capacity) {
            reallocate(capacity / SCALE_FACTOR);
        }
        return val;
    }
};
