#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
    LinkedList<T> list;
public:
    LLDQ() : list() {}
	LLDQ(const LLDQ<T>& lldq) {
        list = LinkedList(lldq.list);
	}
	LLDQ(LLDQ<T>&& other) noexcept {
		list.head = other.list.head;
		list.tail = other.list.tail;
		list.count = other.list.count;
		other.list.head = nullptr;
		other.list.tail = nullptr;
		other.list.count = 0;
	}
	LLDQ<T>& operator=(const LLDQ<T>& rhs) {
		if (list.head == rhs.list.head) {
			return *this;
		}
		delete this;
        list = LinkedList(rhs.list);
		return *this;
	}
	LLDQ<T>& operator=(LLDQ<T>&& other) noexcept {
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
	~LLDQ() {
		list.clear();
	}
    void pushFront(const T& item) override {
        list.addHead(item);
    }
    void pushBack(const T& item) override {
        list.addTail(item);
    }
    T popFront() override {
        T val = (*list.getHead()).data;
        list.removeHead();
    }
    T popBack() override {
        T val = (*list.getTail()).data;
        list.removeTail();
    }
    const T& front() const override {
        return (*list.getHead()).data;
    }
    const T& back() const override {
        return (*list.getTail()).data;
    }
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }
};






