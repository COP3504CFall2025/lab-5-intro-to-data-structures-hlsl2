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
    // Big 5
    ABDQ() : capacity(1), size(0), front_(0), back_(0), arr(new T[1]) {}
    explicit ABDQ(std::size_t c) : capacity(c), size(0), front_(0), back_(0), arr(new T[1]) {}
    ABDQ(const ABDQ& adq) {
        *this = ABDQ(adq.capacity);
        for (size_t i = 0; i < adq.size; ++i) {
            this->arr[i] = adq.arr[i];
        }
    }
    ABDQ(ABDQ&& other) noexcept {
        *this = ABDQ(other.capacity);
        this->size = other.size;
        this->arr = other.arr;
        other.capacity = 1;
        other.size = 0;
        other.arr = nullptr;
    }
    ABDQ& operator=(const ABDQ& other) {
        if (this->arr && this->arr == other.arr) {
            return *this;
        }
        delete this;
        *this = ABDQ(other.capacity);
        for (size_t i = 0; i < other.size; ++i) {
            this->arr[i] = other.arr[i];
        }
        return *this;
    }
    ABDQ& operator=(ABDQ&& other) noexcept {
        if (this->arr && this->arr == other.arr) {
            return *this;
        }
        *this = ABDQ(other.capacity);
        this->size = other.size;
        this->arr = other.arr;
        other.capacity = 1;
        other.size = 0;
        other.arr = nullptr;
        return *this;
    }
    ~ABDQ() noexcept {
        delete[] arr;
    }

    // Insertion
    void pushFront(const T& item) override {
        if (size == capacity) {
            reallocate();
        }
        for (size_t i = 0; i < size; ++i) {
            arr[size] = arr[size - i];
        }
        arr[0] = item;
        ++size;
    }
    void pushBack(const T& item) override {
        if (size == capacity) {
            reallocate();
        }
        arr[size] = item;
        ++size;
    }

    // Deletion
    T popFront() override {
        T val = arr[0];
        --size;
        for (size_t i = 0; i < size; ++i) {
            arr[i] = arr[i + 1];
        }
        return val;
    }
    T popBack() override {
        --size;
        return arr[size];
    }

    // Access
    const T& front() const override {
        return arr[0];
    }
    const T& back() const override {
        return arr[size - 1];
    }

    // Getters
    std::size_t getSize() const noexcept override {
        return size;
    }

};
