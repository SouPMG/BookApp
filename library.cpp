#include "library.h"

library::library() : first(0) {}

library::node::node() : next(0) {}

library::node::node(libraryItem *item, node *n) : info(item), next(n) {}

bool library::empty() const {
	return first == 0;
}

void library::addItem(libraryItem *newItem) {
	first = new node(newItem, first);
}

void library::removeItem(libraryItem *item) {
	node *n = first, *prev = 0;

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

libraryItem* library::extract() {
	node* n = first;
	first = first->next;
	libraryItem* aux = n->info;
	delete n;
	return aux;
}
