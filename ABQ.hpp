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
    // Constructors + Big 5
    ABQ() : capacity(1), size(0), arr(new T[1]) {}
    explicit ABQ(const size_t c) : capacity(c), size(0), arr(new T[c]) {}
    ABQ(const ABQ& other) {
        *this = ABQ(other.capacity);
        for (size_t i = 0; i < other.size; ++i) {
            this->arr[i] = other.arr[i];
        }
    }
    ABQ(ABQ&& other) noexcept {
        *this = ABQ(other.capacity);
        this->size = other.size;
        this->arr = other.arr;
        other.capacity = 1;
        other.size = 0;
        other.arr = nullptr;
    }
    ABQ& operator=(const ABQ& rhs) {
        if (this->arr == rhs.arr) {
            return *this;
        }
        delete this;
        *this = ABQ(rhs.capacity);
        for (size_t i = 0; i < rhs.size; ++i) {
            this->arr[i] = rhs.arr[i];
        }
    }
    ABQ& operator=(ABQ&& rhs) noexcept {
        if (this->arr == rhs.arr) {
            return *this;
        }
        *this = ABS(other.capacity);
        this->size = other.size;
        this->arr = other.arr;
        other.capacity = 1;
        other.size = 0;
        other.arr = nullptr;
    }
    ~ABQ() noexcept override {
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
            reallocate();
        }
        arr[size] = data;
        ++size;
    }

    // Access
    T peek() const override {
        return arr[0];
    }

    // Deletion
    T dequeue() override {
        T val = arr[0];
        --size;
        for (size_t i = 0; i < size; ++i) {
            arr[i] = arr[i + 1]
        }
        return val;
    }
};
