#ifndef LIBRARY_H
#define LIBRARY_H

#include "libraryitem.h"

class Library {
	friend class LibraryIterator;
	private:
		// internal private class node
		class Node {
			public:
				Node();
				Node(LibraryItem*, Node*);
				LibraryItem* info; // pointer to pure virtual base class
				Node* next;
				//~Node();
		};
		Node* first; // pointer to the first node
		static Node* copy(Node*); // deep copy utility method
		static void destroy(Node*); // deep destructor utility method

	public:
		// internal public iterator class
		class LibraryIterator {
			friend class Library;
			private:
				Library::Node* pointer; // node pointed by iterator
			public:
				bool operator ==(LibraryIterator) const;
				bool operator !=(LibraryIterator) const;
				LibraryIterator& operator ++(); // prefix
				LibraryIterator operator ++(int); // postfix
		};

		Library();
		Library(const Library&); // deep copy
		~Library(); // deep destructor

		bool empty() const;
		int size() const;
		LibraryItem* at(int) const; // get library item at a given index
		void addItem(LibraryItem*);
		void removeItem(LibraryItem*);
		LibraryItem* extract();

		//Operators
		Library& operator =(const Library&); // deep allocation

		// methods that use LibraryIterator
		LibraryIterator begin() const;
		LibraryIterator end() const;
		LibraryItem* operator [](LibraryIterator) const;
};

#endif // LIBRARY_H
