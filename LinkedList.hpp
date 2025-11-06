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
		while (count < list.count) {
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
		if (head == rhs.head) {
			return *this;
		}
		Clear();
		Node* ptr = rhs.head;
		while (count < rhs.count) {
			AddTail(ptr->data);
			ptr = ptr->next;
		}
		return *this;
	}
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
		if (head == other.head) {
			return *this;
		}
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
		Node* ptr = head;
		for (size_t i = 0; i < count; ++i) {
			ptr->print();
			ptr = ptr->next;
		}
	}
	void PrintReverse() const {
		Node* ptr = tail;
		for (size_t i = 0; i < count; ++i) {
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
		//while (RemoveHead());
		Node* ptr = head;
		while(ptr) {
			Node* temp = ptr;
			ptr = ptr->next;
			delete temp;
		}
		count = 0;
	}
};