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
	LinkedList(const LinkedList<T>& other) {
		count = 0;
		for (Node* ptr = other.head; ptr; ptr = ptr->next) {
			AddTail(ptr->data);
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
	LinkedList<T>& operator=(const LinkedList<T>& other) {
		if (this == &other) {
			return *this;
		}
		Clear();
		for (Node* ptr = other.head; ptr; ptr = ptr->next) {
			AddTail(ptr->data);
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
	void PrintForward() const {
		Node* ptr = head;
		for (size_t i = 0; i < count; ++i) {
			ptr->print();
			ptr = ptr->next;
		}
	}
	void printForward() const {
		PrintForward();
	}
	void PrintReverse() const {
		Node* ptr = tail;
		for (size_t i = 0; i < count; ++i) {
			ptr->print();
			ptr = ptr->prev;
		}
	}
	void printReverse() const {
		PrintReverse();
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
		++count;
		if (count == 1) {
			head = new Node(data);
			tail = head;
			return;
		}
		Node* temp = head;
		head = new Node(data);
		temp->prev = head;
		head->next = temp;
	}
	void addHead(const T& data) {
		AddHead(data);
	}
	void AddTail(const T& data) {
		++count;
		if (count == 1) {
			tail = new Node(data);
			head = tail;
			return;
		}
		Node* temp = tail;
		tail = new Node(data);
		temp->next = tail;
		tail->prev = temp;
	}
	void addTail(const T& data) {
		AddTail(data);
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
	bool removeHead() {
		RemoveHead();
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
	bool removeTail() {
		RemoveTail();
	}
	void Clear() {
		while (RemoveHead());
	}
	void clear() {
		Clear();
	}
};