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
		list = std::move(other.list);
	}
	LLDQ<T>& operator=(const LLDQ<T>& rhs) {
		if (list.getHead() == rhs.list.getHead()) {
			return *this;
		}
		delete this;
        list = LinkedList(rhs.list);
		return *this;
	}
	LLDQ<T>& operator=(LLDQ<T>&& other) noexcept {
		if (this->getHead() == other.getHead()) {
			return *this;
		}
		list = std::move(other.list);
		return *this;
	}
	~LLDQ() {
		list.Clear();
	}
    void pushFront(const T& item) override {
        list.AddHead(item);
    }
    void pushBack(const T& item) override {
        list.AddTail(item);
    }
    T popFront() override {
        T val = (*list.getHead()).data;
        list.RemoveHead();
        return val;
    }
    T popBack() override {
        T val = (*list.getTail()).data;
        list.RemoveTail();
        return val;
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






