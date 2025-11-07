#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
    LinkedList<T> list;
public:
    LLS() : list() {}
	LLS(const LLS<T>& lls) : list(lls.list) {}
	LLS(LLS<T>&& other) noexcept : list(std::move(other.list)) {}
	LLS<T>& operator=(const LLS<T>& other) {
		if (this == &other) {
			return *this;
		}
        list = other.list;
		return *this;
	}
	LLS<T>& operator=(LLS<T>&& other) noexcept {
		if (this == &other) {
			return *this;
		}
		list = std::move(other.list);
		return *this;
	}
	~LLS() {}
    void push(const T& item) override {
        list.AddTail(item);
    }
    T pop() override {
        if (getSize() == 0) {
            throw std::runtime_error("Cannot pop empty stack");
        }
        T val = (*list.getTail()).data;
        list.RemoveTail();
        return val;
    }
    T peek() const override {
        if (getSize() == 0) {
            throw std::runtime_error("Cannot access empty stack");
        }
        return (*list.getTail()).data;
    }
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }
};