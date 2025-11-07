#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* arr;
    std::size_t capacity;
    std::size_t size;
    std::size_t front_;
    std::size_t back_;
    static constexpr std::size_t SCALE_FACTOR = 2;

    void reallocate(size_t c) {
        T* temp = arr;
        arr = new T[c];
        for (std::size_t i = 0; i < size; ++i) {
            arr[i] = temp[(front_ + i) % capacity];
        }
        delete[] temp;
        capacity = c;
        front_ = 0;
        back_ = size;
    }
public:
    // Big 5
    ABDQ() : capacity(1), size(0), front_(0), back_(0), arr(new T[1]) {}
    explicit ABDQ(std::size_t c) : capacity(c), size(0), front_(0), back_(0), arr(new T[c]) {}
    ABDQ(const ABDQ& other) {
        capacity = other.capacity;
        size = other.size;
        front_ = other.front_;
        back_ = other.back_;
        arr = new T[capacity];
        for (size_t i = 0; i < other.size; ++i) {
            size_t idx =(front_ + i) % capacity;
            arr[idx] = other.arr[idx];
        }
    }
    ABDQ(ABDQ&& other) noexcept {
        capacity = other.capacity;
        size = other.size;
        arr = other.arr;
        front_ = other.front_;
        back_ = other.back_;
        other.capacity = 1;
        other.size = 0;
        other.arr = nullptr;
        other.front_ = 0;
        other.back_ = 0;
    }
    ABDQ& operator=(const ABDQ& other) {
        if (this == &other) {
            return *this;
        }
        delete[] arr;
        capacity = other.capacity;
        size = other.size;
        front_ = other.front_;
        back_ = other.back_;
        arr = new T[capacity];
        for (size_t i = 0; i < other.size; ++i) {
            size_t idx =(front_ + i) % capacity;
            arr[idx] = other.arr[idx];
        }
        return *this;
    }
    ABDQ& operator=(ABDQ&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        delete[] arr;
        capacity = other.capacity;
        size = other.size;
        arr = other.arr;
        front_ = other.front_;
        back_ = other.back_;
        other.capacity = 1;
        other.size = 0;
        other.arr = nullptr;
        other.front_ = 0;
        other.back_ = 0;
        return *this;
    }
    ~ABDQ() noexcept {
        delete[] arr;
    }

    // Insertion
    void pushFront(const T& item) override {
        if (size == capacity) {
            reallocate(capacity * SCALE_FACTOR);
        }
        front_ += capacity - 1; 
        front_ %= capacity;
        arr[front_] = item;
        ++size;
    }
    void pushBack(const T& item) override {
        if (size == capacity) {
            reallocate(capacity * SCALE_FACTOR);
        }
        arr[back_] = item;
        ++back_; back_ %= capacity;
        ++size;
    }

    // Deletion
    T popFront() override {
        if (size == 0) {
            throw std::runtime_error("Cannot pop from empty deque");
        }
        T val = arr[front_];
        ++front_; front_ %= capacity;
        --size;
        if (size > 0 && size * 4 <= capacity) {
            reallocate(capacity / SCALE_FACTOR);
        }
        return val;
    }
    T popBack() override {
        if (size == 0) {
            throw std::runtime_error("Cannot pop from empty deque");
        }
        back_ += capacity - 1; 
        back_ %= capacity;
        T val = arr[back_];
        --size;
        if (size > 0 && size * 4 <= capacity) {
            reallocate(capacity / SCALE_FACTOR);
        }
        return val;
    }

    // Access
    const T& front() const override {
        if (size == 0) {
            throw std::runtime_error("Cannot access empty deque");
        }
        return arr[front_];
    }
    const T& back() const override {
        if (size == 0) {
            throw std::runtime_error("Cannot access empty deque");
        }
        return arr[(back_ + capacity - 1) % capacity];
    }

    // Getters
    std::size_t getSize() const noexcept override {
        return size;
    }
};
