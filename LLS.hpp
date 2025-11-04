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
		list.head = other.list.head;
		list.tail = other.list.tail;
		list.count = other.list.count;
		other.list.head = nullptr;
		other.list.tail = nullptr;
		other.list.count = 0;
	}
	LLS<T>& operator=(const LLS<T>& rhs) {
		if (list.head == rhs.list.head) {
			return *this;
		}
		delete this;
        list = LinkedList(rhs.list);
		return *this;
	}
	LLS<T>& operator=(LinkedList<T>&& other) noexcept {
		if (this->head == other.head) {
			return *this;
		}
		list.head = other.list.head;
		list.tail = other.list.tail;
		list.count = other.list.count;
		other.list.head = nullptr;
		other.list.tail = nullptr;
		other.list.count = 0;
		return *this;
	}
	~LLS() {
		list.clear();
	}
    void push(const T& item) override {
        list.addTail(item);
    }
    T pop() override {
        T val = (*list.getTail()).data;
        list.removeTail();
        return val;
    }
    T peek() const override {
        return (*list.getTail()).data;
    }
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }
};