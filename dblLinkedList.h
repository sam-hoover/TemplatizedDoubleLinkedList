//	dblLinkList.h

#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <exception>
#include <array>

#ifndef DBLLINKEDLIST_H
#define DBLLINKEDLIST_H

using namespace std;
static const int HEAD_VAL = -99999;

template <class T>
class dblLinkedList {
public:
	template <class T>
	class node {
	public:
		node<T> *n_next;
		node<T> *n_prev;
		node<T> *n_head;
		T n_data;
		
		// constructors
		node<T>(T data) : n_next(nullptr), n_prev(nullptr), n_head(nullptr), n_data(data) {}
		node<T>(node<T>* next, node<T>* prev, T data) : n_next(next), n_prev(prev), n_head(nullptr), n_data(data) {}

	};

	template <class T>
	class iterator {
	public:
		// constructor
		iterator<T>(node<T>* that = nullptr) : n_node(that) {}

		// operators
		iterator<T> operator++() {
			if(n_node == nullptr) {
				throw runtime_error("null pointer");
			}
			n_node = n_node->n_next;
			if(n_node == n_node->n_head) {
				n_node = nullptr;
				return(nullptr);
			} else {
				return(*this);
			}
		}

		iterator<T> operator--() {
			if(n_node == nullptr) {
				throw runtime_error("null pointer");
			}
			n_node = n_node->n_prev;
			if(n_node == n_node->n_head) {
				n_node = nullptr;
				return(nullptr);
			} else {
				return(*this);
			}
		}

		iterator<T> operator++(int) {
			if(n_node == nullptr) {
				throw runtime_error("null pointer");
			}
			iterator<T> it_node = *this;
			n_node = n_node->n_next;
			if(n_node == n_node->n_head) {
				n_node = nullptr;
			}
			return(it_node);
		}

		iterator<T> operator--(int) {
			if(n_node == nullptr) {
				throw runtime_error("null pointer");
			}
			iterator<T> it_node = *this;
			n_node = n_node->n_prev;
			if(n_node == n_node->n_head) {
				n_node = nullptr;
			}
			return(it_node);
		}

		node<T>* operator->() {return(n_node);}
		T operator*() {return(n_node->n_data);}
		operator node<T>*() {return(n_node);}

	private:
		node<T>* n_node;
	};

	// constructors
	dblLinkedList<T>() : m_head(&m_head, &m_head, /*HEAD_VAL*/ 0), m_size(0) {m_head.n_head = &m_head;}
	dblLinkedList<T>(dblLinkedList<T>& list);
	dblLinkedList<T>(T dataArray[]);

	// destructor
	~dblLinkedList<T>() {clear();}

	// accessors
	T first();
	T last();
	iterator<T> begin() const {return(m_head.n_next);}
	iterator<T> end() const {return(m_head.n_prev);}

	// mutators
	void push_front(T data);
	void push_back(T data);
	T pop_front();
	T pop_back();

	// operators
	dblLinkedList<T> operator=(const dblLinkedList<T>& list);

	// other
	bool isEmpty() const {return(m_head.n_next == &m_head);}
	node<T> next_node(node<T>* nodeIn) {return(*nodeIn->n_next);}
	void print();
	void testingShit();
	void clear();

protected:
	node<T> m_head;
	unsigned m_size;
};

template <class T>
dblLinkedList<T>::dblLinkedList(dblLinkedList<T>& list) : m_head(&m_head, &m_head, /*HEAD_VAL*/ 0), m_size(0) {
	m_head.n_head = &m_head;
	if(&list != this) {
		dblLinkedList<T>::iterator<T> it = list.begin();
		while(it != nullptr) {
			push_back(*it++);
		}
	}
}

template <class T>
dblLinkedList<T>::dblLinkedList(T dataArray[]) : m_head(&m_head, &m_head, /*HEAD_VAL*/ 0), m_size(0) {
	m_head.n_head = &m_head;
	int size = sizeof(dataArray);
	for(int i = 0; i < (size - 1); i++) {
		push_back(dataArray[i]);
	}
}

template <class T>
dblLinkedList<T> dblLinkedList<T>::operator=(const dblLinkedList& list) {
	if(&list != this) {
		dblLinkedList<T>::iterator<T> it = list.begin();
		clear();
		while(it != nullptr) {
			push_back(*it++);
		}
	}
	return(*this);
}

template <class T>
void dblLinkedList<T>::push_front(T data) {
	node<T>* new_node = new node<T>(data);		// create new node w/ passed-in value
	m_size++;								// increment size since we added to list
	new_node->n_head = &m_head;				// set new node's head pointer to m_head
	new_node->n_next = m_head.n_next;		// set new node's next pointer to m_head's next pointer
	new_node->n_prev = &m_head;				// set new node's prev pointer to m_head
	m_head.n_next = new_node;				// set m_head's next pointer to new node
	new_node->n_next->n_prev = new_node;	// set m_head's old next pointer's previous pointer to new node
}

template <class T>
void dblLinkedList<T>::push_back(T data) {
	node<T>* new_node = new node<T>(data);
	m_size++;
	new_node->n_head = &m_head;
	new_node->n_next = &m_head;
	new_node->n_prev = m_head.n_prev;
	m_head.n_prev = new_node;
	new_node->n_prev->n_next = new_node;
}

template <class T>
T dblLinkedList<T>::pop_front() {
	if(isEmpty()) {
		throw out_of_range("empty list");
	}

	node<T>* temp_node = m_head.n_next;
	T temp_data = temp_node->n_data;

	m_head.n_next = temp_node->n_next;
	m_head.n_next->n_prev = &m_head;
	temp_node->n_head = nullptr;
	m_size--;

	return(temp_data);
}

template <class T>
T dblLinkedList<T>::pop_back() {
	if(isEmpty()) {
		throw out_of_range("empty list");
	}

	node<T>* temp_node = m_head.n_prev;
	T temp_data = temp_node->n_data;

	m_head.n_prev = temp_node->n_prev;
	m_head.n_prev->n_next = &m_head;
	temp_node->n_head = nullptr;
	m_size--;

	return(temp_data);
}

template <class T>
T dblLinkedList<T>::first() {
	if(isEmpty()) {
		throw out_of_range("empty list");
	} else {
		return(m_head.n_next->n_data);
	}
}

template <class T>
T dblLinkedList<T>::last() {
	if(isEmpty()) {
		throw out_of_range("empty list");
	} else {
		return(m_head.n_prev->n_data);
	}
}

template <class T>
void dblLinkedList<T>::clear() {
	while(!isEmpty()) {
		pop_front();
	}
}

template <class T>
void dblLinkedList<T>::print() {
	dblLinkedList<T>::iterator<T> it = begin();
	while(it != nullptr) {
		cout << "(" << *it++ << ")";
		if (it != nullptr) {
			cout << "   ";
		}
	}
}

template <class T>
void dblLinkedList<T>::testingShit() {

}

#endif