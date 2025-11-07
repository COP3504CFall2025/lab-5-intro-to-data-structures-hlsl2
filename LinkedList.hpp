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
		count = 0;
		Node* ptr = list.head;
		while (ptr) {
			AddTail(ptr->data);
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
		if (this == &rhs) {
			return *this;
		}
		Clear();
		Node* ptr = rhs.head;
		while (ptr) {
			AddTail(ptr->data);
			ptr = ptr->next;
		}
		return *this;
	}
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
		if (this == &other) {
			return *this;
		}
		Clear();
		head = other.head;
		tail = other.tail;
		count = other.count;
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
		return *this;
	}
	~LinkedList() {
		Clear();
	}
	// Behaviors
	void printForward() const {
		for (Node* ptr = head; ptr; ptr = ptr->next) {
			ptr->print();
		}
	}
	void PrintReverse() const {
		for (Node* ptr = tail; ptr; ptr = ptr->prev) {
			ptr->print();
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
	void AddHead(const T& data) {
		if (!head) {
			head = new Node(data);
			tail = head;
			count = 1;
			return;
		}
		Node* temp = head;
		head = new Node(data);
		temp->prev = head;
		head->next = temp;
		++count;
	}
	void AddTail(const T& data) {
		if (!tail) {
			tail = new Node(data);
			head = head;
			count = 1;
			return;
		}
		Node* temp = tail;
		tail = new Node(data);
		temp->next = tail;
		tail->prev = temp;
		++count;
	}

	// Removal
	bool RemoveHead() {
		if (count == 0) {
			return false;
		}
		--count;
		if (count == 0) {
			delete head;
			head = nullptr;
			tail = nullptr;
			return true;
		}
		Node* temp = head->next;
		delete head;
		head = temp;
		head->prev = nullptr;
		return true;
	}
	bool RemoveTail() {
		if (count == 0) {
			return false;
		}
		--count;
		if (count == 0) {
			delete tail;
			tail = nullptr;
			head = nullptr;
			return true;
		}
		Node* temp = tail->prev;
		delete tail;
		tail = temp;
		tail->next = nullptr;
		return true;
	}
	void Clear() {
		while (RemoveHead());
	}
};