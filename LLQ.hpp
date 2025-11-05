#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
    LinkedList<T> list;
public:
    LLQ() : list() {}
	LLQ(const LLQ<T>& llq) {
        list = LinkedList(llq.list);
	}
	LLQ(LLQ<T>&& other) noexcept {
		list = std::move(other.list);
	}
	LLQ<T>& operator=(const LLQ<T>& rhs) {
		if (list.getHead() == rhs.list.getHead()) {
			return *this;
		}
		delete this;
        list = LinkedList(rhs.list);
		return *this;
	}
	LLQ<T>& operator=(LLQ<T>&& other) noexcept {
		if (list.getHead() == other.list.getHead()) {
			return *this;
		}
		list = std::move(other.list);
		return *this;
	}
	~LLQ() {
		list.Clear();
	}
    void enqueue(const T& item) override {
        list.AddTail(item);
    }
    T dequeue() override {
        T val = (*list.getHead()).data;
        list.RemoveHead();
        return val;
    }
    T peek() const override {
        return (*list.getHead()).data;
    }
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }
};