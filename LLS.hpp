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
	LLS(const LLS<T>& lls) {
        list = LinkedList(lls.list);
	}
	LLS(LLS<T>&& other) noexcept {
		list = std::move(other.list);
	}
	LLS<T>& operator=(const LLS<T>& rhs) {
		if (list.getHead() == rhs.list.getHead()) {
			return *this;
		}
		delete this;
        list = LinkedList(rhs.list);
		return *this;
	}
	LLS<T>& operator=(LinkedList<T>&& other) noexcept {
		if (list.getHead() == other.list.getHead()) {
			return *this;
		}
		list = std::move(other.list);
		return *this;
	}
	~LLS() {
		list.Clear();
	}
    void push(const T& item) override {
        list.AddTail(item);
    }
    T pop() override {
        if (size == 0) {
            throw std::runtime_error("Cannot pop empty stack");
        }
        T val = (*list.getTail()).data;
        list.RemoveTail();
        return val;
    }
    T peek() const override {
        if (size == 0) {
            throw std::runtime_error("Cannot access empty stack");
        }
        return (*list.getTail()).data;
    }
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }
};