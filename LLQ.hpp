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
		list.head = other.list.head;
		list.tail = other.list.tail;
		list.count = other.list.count;
		other.list.head = nullptr;
		other.list.tail = nullptr;
		other.list.count = 0;
	}
	LLQ<T>& operator=(const LLQ<T>& rhs) {
		if (list.head == rhs.list.head) {
			return *this;
		}
		delete this;
        list = LinkedList(rhs.list);
		return *this;
	}
	LLQ<T>& operator=(LLQ<T>&& other) noexcept {
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
	~LLQ() {
		list.clear();
	}
    void enqueue(const T& item) override {
        list.addTail(item);
    }
    T dequeue() override {
        T val = (*list.getHead()).data;
        list.removeHead();
        return val;
    }
    T peek() const override {
        return (*list.getHead()).data;
    }
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }
};