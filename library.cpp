#include "library.h"

Library::Node::Node() : next(0) {}

Library::Node::Node(LibraryItem *item, Node *n) : info(item), next(n) {}

Library::Library() : first(0) {}

// deep copy constructor using private method copy
Library::Library(const Library &l) : first(copy(l.first)) {}

Library::Node* Library::copy(Node *n) {
	if (!n) {
		return 0;
	} else {
		return new Node (n->info, copy(n->next));
	}
}

// deep destructor using private method destroy
Library::~Library() {
	destroy(first);
}

void Library::destroy(Node *n) {
	if (n) {
		destroy(n->next);
		delete n;
	}
}

bool Library::empty() const {
	return first == 0;
}

int Library::size() const {
	int librarySize = 0;
	Node *temp = first;
	while (temp) {
		librarySize++;
		temp = temp->next;
	}
	return librarySize;
}

void Library::addItem(LibraryItem *newItem) {
	first = new Node(newItem, first);
}

void Library::removeItem(LibraryItem *item) {
	Node *n = first, *prev = 0;

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

void Library::editItemAt(LibraryItem *item, int position) {
	LibraryItem *selectedItemGeneric = this->at(position);
	//selectedItemGeneric = item;
	selectedItemGeneric = new Book("ciao");
}

LibraryItem *Library::extract() {
	Node* n = first;
	first = first->next;
	LibraryItem* aux = n->info;
	delete n;
	return aux;
}

LibraryItem *Library::at(int index) const {
	Node *temp = first;
	int counter = 0;
	while (counter < index) {
		counter++;
		temp = temp->next;
	}
	if (temp) {
		return temp->info;
	} else {
		return NULL;
	}
}

Library &Library::operator =(const Library &l) {
	if (this != &l) { // operator!= between pointers
		destroy(first);
		first = copy(l.first);
	}
	return *this;
}

// LibraryIterator methods implementation
bool Library::LibraryIterator::operator ==(LibraryIterator iterator) const {
	return pointer == iterator.pointer;
}

bool Library::LibraryIterator::operator !=(LibraryIterator iterator) const {
	return pointer != iterator.pointer;
}

Library::LibraryIterator& Library::LibraryIterator::operator ++() {
	// prefix increase
	if (pointer) {
		pointer = pointer->next; // side effect
	}
	return *this;
}

Library::LibraryIterator Library::LibraryIterator::operator ++(int) {
	// postfix increase
	LibraryIterator aux = *this;
	if (pointer) {
		pointer = pointer->next;
	}
	return aux;
}

Library::LibraryIterator Library::begin() const {
	LibraryIterator aux;
	aux.pointer = first;
	return aux;
}

Library::LibraryIterator Library::end() const {
	LibraryIterator aux;
	aux.pointer = 0;
	return aux;
}

LibraryItem* Library::operator [](Library::LibraryIterator iterator) const {
	return (iterator.pointer)->info;
	// NB: no i.pointer != 0 checks
}
