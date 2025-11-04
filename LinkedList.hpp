#pragma once
#include <iostream>
using namespace std;

template <typename T>
class LinkedList {
	struct Node {
		T data;
		Node* prev;
		Node* next;
		Node(T d) : data(d), prev(nullptr), next(nullptr) {}
		void print() {
			cout << data << endl;
		}
	};
	Node* head;
	Node* tail;
	unsigned int count;
public:
	LinkedList() : head(nullptr), tail(nullptr), count(0) {}
	LinkedList(const LinkedList<T>& list) {
		Node* ptr = list.head;
		while (this->count < list.count) {
			this->addTail(ptr->data);
			ptr = ptr->next;
		}
	}
	LinkedList(LinkedList<T>&& other) noexcept {
		head = other.head;
		tail = other.tail;
		count = other.count;
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	}
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
		if (this->head == rhs.head) {
			return *this;
		}
		delete this;
		Node* ptr = rhs.head;
		while (this->count < rhs.count) {
			this->addTail(ptr->data);
			ptr = ptr->next;
		}
	}
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
		if (this->head == other.head) {
			return *this;
		}
		head = other.head;
		tail = other.tail;
		count = other.count;
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	}
	~LinkedList() {
		this->Clear();
	}
	// Behaviors
	void printForward() const {
		Node* ptr = head;
		for (int i = 0; i < count; ++i) {
			ptr->print();
			ptr = ptr->next;
		}
	}
	void printReverse() const {
		Node* ptr = tail;
		for (int i = 0; i < count; ++i) {
			ptr->print();
			ptr = ptr->prev;
		}
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const {
		return count;
	}
	Node* getHead() {
		return head;
	}
	const Node* getHead() const {
		return head;
	}
	Node* getTail() {
		return tail;
	}
	const Node* getTail() const {
		return tail;
	}

	// Insertion
	void addHead(const T& data) {
		Node* temp = head;
		head = new Node(data);
		if (temp) {
			temp->prev = head;
		} else {
			tail = head;
		}
		head->next = temp;
		++count;
	}
	void addTail(const T& data) {
		Node* temp = tail;
		tail = new Node(data);
		if (temp) {
			temp->next = tail;
		} else {
			head = tail;
		}
		tail->prev = temp;
		++count;
	}

	// Removal
	bool removeHead() {
		if (count == 1) {
			delete head;
			head = nullptr;
			--count;
			return false;
		}
		Node* temp = head->next;
		temp->prev = nullptr;
		delete head;
		head = temp;
		--count;
		return true;
	}
	bool removeTail() {
		if (count == 1) {
			delete tail;
			tail = nullptr;
			--count;
			return false;
		}
		Node* temp = tail->prev;
		temp->next = nullptr;
		delete tail;
		tail = temp;
		--count;
		return true;
	}
	void Clear() {
		while (count > 0) {
			removeHead();
		}
	}
};