#include "library.h"

template<class T>
library::library() : first(0) {}

template<class T>
library::node::node() : next(0) {}

template<class T>
library::node::node(const T &item, node* n) : info(item), next(n) {}

template<class T>
bool library::empty() const {
	return first == 0;
}

template<class T>
void library::addItem(T newItem) {
	first = new node(newItem, first);
}

template<class T>
void library::removeItem(T item) {
	node* n = first, *prev = 0;

	while (n && !(n->info == item)) {
		prev = n;
		n = n->next;
	}

	if (n) {
		if (!prev) {
			first = n->next;
		} else {
			prev->next = n->next;
		}
		delete n;
	}
}

template<class T>
T library::extract() {
	node* n = first;
	first = first->next;
	T aux = n->info;
	delete n;
	return aux;
}
